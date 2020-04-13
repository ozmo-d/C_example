#include "bitmap.h"

/*
Reads a bitmap, only compatible with uncompressed 24bit data.
 */
int read_bitmap(FILE* fptr, ImageData* image) {
   BMPHeader header;
   InfoHeader infoheader;

    // read header
    fread(&header.type,      2,1,fptr);
    fread(&header.size,      4,1,fptr);
    fread(&header.reserved1, 2,1,fptr);
    fread(&header.reserved2, 2,1,fptr);
    fread(&header.offset,    4,1,fptr);

    fprintf(stderr,"ID is: %d, should be %d\n",header.type,'M'*256+'B');
    fprintf(stderr,"File size is %d bytes\n",header.size);
    fprintf(stderr,"Offset to image data is %d bytes\n",header.offset);
    fprintf(stderr, "Reserved1 is %d\n", header.reserved1);
    fprintf(stderr, "Reserved2 is %d\n", header.reserved2);
  

    // read info
   /* Read and check the information header */
    if (fread(&infoheader,sizeof(InfoHeader),1,fptr) != 1) {
        fprintf(stderr,"Failed to read BMP info header\n");
        return(-1);
    }
    fprintf(stderr,"Image size = %d x %d\n",infoheader.width,infoheader.height);
    fprintf(stderr,"Number of colour planes is %d\n",infoheader.planes);
    fprintf(stderr,"Bits per pixel is %d\n",infoheader.bits);
    fprintf(stderr,"Compression type is %d\n",infoheader.compression);
    fprintf(stderr,"Number of colours is %d\n",infoheader.ncolours);
    fprintf(stderr,"Number of required colours is %d\n", infoheader.importantcolours);

    if (infoheader.bits != 24) {
        fprintf(stderr,"I can only read 24 bit bitmaps :(\n");
        return(-1);
    }

    // allocate memory
    image->data = malloc(sizeof(Pixel)*infoheader.width*infoheader.height);

    // populate image data
    //uint8_t r,g,b;
    Pixel pixel;
    int ind = 0;
    fseek(fptr,header.offset,SEEK_SET);

   /* Read the image */
    for (int j=0;j<infoheader.height;j++) {
        for (int i=0;i<infoheader.width;i++) {    

        if (fread(&pixel.b,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            return(-1);
        }
        if (fread(&pixel.g,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            return(-1);
        }
        if (fread(&pixel.r,sizeof(unsigned char),1,fptr) != 1) {
            fprintf(stderr,"Image read failed\n");
            return(-1);
        }
        image->data[ind] = pixel;
        ind++;
        }
    }
    image->x = infoheader.width;
    image->y = infoheader.height;

    return 0;
}



int write_bitmap(FILE* fptr, ImageData* image) {
   BMPHeader header;
   InfoHeader infoheader;

    header.type = 'M'*256+'B';
    header.size = 3*(image->x)*(image->y)+54;
    header.offset = 54;

    header.reserved1 = 0;
    header.reserved2 = 0;

    // read header
    fwrite(&header.type,      2,1,fptr);
    fwrite(&header.size,      4,1,fptr);
    fwrite(&header.reserved1, 2,1,fptr);
    fwrite(&header.reserved2, 2,1,fptr);
    fwrite(&header.offset,    4,1,fptr);

    infoheader.size = sizeof(InfoHeader);               /* Header size in bytes      */
    infoheader.width = image->x;
    infoheader.height = image->y;                /* Width and height of image */
    infoheader.planes = 1;                /* Width and height of image */
    infoheader.bits = 24;/* Bits per pixel            */
    infoheader.compression = 0;        /* Compression type          */
    infoheader.imagesize = 3*(image->x)*(image->y);          /* Image size in bytes       */
    infoheader.xresolution = 1;
    infoheader.yresolution = 1; /* Pixels per meter          */
    infoheader.ncolours = 0;           /* Number of colours         */
    infoheader.importantcolours = 0;   /* Important colours         */
    fwrite(&infoheader, sizeof(InfoHeader), 1, fptr);

    // allocate memory

    // populate image data
    //uint8_t r,g,b;
    Pixel pixel;
    int ind = 0;
    fseek(fptr,header.offset,SEEK_SET);

   /* Read the image */
    for (int j=0;j<infoheader.height;j++) {
        for (int i=0;i<infoheader.width;i++) {

            pixel = image->data[ind];
            if (fwrite(&pixel.b,sizeof(unsigned char),1,fptr) != 1) {
                fprintf(stderr,"Image write failed\n");
                return(-1);
            }
            if (fwrite(&pixel.g,sizeof(unsigned char),1,fptr) != 1) {
                fprintf(stderr,"Image write failed\n");
                return(-1);
            }
            if (fwrite(&pixel.r,sizeof(unsigned char),1,fptr) != 1) {
                fprintf(stderr,"Image write failed\n");
                return(-1);
            }
            ind++;
        }
    }
    return 0;
}