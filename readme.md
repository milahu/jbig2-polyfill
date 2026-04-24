# jbig2-polyfill

decode [JBIG2](https://en.wikipedia.org/wiki/JBIG2) images in a web browser



## status

working prototype



## todo

- streaming decode (for large images)
- use pdfium jbig2_decoder.cpp
- test multi-page images



## why

the [JBIG2](https://en.wikipedia.org/wiki/JBIG2) image format is useful  
to store [binary images](https://en.wikipedia.org/wiki/Binary_image)

this binary image compression method  
is already supported in the PDF format  
which is supported by practically all web browsers

it is useful for images of text  
for example scanned book pages  
with single-bit depth (bitonal images)  
and high resolution (usually 600 dpi)

the only usable alternative is the AVIF image format  
but compressing AVIF images  
takes about 100 times more CPU time  
than compressing JBIG2 images  
to get similar file size and similar visual quality

binary image compression methods  
are useful for [EPUB-FXL documents](https://github.com/internetarchive/archive-hocr-tools/pull/23)  
(FXL = fixed layout)  
which are similar to PDF documents of scanned book pages  
but implemented in HTML



## limitations

the polyfill does not work over the file protocol,
because we cannot
[fetch](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API/Using_Fetch)
the JBIG2 image



## browser support

currently, no web browsers support JBIG2 images

... based on
https://en.wikipedia.org/wiki/Comparison_of_web_browsers#Image_format_support



## related

https://github.com/Fyrd/caniuse/issues/7513  
JBIG2 image compression

https://stackoverflow.com/questions/22272466  
Using pdf.js to render a JBIG2 image in a browser

https://en.wikipedia.org/wiki/JBIG2

> JBIG2 is an image compression standard for bi-level images,
> developed by the Joint Bi-level Image Experts Group.
> It is suitable for both lossless and lossy compression.
> According to a press release from the Group,
> in its lossless mode JBIG2 typically generates files 3–5 times smaller than Fax Group 4
> and 2–4 times smaller than JBIG,
> the previous bi-level compression standard released by the Group.
> JBIG2 was published in 2000 as the international standard ITU T.88,
> and in 2001 as ISO/IEC 14492.

https://help.accusoft.com/ImageGear/v17.1/Windows/DLL/HTML/topic672.html

> JBIG2_DISABLE_CSM - This parameter, when TRUE, specifies that Combined Symbol Matching will not be used. When this option is TRUE, the compression algorithm uses lossy compression. Using lossy compression is likely to result in an image that is smaller (lossless compression can result in encoded images up to 2-3x larger) and a compression speed that is slower than when using lossless compression.



## JBIG2 decoders

https://github.com/ArtifexSoftware/jbig2dec

https://pdfium.googlesource.com/pdfium/+/refs/heads/main/core/fxcodec/jbig2/jbig2_decoder.cpp

https://cgit.freedesktop.org/poppler/poppler/tree/poppler/JBIG2Stream.cc



## alternative container formats

the TIFF format supports JBIG2 compression in theory,
but many tools (like imagemagick or GIMP) dont support it
