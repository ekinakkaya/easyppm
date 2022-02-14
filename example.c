#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"

int main() {
    ppmdata_t *ppmdata = ppm_init(200, 200);

    ppm_paint_fill(ppmdata, 100, 100, 120, 120, 200, 100, 50);
    ppm_save_to_file(ppmdata, "test.ppm");

    // it works!!

    return 0;
}
