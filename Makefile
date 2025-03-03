test: test
	./list_test

list.o: list.c list.h
	gcc -c list.c -o list.o

list.a: list.o
	ar rc list.a list.o

list_test.o: list_test.c 
	gcc -c list_test.c -o list_test.o

list_test: list_test.o list.a
	gcc -static -o list_test list_test.o list.a

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`
	
check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry run --Werror

clear:
	rm -rf *.o *.a *_test


