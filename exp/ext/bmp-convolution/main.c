#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cv.h"

static PixelBlock empty;

PixelBlock *get_pixel(BMPImage *img, int x, int y) {
    if (0 <= x && x < img->width && 0 <= y && y < img->height) {
        // Ref: cv.c line 69
        return img->imageData + (img->height - 1 - x) * img->width + y;
    } else {
        return &empty;
    }
}

int const dx_[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int const dy_[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
#define dlen sizeof(dx_) / sizeof(*dx_)

BMPImage *Convolution2D(BMPImage *raw, float const kernel[static 3][3]) {
    BMPImage *res = malloc(sizeof(*res));
    memcpy(res, raw, sizeof(*res));
    res->imageData = calloc(res->height * res->width, sizeof(PixelBlock));

    for (int x = 0; x < res->height; x++) {
        for (int y = 0; y < res->width; y++) {
            PixelBlock *const target = get_pixel(res, x, y);

            float tB = 0, tG = 0, tR = 0;
            for (size_t i = 0; i < dlen; i++) {
                int const dx = dx_[i];
                int const dy = dy_[i];
                PixelBlock const *const source = get_pixel(raw, x + dx, y + dy);

                // 要先求和, 再截断
                // target->B = (uint8_t) (source->B * kernel[dx + 1][dy + 1]);
                // target->G = (uint8_t) (source->G * kernel[dx + 1][dy + 1]);
                // target->R = (uint8_t) (source->R * kernel[dx + 1][dy + 1]);

                tB += source->B * kernel[dx + 1][dy + 1];
                tG += source->G * kernel[dx + 1][dy + 1];
                tR += source->R * kernel[dx + 1][dy + 1];
            }

            target->B = (uint8_t) tB;
            target->G = (uint8_t) tG;
            target->R = (uint8_t) tR;
        }
    }

    return res;
}

void bmp_free(BMPImage *img) {
    free(img->imageData);
    free(img);
}

float const outline[3][3] = {
    {-1. / 8, -1. / 8, -1. / 8},
    {-1. / 8, 1, -1. / 8},
    {-1. / 8, -1. / 8, -1. / 8},
};

float const gaussian[3][3] = {
    {0.089, 0.112, 0.089},
    {0.112, 0.100, 0.112},
    {0.089, 0.112, 0.089},
};

float const sculpture[3][3] = {
    {-1. / 2, -0, -0},
    {-0., 0, -0},
    {0, 0, 1. / 2},
};

float const identify[3][3] = {
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0},
};

#define save_bmp(img, kernel_name)                                             \
    do {                                                                       \
        BMPImage *res = Convolution2D(img, kernel_name);                       \
        if (SaveBMPImage("out/xm_" #kernel_name ".bmp", res)) {                    \
            printf("BMP image " #kernel_name " processed.\n");                 \
            bmp_free(res);                                                     \
        }                                                                      \
    } while (0)

int main() {
    BMPImage *img = LoadBMPImage("xm.bmp");

    save_bmp(img, identify);
    save_bmp(img, outline);
    save_bmp(img, gaussian);
    save_bmp(img, sculpture);

    bmp_free(img);

    return 0;
}
