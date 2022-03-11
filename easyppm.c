#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "easyppm.h"


#define DEBUG 0


// Global error info holder for ppm error functions.
struct PPM_ERR_INFO_CONTAINER ppm_error_info_holder;


// writes to the global error info data structure ppm_error_info_holder
// char ppm_error_info_holder.text[PPM_ERRINFO_CONTAINER_BUFSIZ]
void ppm_err_info_set__text(char text[PPM_ERRINFO_CONTAINER_BUFSIZ]) {
    strcpy(ppm_error_info_holder.text, text);
}

// writes to the global error info data structure ppm_error_info_holder
// char ppm_error_info_holder.c[PPM_ERRINFO_CONTAINER_BUFSIZ]
void ppm_err_info_set__c(char c[PPM_ERRINFO_CONTAINER_BUFSIZ]) {
    strcpy(ppm_error_info_holder.c, c);
}

// writes to the global error info data structure ppm_error_info_holder
// int ppm_error_info_holder.i[PPM_ERRINFO_CONTAINER_BUFSIZ]
void ppm_err_info_set__i(int i[PPM_ERRINFO_CONTAINER_BUFSIZ]) {
    for (int j = 0; j < PPM_ERRINFO_CONTAINER_BUFSIZ; j++)
        ppm_error_info_holder.i[j] = i[j];
}

// writes to the global error info data structure ppm_error_info_holder
// unsigned int ppm_error_info_holder.ui[PPM_ERRINFO_CONTAINER_BUFSIZ]
void ppm_err_info_set__ui(unsigned int ui[PPM_ERRINFO_CONTAINER_BUFSIZ]) {
    for (int j = 0; j < PPM_ERRINFO_CONTAINER_BUFSIZ; j++)
        ppm_error_info_holder.ui[j] = ui[j];
}



// https://blog.podkalicki.com/bit-level-operations-bit-flags-and-bit-masks/
#define PPMERRFLAG_WARN (1 << 0) // 1 (01)
#define PPMERRFLAG_EXIT (1 << 1) // 2 (10)
// TODO: implement: exit on critical error
// TODO: add: more flags if necessary


char error_msg_buffer[2048];


void ppm_error_msg(int err, const char *at_func) {
    // just for readibility
    PPM_ERR_INFO_C *einfo = &ppm_error_info_holder;

    // temp error message buffer
    char e[2048];

    strcpy(e, "ppm: \033[0;31m error: ");
    strcpy(error_msg_buffer, e);

    switch (err) {
        case PPM_ERR__error_not_specified:
            sprintf(e, "Error not specified."); break;
        case PPM_ERR__malloc_failed:
            sprintf(e, "'malloc() failed'"); break;
        case PPM_ERR__ppmdata_t_is_null:
            sprintf(e, "'ppmdata_t structure is null'"); break;
        case PPM_ERR__value_out_of_bounds:
            sprintf(e, "'Value out of bounds'\n      value %d should be between (%d, %d)", einfo->i[0], einfo->i[1], einfo->i[2]);
            break;
        case PPM_ERR__coordinate_out_of_bounds:
            sprintf(e, "'Coordinate out of bounds'\n      Coordinate value %d should be between (%d, %d)", einfo->i[0], einfo->i[1], einfo->i[2]);
            break;
        case PPM_ERR__fopen_failed:
            sprintf(e, "'fopen() failed'"); break;
        case PPM_ERR__fprintf_failed:
            sprintf(e, "'fprintf() failed'"); break;
        case PPM_ERR__fwrite_failed:
            sprintf(e, "'fwrite() failed"); break;
        case PPM_ERR__fclose_failed:
            sprintf(e, "'fclose() failed'"); break;
    }
    strcat(e, "\033[0m\n");
    strcat(error_msg_buffer, e);

    sprintf(e, "      inside this function: '%s()'\n", at_func);
    strcat(error_msg_buffer, e);

    sprintf(e, "          einfo-text: %s\n", einfo->text);
    strcat(error_msg_buffer, e);
}



int ppm_error(int err, const char *at_func) {
    error_msg_buffer[0] = '\0';

    // TODO: get errinfo structure and for every error, print err info
    switch (err) {
        case PPM_ERR__error_not_specified:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__malloc_failed:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__ppmdata_t_is_null:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__value_out_of_bounds:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__coordinate_out_of_bounds:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__fopen_failed:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__fprintf_failed:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__fwrite_failed:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;
        case PPM_ERR__fclose_failed:
            ppm_error_msg(err, at_func);
            printf("%s\n", error_msg_buffer);
            break;

    }
    return 0;
}

