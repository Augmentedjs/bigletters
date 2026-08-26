#!/bin/sh

set -eu

task_tmp_dir=$(mktemp -d "${TMPDIR:-/tmp}/bigletters-cli.XXXXXX")
trap 'rm -rf "$task_tmp_dir"' EXIT HUP INT TERM

./bigletters -t "Title 123" > "$task_tmp_dir/default"
./bigletters -t "Title 123" --font cga-thin > "$task_tmp_dir/cga-thin"
cmp "$task_tmp_dir/default" "$task_tmp_dir/cga-thin"

./bigletters -t "Title 123" -b > "$task_tmp_dir/bold-flag"
./bigletters -t "Title 123" --font ega > "$task_tmp_dir/ega"
cmp "$task_tmp_dir/bold-flag" "$task_tmp_dir/ega"

if cmp -s "$task_tmp_dir/default" "$task_tmp_dir/ega"; then
    echo "default and bold output should remain distinct" >&2
    exit 1
fi

task_escape=$(printf '\033')
./bigletters -t "A" -u > "$task_tmp_dir/single-raw"
./bigletters -t "AA" -u > "$task_tmp_dir/double-raw"
sed "s/${task_escape}\[[0-9;]*m//g" \
    "$task_tmp_dir/single-raw" > "$task_tmp_dir/single"
sed "s/${task_escape}\[[0-9;]*m//g" \
    "$task_tmp_dir/double-raw" > "$task_tmp_dir/double"
awk '{ print $0 $0 }' \
    "$task_tmp_dir/single" > "$task_tmp_dir/expected-double"
cmp "$task_tmp_dir/double" "$task_tmp_dir/expected-double"

./bigletters -t "A" -u -s > "$task_tmp_dir/slanted-raw"
sed "s/${task_escape}\[[0-9;]*m//g" \
    "$task_tmp_dir/slanted-raw" > "$task_tmp_dir/slanted"
awk '{
    offset = NR <= 4 ? 4 - NR : 0
    for (column = 0; column < offset; column++) {
        printf " "
    }
    print $0
}' "$task_tmp_dir/single" > "$task_tmp_dir/expected-slanted"
cmp "$task_tmp_dir/slanted" "$task_tmp_dir/expected-slanted"

./bigletters -t "RGB" -r 12,34,56 > "$task_tmp_dir/rgb"
./bigletters -t "RGB" -c 999 -r 12,34,56 > "$task_tmp_dir/rgb-after-color"
./bigletters -t "RGB" -r 12,34,56 -c 999 > "$task_tmp_dir/rgb-before-color"
cmp "$task_tmp_dir/rgb" "$task_tmp_dir/rgb-after-color"
cmp "$task_tmp_dir/rgb" "$task_tmp_dir/rgb-before-color"

./bigletters -t "RGB" -r 12,34,56 -i -s \
    > "$task_tmp_dir/rgb-inverse-slanted"
task_slant_prefix=$(printf '   \033[48;2;12;34;56m')
task_actual_prefix=$(head -c "${#task_slant_prefix}" \
    "$task_tmp_dir/rgb-inverse-slanted")
if test "$task_actual_prefix" != "$task_slant_prefix"; then
    echo "slant padding should precede the inverse RGB escape" >&2
    exit 1
fi

if ./bigletters -t "RGB" -r 256,0,0 > /dev/null 2>&1; then
    echo "out-of-range RGB input should fail" >&2
    exit 1
fi

if ./bigletters -t "RGB" -r 1,2 > /dev/null 2>&1; then
    echo "incomplete RGB input should fail" >&2
    exit 1
fi
