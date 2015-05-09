all:
	gcc -O3 -fPIC -shared -o bitmap_filter.so bitmap_filter.c
