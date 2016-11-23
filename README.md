# GB2312 decode and render

This was a small demo. On 2004 we were doing a project in China and the printers (dot matrix printers) were brough from Spain, these models didn't have the Chinese font on the ROM so it couldn't print Chinese characters.

There were some solutions, I said it should be easy to just decode the thing, render a image and send it to the printer, someone said it was too difficult, someone from a partner company told me some pointers and this is the result.

What it does is read a file with gb2312 encoding (if I remember correctly) and renders each character separately, the fonts are included, very small compared with today's font files for CJK.