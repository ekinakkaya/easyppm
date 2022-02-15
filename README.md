# easyppm.c

small .ppm library for doing various image-related tasks. .ppm files can be compiled to other formats with ffmpeg. multiple files can be compiled into videos with ffmpeg. this is basically the first step.

## compile and run
with gcc:
```sh
# random-noise example
gcc example.c easyppm.c && ./a.out

# looped memory test for leaks
gcc memtest.c easyppm.c && ./a.out
```
