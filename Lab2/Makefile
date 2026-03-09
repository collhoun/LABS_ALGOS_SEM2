# Как сделать проверку на наличие файлов в папке data_samples и запускать скрипт для их создания, если их нет?\
# тоже самое для папки tests, чтобы при запуске make tests, если в папке tests нет тестов, то они создавались автоматически
data_samples:
	python src/data_creators/create_samples.py

data_tests:
	python tests/tests_data_creators.py

# -DTEST - для того, чтобы в тестах не выполнялась функция main, а выполнялись только тесты
tests: data_tests
	gcc -DTEST -o test tests/test.c src/main.c

clean_tests: tests
	rm -f test

clean:
	rm -f main

run: data_samples
	gcc -o main src/main.c