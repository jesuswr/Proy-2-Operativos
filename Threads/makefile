pruebrecdir: pruebas_recorrer_dir.o utilities.o hash.o hash_list.o
	gcc -o pruebrecdir pruebas_recorrer_dir.o utilities.o hash.o hash_list.o

pruebas_recorrer_dir.o: pruebas_recorrer_dir.c utilities.h hash.h hash_list.h
	gcc -c -ansi -Wpedantic pruebas_recorrer_dir.c

utilities.o: utilities.c utilities.h
	gcc -c -ansi -Wpedantic utilities.c


hash_list.o : hash_list.c hash_list.h
	gcc -c -ansi -Wpedantic hash_list.c

hash.o : hash.c hash.h hash_list.h
	gcc -c -ansi -Wpedantic hash.c

# Makefile para probar la tabla de hash
#prueb : pruebas.o hash_list.o hash.o
#	gcc -o prueb pruebas.o hash_list.o hash.o

#pruebas.o : pruebas.c hash_list.h hash.h
#	gcc -c -ansi -Wpedantic pruebas.c

#hash_list.o : hash_list.c hash_list.h
#	gcc -c -ansi -Wpedantic hash_list.c

#hash.o : hash.c hash.h hash_list.h
#	gcc -c -ansi -Wpedantic hash.c