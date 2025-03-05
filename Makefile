test: clear integral_test
	./integral_test

integral.o: integral.c integral.h
	gcc -c integral.c -o integral.o

integral.a: integral.o
	ar rc integral.a integral.o

integral_test.o: integral_test.c 
	gcc -c integral_test.c -o integral_test.o

integral_test: integral_test.o integral.a
	gcc -static -o integral_test integral_test.o integral.a -lm

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`
	
check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

clear:
	rm -rf *.o *.a *_test


