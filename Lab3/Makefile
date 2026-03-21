# Компиляция объектных файлов основных модулей
stack.o: src/stack.c src/stack.h
	gcc -c src/stack.c -o stack.o

validation.o: src/validation.c src/validation.h src/stack.h
	gcc -c src/validation.c -o validation.o

tokenization.o: src/tokenization.c src/tokenization.h src/validation.h src/stack.h
	gcc -c src/tokenization.c -o tokenization.o

# Компиляция объектных файлов дерева и калькулятора
tree.o: src/tree.c src/tree.h src/tree_stack.h src/tokenization.h
	gcc -c src/tree.c -o tree.o

tree_stack.o: src/tree_stack.c src/tree_stack.h src/tree.h
	gcc -c src/tree_stack.c -o tree_stack.o

calculator.o: src/calculator.c src/calculator.h src/tree.h src/tree_stack.h
	gcc -c src/calculator.c -o calculator.o

# Компиляция объектных файлов тестов
test_expr.o: tests/test_expr.c src/validation.h
	gcc -c tests/test_expr.c -o test_expr.o

test_stack.o: tests/test_stack.c src/stack.h
	gcc -c tests/test_stack.c -o test_stack.o

test_tokenization.o: tests/test_tokenization.c src/tokenization.h src/validation.h src/stack.h
	gcc -c tests/test_tokenization.c -o test_tokenization.o

test_tree_stack.o: tests/test_tree_stack.c tests/test_tree_stack.h src/tree_stack.h src/tree.h
	gcc -c tests/test_tree_stack.c -o test_tree_stack.o

test_tree.o: tests/test_tree.c tests/test_tree.h src/tree.h src/tokenization.h src/calculator.h
	gcc -c tests/test_tree.c -o test_tree.o

test_calculator.o: tests/test_calculator.c tests/test_calculator.h src/calculator.h src/tree.h
	gcc -c tests/test_calculator.c -o test_calculator.o

test.o: tests/test.c
	gcc -c tests/test.c -o test.o

# Сборка исполняемого файла тестов (здесь происходит связывание)
all_tests: test.o test_expr.o test_stack.o test_tokenization.o test_tree_stack.o test_tree.o test_calculator.o stack.o validation.o tokenization.o tree.o tree_stack.o calculator.o
	gcc -o all_tests test.o test_expr.o test_stack.o test_tokenization.o test_tree_stack.o test_tree.o test_calculator.o stack.o validation.o tokenization.o tree.o tree_stack.o calculator.o

run: src/calculator.c src/tree.c src/tree_stack.c src/tokenization.c src/validation.c src/stack.c
	gcc -o run src/main.c src/calculator.c src/tree.c src/tree_stack.c src/tokenization.c src/validation.c src/stack.c


# Очистка
clean_tests:
	rm -f *.o

clean_exe:
	rm -f *.exe

