# Add a header later

clean:
	rm -f mem_allocate

test:
	# Compile everything for now
	gcc -o mem_allocate mem_test.c

	# Add conditions later to check if my_malloc file is included
	# https://stackoverflow.com/questions/5553352/how-do-i-check-if-file-exists-in-makefile-so-i-can-delete-it

	./mem_allocate

test_my_malloc:
	
	gcc -o my_malloc my_malloc.c test_my_malloc.c

	./my_malloc