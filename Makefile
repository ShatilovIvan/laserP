test: roots_test
	./roots_test

roots.o: roots.c roots.h
	gcc -c roots.c -o roots.o

roots.a: roots.o
	ar rc roots.a roots.o

roots_test.o: roots_test.c 
	gcc -c roots_test.c -o roots_test.o

roots_test: roots_test.o roots.a
	gcc -static -o roots_test roots_test.o roots.a -lm

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`
	
check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

clear:
	rm -rf *.o *.a *_test


