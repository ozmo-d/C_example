basic_matrix : basic_matrix.c basic_matrix.h
	gcc -o basic_matrix basic_matrix.c -std=c11

bitmap.o : bitmap.c bitmap.h
	gcc -c bitmap.c -std=c11

bitmap_test : bitmap.c bitmap.h bitmap_test.c bitmap.o
	gcc -o bitmap_test.exe bitmap_test.c bitmap.o -std=c11