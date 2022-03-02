# easyppm.c

Small .ppm library for creating image files. Provides basic functions like painting pixels or chunks. ffmpeg can be used to convert ppm files to png files.

## examples

```sh
# avatar creator example
gcc examples/avatar-creator.c easyppm.c && ./a.out
```
[image]



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
