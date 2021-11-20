#ifndef CV_H
#define CV_H
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t bfSize;     //�ļ���С
    uint16_t fReserved1; //������
    uint16_t fReserved2; //������
    uint32_t fOffBits;   //λͼ����ƫ���ֽ���
} BitMapFileHeader;      /*�ļ�ͷ*/

typedef struct {
    uint32_t biSize;          //�ṹ�峤��
    int32_t  biWidth;         //λͼ����
    int32_t  biHeight;        //λͼ�߶�
    uint16_t biPlanes;        //λͼƽ����
    uint16_t biBitCount;      //��ɫλ��
    uint32_t biCompression;   //ѹ����ʽ
    uint32_t biSizeImage;     //ʵ��λͼ����ռ�õ��ֽ���
    int32_t  biXPelsPerMeter; // X����ֱ���
    int32_t  biYPelsPerMeter; // Y����ֱ���
    uint32_t biClrUsed;       //ʹ�õ���ɫ��
    uint32_t biClrImportant;  //��Ҫ��ɫ��
} BitMapInfoHeader;           /*λͼ��Ϣͷ*/

typedef struct {
    uint8_t B;
    uint8_t G;
    uint8_t R;
} PixelBlock;

typedef struct {
    int32_t     width;
    int32_t     height;
    int32_t     channels;
    PixelBlock *imageData;
} BMPImage;

BMPImage *LoadBMPImage(char *path);
bool      SaveBMPImage(char *path, BMPImage *bmpImg);

#endif
