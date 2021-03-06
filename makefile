CC=g++-4.8
CFLAGS=-Wall -std=c++11 -c
BUILDDIR=build/
SRC=src/
HEAD=src/headers/
TARGET=md5awsum

all: build md5lib md5hash pugixml rainbow_table repository_manager input_parser md5awsumsrc main $(TARGET)

$(TARGET): $(BUILDDIR)md5lib.o $(BUILDDIR)md5hash.o $(BUILDDIR)pugixml.o $(BUILDDIR)rainbow_table.o $(BUILDDIR)repository_manager.o $(BUILDDIR)input_parser.o $(BUILDDIR)md5awsum.o $(BUILDDIR)main.o
	@printf 'building executable...\t\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)md5hash.o $(BUILDDIR)pugixml.o $(BUILDDIR)rainbow_table.o $(BUILDDIR)repository_manager.o $(BUILDDIR)input_parser.o $(BUILDDIR)md5awsum.o $(BUILDDIR)main.o -o $(TARGET)
	@echo 'complete.'
	@echo 'Enjoy your program!!'

build:
	@printf 'creating build directory...\t'
	@mkdir $(BUILDDIR)
	@echo 'complete.'

md5lib: build $(SRC)md5lib.cpp $(HEAD)md5lib.h
	@printf	'building md5lib...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5lib.cpp -o $(BUILDDIR)md5lib.o
	@echo 'complete.'

md5hash: build $(SRC)md5hash.cpp $(HEAD)md5hash.h $(HEAD)md5lib.h
	@printf 'building md5hash...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5hash.cpp -o $(BUILDDIR)md5hash.o
	@echo 'complete.'

pugixml: build $(SRC)pugixml.cpp $(HEAD)pugixml.hpp
	@printf 'building pugixml...\t\t'
	@$(CC) $(CFLAGS) $(SRC)pugixml.cpp -o $(BUILDDIR)pugixml.o
	@echo 'complete.'

rainbow_table: build $(SRC)rainbow_table.cpp $(HEAD)rainbow_table.h $(HEAD)pugixml.hpp
	@printf 'building rainbow_table...\t'
	@$(CC) $(CFLAGS) $(SRC)rainbow_table.cpp -o $(BUILDDIR)rainbow_table.o
	@echo 'complete.'

repository_manager: build $(SRC)repository_manager.cpp $(HEAD)repository_manager.h $(HEAD)rainbow_table.h $(HEAD)md5hash.h
	@printf 'building repository_manager...\t'
	@$(CC) $(CFLAGS) $(SRC)repository_manager.cpp -o $(BUILDDIR)repository_manager.o
	@echo 'complete.'

input_parser: build $(SRC)input_parser.cpp $(HEAD)md5awsum.h
	@printf 'building input_parser...\t'
	@$(CC) $(CFLAGS) $(SRC)input_parser.cpp -o $(BUILDDIR)input_parser.o
	@echo 'complete.'

md5awsumsrc: build $(SRC)md5awsum.cpp $(HEAD)md5awsum.h $(HEAD)rainbow_table.h $(HEAD)md5hash.h $(HEAD)repository_manager.h
	@printf 'building md5awsum...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5awsum.cpp -o $(BUILDDIR)md5awsum.o
	@echo 'complete.'

main: build $(SRC)main.cpp $(HEAD)md5awsum.h $(SRC)input_parser.cpp
	@printf 'building main...\t\t'
	@$(CC) $(CFLAGS) $(SRC)main.cpp -o $(BUILDDIR)main.o
	@echo 'complete.'

md5libtest: build tempfiles $(SRC)md5libtest.cpp $(HEAD)md5lib.h
	@printf 'building md5libtest...\t\t'
	@$(CC) $(CFLAGS) $(SRC)md5libtest.cpp -o $(BUILDDIR)md5libtest.o
	@echo 'complete.'
	@printf 'building testmd5 executable...\t'
	@$(CC) $(BUILDDIR)md5lib.o $(BUILDDIR)md5libtest.o -o testmd5
	@echo 'complete.'

tempfiles:
	@printf 'building testfiles...\t\t'
	@echo 'this is a test file!!!' > /tmp/.testfile
	@perl -e 'for (my $$i=0; $$i <= 1000000; $$i++) { print "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n"; }' > /tmp/.testfile
	@printf '' > /tmp/.emptyfile
	@echo 'complete.'

install:
	@printf 'installing md5awsum in /usr/bin... '
	@mv $(TARGET) /usr/bin
	@echo 'complete.'

clean:
	@printf 'deleting .o files...\t\t'
	@rm $(BUILDDIR)*.o
	@echo 'complete.'
	@printf 'deleting build directory...\t'
	@rm -r $(BUILDDIR)
	@echo 'complete.'
	@printf 'deleting local hash table...\t'
	@rm -r ~/.md5awsum/
	@echo 'complete.'
	@echo 'Clean complete -> please delete md5awsum from the location it is stored in.'
