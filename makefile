COMPILER = gcc
ARGS = -Wall -Wextra -std=c11 -O3
PWD = $(shell pwd)
NAME = sha
ifeq ($(OS),Windows_NT)
	LIBNAME = lib$(NAME).dll
	EXENAME = hashverif.exe
else
	LIBNAME = lib$(NAME).so
	EXENAME = hashverif
endif

all: $(LIBNAME)

$(LIBNAME): sha1.o sha256_internal.o sha224.o sha256.o sha512_internal.o sha384.o sha512.o sha512_224.o sha512_256.o hashtests.o
	$(COMPILER) $(ARGS) -shared -Wl,-soname,$(LIBNAME) -o $(LIBNAME) sha1.o sha256_internal.o sha224.o sha256.o sha512_internal.o sha384.o sha512.o sha512_224.o sha512_256.o hashtests.o

sha1.o: sha1.c
	$(COMPILER) $(ARGS) -c -fPIC sha1.c

sha256_internal.o: sha256_internal.c
	$(COMPILER) $(ARGS) -c -fPIC sha256_internal.c

sha512_internal.o: sha512_internal.c
	$(COMPILER) $(ARGS) -c -fPIC sha512_internal.c

sha224.o: sha224.c
	$(COMPILER) $(ARGS) -c -fPIC sha224.c

sha256.o: sha256.c
	$(COMPILER) $(ARGS) -c -fPIC sha256.c

sha384.o: sha384.c
	$(COMPILER) $(ARGS) -c -fPIC sha384.c

sha512.o: sha512.c
	$(COMPILER) $(ARGS) -c -fPIC sha512.c

sha512_224.o: sha512_224.c
	$(COMPILER) $(ARGS) -c -fPIC sha512_224.c

sha512_256.o: sha512_256.c
	$(COMPILER) $(ARGS) -c -fPIC sha512_256.c

hashtests.o: hashtests.c
	$(COMPILER) $(ARGS) -c -fPIC hashtests.c

clean:
	rm -f *.o $(LIBNAME) $(EXENAME)

run-hashverif: build-hashverif
	export LD_LIBRARY_PATH=$$(pwd):$$LD_LIBRARY_PATH; ./$(EXENAME)

$(EXENAME): $(LIBNAME) hashverif.o
	$(COMPILER) $(ARGS) -o $(EXENAME) -L$(PWD) hashverif.o -l$(NAME)

hashverif.o: hashverif.c
	$(COMPILER) $(ARGS) -c hashverif.c

commit: clean
	git add *
	git commit -a