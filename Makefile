TESTP=test-malloc test-calloc test-realloc test-new
EXE=mydebug.so $(TESTP)

all: $(EXE)

mydebug.so: mydebug.c
	gcc -shared -fpic -nostdlib mydebug.c -o mydebug.so -ldl

test-malloc: test-malloc.c
	gcc -o test-malloc test-malloc.c

test-calloc: test-calloc.c
	gcc -o test-calloc test-calloc.c

test-realloc: test-realloc.c
	gcc -o test-realloc test-realloc.c

test-new: test-new.cpp
	g++ -o test-new test-new.cpp

test:
	LD_PRELOAD=./mydebug.so ./test-malloc
	LD_PRELOAD=./mydebug.so ./test-calloc
	LD_PRELOAD=./mydebug.so ./test-realloc
	LD_PRELOAD=./mydebug.so ./test-new

clean:
	rm $(EXE)

clean-test:
	rm $(TESTP)

