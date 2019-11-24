frecpalhilo: frecpalhilo.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o 
	gcc -o frecpalhilo -pthread frecpalhilo.o utilities.o hash.o str_hash.o str_list.o str_ht_list.o hash_list.o 

frecpalhilo.o: frecpalhilo.c utilities.h hash.h str_hash.h str_list.h 
	gcc -c -ansi -Wpedantic -pthread frecpalhilo.c

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

clean:
	if find *.o; then rm *.o; fi
	if find frecpalhilo; then rm frecpalhilo; fi