//TODO
void ppm_catch_error(int error_code, const char *at_func, int err_msg_code);

ppmdata_t *ppm_init(int x, int y) {
    unsigned long data_size = x * y * 3;

    ppmdata_t *ppm = NULL;

    ppm = malloc(sizeof(ppmdata_t));
    if (ppm == NULL)
        ppm_error(PPM_ERR__malloc_failed, __FUNCTION__);
    if (DEBUG) printf("addr of ppm -> %p\n", ppm);

    ppm->x = x; ppm->y = y;
    if (DEBUG) printf("ppm->x = %d, ppm->y = %d\n", ppm->x, ppm->y);

    ppm->pixel_data = malloc(sizeof(char) * x * y * 3);
    if (ppm->pixel_data == NULL)
        ppm_error(PPM_ERR__malloc_failed, __FUNCTION__);

    if (DEBUG) printf("addr of pixel_data -> %p\n", ppm->pixel_data);

    for (int i = 0; i < data_size; i++)
        ppm->pixel_data[i] = 0;

    ppm->cnt_pixel_paint_op = 0;
    ppm->cnt_chunk_paint_op = 0;


    return ppm;
}


int ppm_write_to_pixel(ppmdata_t *ppm, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    // don't check the validity of the values. this function is heavily used.
    // just make sure your values are valid.
    
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
    if (ppm == NULL) ppm_error(PPM_ERR__ppmdata_t_is_null, __FUNCTION__);

    int ppmx = ppm->x;
    int ppmy = ppm->y;

    int errinfo[1024];

    if (!(x1 >= 0 && x1 < ppmx)) {
        errinfo[0] = x1; errinfo[1] = 0; errinfo[2] = ppmx;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    }
    if (!(y1 >= 0 && y1 < ppmy)) {
        errinfo[0] = y1; errinfo[1] = 0; errinfo[2] = ppmy;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    }

    if (!(x2 >= 0 && x2 < ppmx)) {
        errinfo[0] = x2; errinfo[1] = 0; errinfo[2] = ppmx;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    }
    if (!(y2 >= 0 && y2 < ppmy)) {
        errinfo[0] = y2; errinfo[1] = 0; errinfo[2] = ppmy;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    }

    if (!(r >= 0 && r < 256)) {
        errinfo[0] = r; errinfo[1] = 0; errinfo[2] = 256;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__value_out_of_bounds, __FUNCTION__);
    }
    if (!(g >= 0 && g < 256)) {
        errinfo[0] = g; errinfo[1] = 0; errinfo[2] = 256;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__value_out_of_bounds, __FUNCTION__);
    }
    if (!(b >= 0 && b < 256)) {
        errinfo[0] = b; errinfo[1] = 0; errinfo[2] = 256;
        ppm_err_info_set__i(errinfo);
        ppm_error(PPM_ERR__value_out_of_bounds, __FUNCTION__);
    }


    // fill every pixel with same color

    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++)
            ppm_write_to_pixel(ppm, i, j, r, g, b);

    return 0;
}


//int ppm_paint_spray();
//int ppm_paint_gradient();

//int ppm_draw_dot();
//int ppm_draw_line();
//int ppm_draw_circle();
//int ppm_draw_rect();
//int ppm_draw_diagonal();


//int    ppm_write_from_buf(ppmdata_t *ppm, int x, int y, unsigned char *buf, int buf_x, int buf_y);
//int    ppm_write_from_buf_to_coordinate(ppmdata_t *ppm, int x, int y, unsigned char *buf, int buf_x, int buf_y);
//char * ppm_pixel_read(ppmdata_t *ppm, int x, int y);

int ppm_save_to_file(ppmdata_t *ppm, char filename[256]) {
    if (ppm == NULL)
        ppm_error(PPM_ERR__ppmdata_t_is_null, __FUNCTION__);

    // TODO: catch error
    FILE *fp = fopen(filename, "wb");
    // TODO: catch error
    fprintf(fp, "P6\n%d %d\n255\n", ppm->x, ppm->y);
    // TODO: catch error
    fwrite(ppm->pixel_data, ppm->x * ppm->y * 3, 1, fp);
    // TODO: catch error
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
    if (ppm == NULL)
        ppm_error(PPM_ERR__ppmdata_t_is_null, __FUNCTION__);

    if (!(startX >= 0 && startX < ppm->x))
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    if (!(startY >= 0 && startY < ppm->x))
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    if (!(endX >= 0 && endX < ppm->x))
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);
    if (!(endY >= 0 && endY < ppm->x))
        ppm_error(PPM_ERR__coordinate_out_of_bounds, __FUNCTION__);

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


