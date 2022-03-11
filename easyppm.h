#include <stdio.h>
#include <stdlib.h>


#define PPM_ERRINFO_CONTAINER_BUFSIZ 1024


// error codes. These values will be used by error functions of easyppm.

enum PPM_ERR {
    PPM_ERR__error_not_specified = 500,

    PPM_ERR__malloc_failed,

    PPM_ERR__ppmdata_t_is_null,

    PPM_ERR__value_out_of_bounds,
    PPM_ERR__coordinate_out_of_bounds,

    PPM_ERR__fopen_failed,
    PPM_ERR__fprintf_failed,
    PPM_ERR__fwrite_failed,
    PPM_ERR__fclose_failed,

    PPM_ERR__,
};



// Structure that contains info about errors raised from ppm functions.

typedef struct PPM_ERR_INFO_CONTAINER {
    char         text[PPM_ERRINFO_CONTAINER_BUFSIZ];
    char         c[PPM_ERRINFO_CONTAINER_BUFSIZ];
    int          i[PPM_ERRINFO_CONTAINER_BUFSIZ];
    unsigned int ui[PPM_ERRINFO_CONTAINER_BUFSIZ];
} PPM_ERR_INFO_C;


void ppm_err_info_set__text(char text[PPM_ERRINFO_CONTAINER_BUFSIZ]);
void ppm_err_info_set__c(char c[PPM_ERRINFO_CONTAINER_BUFSIZ]);
void ppm_err_info_set__i(int i[PPM_ERRINFO_CONTAINER_BUFSIZ]);
void ppm_err_info_set__ui(unsigned int ui[PPM_ERRINFO_CONTAINER_BUFSIZ]);

void ppm_error_msg(int err, const char *at_func);
int ppm_error(int err, const char *at_func);




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


