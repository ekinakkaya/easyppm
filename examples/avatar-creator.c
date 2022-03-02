#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../easyppm.h"

#define GRID_SIZE 7  //dots
#define DOTS      10 //dots will be painted

#define DOT_SIZE  40 //px
#define MARGIN    20 //px

int grid[GRID_SIZE][GRID_SIZE];

int main() {
    srand(time(NULL));

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }

    // random color. all the dots will be the same color
    int R = rand() % 256;
    int G = rand() % 256;
    int B = rand() % 256;

    // let's paint random dots in our grid
    for (int i = 0; i < DOTS; i++) {
        int randx = rand() % GRID_SIZE;
        int randy = rand() % GRID_SIZE;

        grid[randx][randy] = 1;
        
        // make it symmetrical so the image looks a bit nicer.
        grid[GRID_SIZE - randx - 1][randy] = 1;
    }



    // let's actually create the image. every dot will have a size of 40x40 pixels.
    // and the image will have a margin of 20 pixels.
    int imgsize = MARGIN * 2 + GRID_SIZE * DOT_SIZE;
    ppmdata_t *ppmdata = ppm_init(imgsize, imgsize);

    // paint the image white
    ppm_paint_fill(ppmdata, 0, 0, imgsize-1, imgsize-1, 255, 255, 255);

    for (int i = 0; i < GRID_SIZE; i++) {
        int y = MARGIN + i * DOT_SIZE;
        for (int j = 0; j < GRID_SIZE; j++) {
            int x = MARGIN + j * DOT_SIZE;
            if (grid[j][i] == 1) ppm_paint_fill(ppmdata, x, y, x + DOT_SIZE - 1, y + DOT_SIZE - 1, R, G, B);
        }
    }

    char filename[128];
    // create a unique name from the grid
    int gridseed = 17927795;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) gridseed = gridseed * 1373 + (gridseed - 79) % GRID_SIZE * 999;
            else                 gridseed = gridseed * 2398 + (gridseed - 1892) % GRID_SIZE * 333;
        }
    }

    sprintf(filename, "avatar-%X.ppm", gridseed);
    ppm_save_to_file(ppmdata, filename);



    return 0;
}
