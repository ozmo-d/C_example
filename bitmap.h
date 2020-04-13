#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    uint8_t r, g, b;
} Pixel;

typedef struct{
    Pixel* data;
    uint32_t x, y;
} ImageData;

typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1, reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
   uint32_t size;               /* Header size in bytes      */
   int32_t width,height;                /* Width and height of image */
   uint16_t planes;       /* Number of colour planes   */
   uint16_t bits;         /* Bits per pixel            */
   uint32_t compression;        /* Compression type          */
   uint32_t imagesize;          /* Image size in bytes       */
   int32_t xresolution,yresolution;     /* Pixels per meter          */
   uint32_t ncolours;           /* Number of colours         */
   uint32_t importantcolours;   /* Important colours         */
} InfoHeader;

int read_bitmap(FILE* fptr, ImageData* image);
int write_bitmap(FILE* fptr, ImageData* image);

#endif