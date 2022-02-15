#include <stdio.h>
#include <stdlib.h>

#include "easyppm.h"


#define DEBUG 0


ppmdata_t *ppm_init(int x, int y) {
    unsigned long data_size = x * y * 3;

    ppmdata_t *ppm = NULL;

    ppm = malloc(sizeof(ppmdata_t));
    if (DEBUG) printf("addr of ppm -> %p\n", ppm);

    ppm->x = x; ppm->y = y;
    if (DEBUG) printf("ppm->x = %d, ppm->y = %d\n", ppm->x, ppm->y);

    ppm->pixel_data = malloc(sizeof(char) * x * y * 3);
    if (DEBUG) printf("addr of pixel_data -> %p\n", ppm->pixel_data);

    for (int i = 0; i < data_size; i++)
        ppm->pixel_data[i] = 0;

    ppm->cnt_pixel_paint_op = 0;
    ppm->cnt_chunk_paint_op = 0;


    return ppm;
}


int ppm_write_to_pixel(ppmdata_t *ppm, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    // TODO: check validity of all values

    // pixel [x, y]
    // pixel [1, 1]
    // pixel [y * X + x]
    
    int data_index = x * 3 + y * ppm->x * 3;
    ppm->pixel_data[data_index + 0] = r;
    ppm->pixel_data[data_index + 1] = g;
    ppm->pixel_data[data_index + 2] = b;

    ppm->cnt_pixel_paint_op++;

    return 0;
}


// TODO: should the paint and draw functions use ppm_write_to_pixel or write to pixels themselves?
// first option makes a lot of function calls
// second option rewrites the ppm_write_to_pixel function in every function
// conclusion: will go with the second one. it's easy to replace the function anyways.


int ppm_paint_fill(ppmdata_t *ppm, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
    // TODO: check validity of all passed values

    // fill every pixel with same color

    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++)
            ppm_write_to_pixel(ppm, i, j, r, g, b);

    return 0;
}


int ppm_paint_spray();
int ppm_paint_gradient();

int ppm_draw_dot();
int ppm_draw_line();
int ppm_draw_circle();
int ppm_draw_rect();
int ppm_draw_diagonal();


int    ppm_write_from_buf(ppmdata_t *ppm, int x, int y, unsigned char *buf, int buf_x, int buf_y);
int    ppm_write_from_buf_to_coordinate(ppmdata_t *ppm, int x, int y, unsigned char *buf, int buf_x, int buf_y);
char * ppm_pixel_read(ppmdata_t *ppm, int x, int y);

int    ppm_save_to_file(ppmdata_t *ppm, char filename[256]) {
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", ppm->x, ppm->y);
    fwrite(ppm->pixel_data, ppm->x * ppm->y * 3, 1, fp);
    fclose(fp);

    return 0;
}


int ppm_free(ppmdata_t *ppm) {
    free(ppm->pixel_data);
    free(ppm);
    ppm = NULL;

    return 0;
}


void ppm_print_chunk(ppmdata_t *ppm, int startX, int startY, int endX, int endY) {
    // TODO: check validity of all values
    if ( !(startX < ppm->x && startY < ppm->y  && endX < ppm->x && endY < ppm->y) ) {
        printf("easyppm [error, (void) ppm_print_chunk()]: invalid coordinate parameters");
        return;
    }

    printf("resolution: %dx%d\n", ppm->x, ppm->y);
    printf("pixels painted %lu times, chunks painted %lu times\n",
            ppm->cnt_pixel_paint_op,
            ppm->cnt_chunk_paint_op );
    printf("from %d, %d to %d %d\n", startX, startY, endX, endY);

    for (int j = startY; j <= endY; j++) {
        for (int i = startX; i <= endX; i++) {
            int pixel_index = ppm->x * j * 3 + i * 3;
            printf("%2x ", ppm->pixel_data[pixel_index]);
            printf("%2x ", ppm->pixel_data[pixel_index + 1]);
            printf("%2x|", ppm->pixel_data[pixel_index + 2]);
        }
        printf("\n");
    }
    printf("\n");
}


/*

int main() {
    ppmdata_t *ppmdata = ppm_init(IMAGE_WIDTH, IMAGE_HEIGHT);
    ppm_print_chunk(ppmdata, 0, 0, 10, 10);

    ppm_write_to_pixel(ppmdata, 0, 0, 1, 1, 1);
    ppm_write_to_pixel(ppmdata, 1, 0, 2, 2, 2);
    ppm_write_to_pixel(ppmdata, 0, 1, 2, 2, 2);
    ppm_write_to_pixel(ppmdata, 5, 3, 111, 222, 123);
    ppm_print_chunk(ppmdata, 0, 0, 10, 10);


    ppm_write_to_pixel(ppmdata, 300, 300, 1, 1, 1);
    ppm_write_to_pixel(ppmdata, 301, 301, 1, 1, 1);
    ppm_write_to_pixel(ppmdata, 302, 302, 1, 1, 1);
    ppm_write_to_pixel(ppmdata, 303, 303, 1, 1, 1);
    ppm_write_to_pixel(ppmdata, 304, 304, 1, 1, 1);
    ppm_print_chunk(ppmdata, 300, 300, 310, 310);

    ppm_paint_fill(ppmdata, 305, 305, 310, 310, 200, 200, 2);
    ppm_print_chunk(ppmdata, 300, 300, 310, 310);

    ppm_save_to_file(ppmdata, "testwowwowwow.ppm");

    
    return 0;
}


*/
