# easyppm.c

Small .ppm library for creating image files. Provides basic functions like painting pixels or chunks. ffmpeg can be used to convert ppm files to png files.

## examples
Note: ```./ppmtopng.sh``` script can be used to convert and copy all .ppm images to ./images directory as .png files.

```sh
# avatar creator example
gcc examples/avatar-creator.c easyppm.c && ./a.out
```
![avatar](./README-images/avatar.png)
![avatar](./README-images/avatar-C4BDAC35.png)

---
```sh
# text rendering example
gcc examples/text-rendering.c easyppm.c && ./a.out
```
![avatar](./README-images/text.png)




```sh
# random noise example
gcc examples/example.c easyppm.c && ./a.out
```
[image]


## compile and run

with gcc:
```sh
# looped memory test for leaks
gcc example/memtest.c easyppm.c && ./a.out
```
