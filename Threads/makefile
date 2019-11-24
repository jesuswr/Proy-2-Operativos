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


#pruebstrlist: prueba_str_list.o str_list.o
#	gcc -o pruebstrlist prueba_str_list.o str_list.o

#prueba_str_list.o: prueba_str_list.c str_list.h
#	gcc -c prueba_str_list.c 

#str_list.o: str_list.c str_list.h
#	gcc -c str_list.c

#pruebassort: pruebas_sort.o utilities.o hash.o hash_list.o
#	gcc -o pruebassort pruebas_sort.o utilities.o hash.o hash_list.o

#pruebas_sort.o: pruebas_sort.c utilities.h
#	gcc -c pruebas_sort.c

#utilities.o: utilities.c utilities.h hash.h
#	gcc -c -ansi -Wpedantic utilities.c

#hash_list.o : hash_list.c hash_list.h
#	gcc -c -ansi -Wpedantic hash_list.c

#hash.o : hash.c hash.h hash_list.h
#	gcc -c -ansi -Wpedantic hash.c

#pruebasstrhash: pruebasstrhash.o str_hash.o str_ht_list.o
#	gcc -o pruebasstrhash pruebasstrhash.o str_hash.o str_ht_list.o

#pruebasstrhash.o: pruebasstrhash.c str_hash.h str_ht_list.h
#	gcc -c -ansi -Wpedantic pruebasstrhash.c

#str_hash.o: str_hash.c str_hash.h str_ht_list.h
#	gcc -c -ansi -Wpedantic str_hash.c

#str_ht_list.o: str_ht_list.c str_ht_list.h
#	gcc -c -ansi -Wpedantic str_ht_list.c

#pruebastrlist: pruebas_lista_string.o str_ht_list.o
#	gcc -o pruebastrlist pruebas_lista_string.o str_ht_list.o

#pruebas_lista_string.o: pruebas_lista_string.c str_ht_list.h
#	gcc -c -ansi -Wpedantic pruebas_lista_string.c

#str_ht_list.o: str_ht_list.c str_ht_list.h
#	gcc -c -ansi -Wpedantic str_ht_list.c

# MAKEFILE PARA PROBAR EL RECORRIDO DE DIRECTORIOS
#pruebrecdir: pruebas_recorrer_dir.o utilities.o hash.o hash_list.o
#	gcc -o pruebrecdir pruebas_recorrer_dir.o utilities.o hash.o hash_list.o

#pruebas_recorrer_dir.o: pruebas_recorrer_dir.c utilities.h hash.h hash_list.h
#	gcc -c -ansi -Wpedantic pruebas_recorrer_dir.c

#utilities.o: utilities.c utilities.h
#	gcc -c -ansi -Wpedantic utilities.c


#hash_list.o : hash_list.c hash_list.h
#	gcc -c -ansi -Wpedantic hash_list.c

#hash.o : hash.c hash.h hash_list.h
#	gcc -c -ansi -Wpedantic hash.c

# Makefile para probar la tabla de hash
#prueb : pruebas.o hash_list.o hash.o
#	gcc -o prueb pruebas.o hash_list.o hash.o

#pruebas.o : pruebas.c hash_list.h hash.h
#	gcc -c -ansi -Wpedantic pruebas.c

#hash_list.o : hash_list.c hash_list.h
#	gcc -c -ansi -Wpedantic hash_list.c

#hash.o : hash.c hash.h hash_list.h
#	gcc -c -ansi -Wpedantic hash.c