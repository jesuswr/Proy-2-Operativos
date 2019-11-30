all: frecpalproc count_words get_txt frecpalhilo

frecpalhilo: frecpalhilo.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o
	gcc -o frecpalhilo -pthread frecpalhilo.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o

frecpalhilo.o: frecpalhilo.c utilities.h hash.h str_hash.h str_list.h 
	gcc -c -ansi -Wpedantic -pthread frecpalhilo.c

frecpalproc: frecpalproc.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o
	gcc -o frecpalproc -pthread -lpthread frecpalproc.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o

frecpalproc.o: frecpalproc.c utilities.h hash.h str_hash.h str_list.h 
	gcc -c -ansi -Wpedantic -pthread -lpthread frecpalproc.c

count_words: count_words.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o
	gcc -o count_words -pthread -lpthread count_words.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o

count_words.o: count_words.c utilities.h hash.h str_hash.h str_list.h error_handler.h
	gcc -c -ansi -Wpedantic -pthread -lpthread count_words.c

get_txt: get_txt.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o
	gcc -o get_txt -pthread -lpthread get_txt.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o error_handler.o

get_txt.o: get_txt.c utilities.h hash.h str_hash.h str_list.h error_handler.h
	gcc -c -ansi -Wpedantic -pthread -lpthread get_txt.c

utilities.o: utilities.c utilities.h hash.h
	gcc -c -ansi -Wpedantic utilities.c

hash.o : hash.c hash.h hash_list.h
	gcc -c -ansi -Wpedantic hash.c

str_hash.o: str_hash.c str_hash.h str_ht_list.h
	gcc -c -ansi -Wpedantic str_hash.c

str_list.o: str_list.c str_list.h
	gcc -c str_list.c

str_ht_list.o: str_ht_list.c str_ht_list.h
	gcc -c -ansi -Wpedantic str_ht_list.c

hash_list.o : hash_list.c hash_list.h
	gcc -c -ansi -Wpedantic hash_list.c

error_handler.o : error_handler.c error_handler.h
	gcc -c -ansi -Wpedantic error_handler.c

clean:
	if find *.o; then rm *.o; fi
	if find frecpalproc; then rm frecpalproc; fi
	if find get_txt; then rm get_txt; fi
	if find count_words; then rm count_words; fi
	if find frecpalhilo; then rm frecpalhilo; fi