#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "easyppm.h"

int main() {
    srand(time(NULL));

    ppmdata_t *ppmdata = ppm_init(200, 200);

    for (int i = 0; i < ppmdata->x; i++) {
        for (int j = 0; j < ppmdata->y; j++) {
            ppm_write_to_pixel(ppmdata, i, j, rand() % 255, rand() % 255, rand() % 255);
        }
    }

    printf("ppmdata x: %d | y: %d\n", ppmdata->x, ppmdata->y);
    ppm_print_chunk(ppmdata, 0, 0, 10, 10);
    
    ppm_save_to_file(ppmdata, "random-noise.ppm");

    ppm_free(ppmdata);

    // it works!!

    return 0;
}
