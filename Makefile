test: 
	@for test in $(shell find . -regex '.*_test'); do \
        echo "Running: $$test"; \
        ./$$test; \
    done

fmt: 
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"`
	
check_fmt:
	clang-format -style=Microsoft -i `find -regex ".+\.[ch]"` --dry-run --Werror

clear:
	rm -rf *.o *.a *_test
