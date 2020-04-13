#include "bitmap.h"

// invert image data, as a simple test of reading/writing
void invert_image(ImageData* image){
    int total_sz;
    Pixel p;

    total_sz = (image->x)*(image->y);
    for(int i=0; i<total_sz; i++) {
        p = image->data[i];
        p.r = 255-p.r;
        p.g = 255-p.g;
        p.b = 255-p.b;
        image->data[i] = p;
    }
}


int main(int argc,char **argv) {
    FILE* fptr;
    ImageData image;

   // Check arguments
   if (argc < 2) {
      fprintf(stderr,"Usage: %s filename\n",argv[0]);
      exit(-1);
   }

   /* Open file */
   if ((fptr = fopen(argv[1],"r")) == NULL) {
      fprintf(stderr,"Unable to open BMP file \"%s\"\n",argv[1]);
      exit(-1);
   }

   if(read_bitmap(fptr, &image) != 0) {
       fprintf(stderr, "Couldn't read image");
       exit(-1);
   }
   fclose(fptr);

   invert_image(&image);

   if ((fptr = fopen("inverted.bmp","w")) == NULL) {
      fprintf(stderr,"Unable to write output\n");
      exit(-1);
   }

   write_bitmap(fptr, &image);
   free(image.data);

   return 0;
}