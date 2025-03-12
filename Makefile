test: stack_test
	./stack_test

stack.o: stack.c stack.h
	gcc -c stack.c -o stack.o

stack.a: stack.o
	ar rc stack.a stack.o

stack_test.o: stack_test.c 
	gcc -c stack_test.c -o stack_test.o

stack_test: stack_test.o stack.a
	gcc -static -o stack_test stack_test.o stack.a

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`
	
check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

clear:
	rm -rf *.o *.a *_test

