#include"Makefile"
objects= 指针 const const数组 cin.read putback 替身 校门外的树

CC=g++
CFLAGS=

all: $(objects)
$(objects): %: %.cpp
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(objects)
