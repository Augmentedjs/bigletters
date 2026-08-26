# Legacy font data license and attribution

The bitmap glyph data in `font_cga_thin.c`, `font_ega.c`, and
`font_phoenix.c` is adapted from TrueType fonts in VileR's
[The Ultimate Oldschool PC Font Pack](https://int10h.org/oldschool-pc-fonts/).

The adapted font data is licensed under the
[Creative Commons Attribution-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-sa/4.0/).
Copyright for the TrueType remakes and enhancements belongs to VileR. Credit
for the original hardware raster designs belongs to their respective designers.

The surrounding BigLetters program code remains licensed under the Apache
License 2.0. The CC BY-SA license applies specifically to the derived bitmap
font data named above.

## Source artifacts

The files were rasterized at their native 8-pixel size with
`tools/generate_font_pack.py`. The source artifacts used for this version were:

| Source font | SHA-256 |
|---|---|
| `Px437_IBM_CGAthin.ttf` | `ee07eb44b40c26b8bcdd8ccd7191c8d36d56386e8782ec33074c39f5d55de6b2` |
| `Px437_IBM_EGA_8x8.ttf` | `09c8e0a4bc82507dec55bbcc215ec7dc0388f565432ac81cab079cd0345cb6d0` |
| `Px437_PhoenixEGA_8x8.ttf` | `7f3c180bafa9487d9b2d0033042b63f9118637077c9ad4cdaa2874013ad76c4f` |

The TTF files are regeneration inputs and are not redistributed by this
repository.
