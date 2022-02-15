#include <stdio.h>
#include <stdlib.h>

typedef struct ppmdata_struct_ {
    int x, y;
    unsigned char *pixel_data; // size of x * y * 3

    unsigned long int cnt_pixel_paint_op;
    unsigned long int cnt_chunk_paint_op;
} ppmdata_t;

ppmdata_t *ppm_init(int x, int y);

int    ppm_write_to_pixel(ppmdata_t *ppm, int x, int y, unsigned char r, unsigned char g, unsigned char b);

int    ppm_paint_fill(ppmdata_t *ppm, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);

//int    ppm_paint_spray();
//int    ppm_paint_gradient();

//int    ppm_draw_dot();
//int    ppm_draw_line();
//int    ppm_draw_circle();
//int    ppm_draw_rect();
//int    ppm_draw_diagonal();


//int    ppm_write_from_buf(ppmdata_t *ppm, int x, int y, unsigned char *buf, int buf_x, int buf_y);
//int    ppm_write_from_buf_to_coordinate(ppmdata_t *ppm, int x, int y, unsigned char *buf, int buf_x, int buf_y);
//char * ppm_pixel_read(ppmdata_t *ppm, int x, int y);
int    ppm_save_to_file(ppmdata_t *ppm, char filename[256]);
int    ppm_free(ppmdata_t *ppm);

void   ppm_print_chunk(ppmdata_t *ppm, int startX, int startY, int endX, int endY);
