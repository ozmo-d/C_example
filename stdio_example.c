#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Array{
    float* data;
    int n;
} Array;

int read_data(FILE *fp, Array* array) {
   int n_char = 0;
   float val = 0.0;
   while(fscanf(fp, "%f", &val) == 1) {
       n_char++;
   }
   printf("found %d chars\n", n_char);

   array->data = malloc(n_char*sizeof(float));
   array->n = n_char;

   rewind(fp);
   for(int i=0; i<n_char; i++) {
      fscanf(fp, "%f", &(array->data[i]));
   }
}

float variance(float* data, int n)
{
    float sum = 0;
    for(int i=0; i<n; i++) {
        sum += data[i];
    }
    sum = sum/n;

    float var = 0;
    float diff = 0;
    for(int i=0; i<n; i++) {
        diff = (data[i]-sum);
        diff *= diff;
        var += diff;
    }
    var = var/(n);
    return var;
}

int main() {
    float res;
//   float data[] = {1,2,3,1,2,3,4,5,3,4,0,4};
//    int n =  12;

    Array array;
    FILE* fp = fopen("values.txt", "r");
    read_data(fp, &array);
    fclose(fp);

    res = variance(array.data, array.n);
    printf("result: %3.3f\n", res);
}
