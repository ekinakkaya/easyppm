#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../easyppm.h"
#include "../font.h"

#define IMAGE_X 400
#define IMAGE_Y 400

#define FONT_SIZE 8

#define CHECK_BIT(var, pos)    ( ( (var)>>(pos) ) & 1 )


char *get_char_bitmap(char c) {
    return font8x8_basic[c];
}


void print_bits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char *) ptr;
    unsigned char byte;

    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");

}





int main() {
    ppmdata_t *ppmdata = ppm_init(IMAGE_X, IMAGE_Y);

    // paint the canvas to all white
    ppm_paint_fill(ppmdata, 0, 0, IMAGE_X-1, IMAGE_Y-1, 255, 255, 255);

    int text_color[3] = {0, 0, 0};


    // rendering the font will be easy. the data is 8x8 bitmap.

    char *msg = "hello!";
    for (int i = 0; i < strlen(msg); i++) {
        // let's read the bitmap and paint chunks accordingly.

        char *bitmap = get_char_bitmap(msg[i]);
        //for (int j = 0; j < 8; j++) print_bits(sizeof(char), &bitmap[j]);
        

        for (int j = 0; j < 8; j++) {     // columns
            for (int k = 0; k < 8; k++) { // rows
                // the x coordinate has an offset according to the i'th letter we're writing.
                if ((bitmap[j] >> k) & 1) ppm_paint_fill(ppmdata,
                                                         (i * FONT_SIZE * 8) + k * FONT_SIZE, j * FONT_SIZE,
                                                         (i * FONT_SIZE * 8) + (k + 1) * FONT_SIZE - 1, (j + 1) * FONT_SIZE - 1,
                                                         text_color[0], text_color[1], text_color[2]);
            }
        }
    }

    ppm_save_to_file(ppmdata, "text.ppm");
    ppm_free(ppmdata);
    

    return 0;
}



