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
