/* random noise example - memory allocation test results (no read or write to a file)
 * environment:
 * Windows 11 + WSL2
 *
 * 10000 generations usually happen in 12-13 seconds,
 * which means 0.0012 - 0.0013 seconds per generation.
 * but i feel like the compiler heavily optimizes the code
 *
 * memory usage of the process:
 * VIRT: 2492 bytes
 * RES:  712 bytes
 * SHR:  644 bytes
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "easyppm.h"

int main() {
    srand(time(NULL));
    int count = 0;

    time_t begin, end;
    time(&begin);

    while (1) {

        ppmdata_t *ppmdata = ppm_init(200, 200);

        for (int i = 0; i < ppmdata->x; i++) {
            for (int j = 0; j < ppmdata->y; j++) {
                ppm_write_to_pixel(ppmdata, i, j, rand() % 255, rand() % 255, rand() % 255);
            }
        }
        ppm_free(ppmdata);
        count++;


        int test_batch = 10000;
        if (count == test_batch) {
            time(&end);

            begin = end - begin;

            printf("random-noise generated (%d times) in %ld seconds. avg time per generation: %.5f\n", test_batch, begin, (double) begin / 10000);
            fflush(stdout);
            count = 0;
            
            time(&begin);
        }
    }
    return 0;
}
