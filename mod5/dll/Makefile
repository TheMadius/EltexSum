#	LD_LIBRARY_PATH=$(pwd)
#	export LD_LIBRARY_PATH

LIB:
	gcc -c main.c add.c multi.c
	ar rc libmat.a add.o multi.o
	ranlib libmat.a
	gcc main.o -L. -lmat -o rezult
S_DLL:
	gcc -fPIC -c add.c multi.c
	gcc -shared multi.o add.o -o libmat.so
	gcc main.c -L. -lmat -o rezultdll
DLL:
	gcc -fPIC -c add.c multi.c
	gcc -shared add.o multi.o -o libmat.so
	gcc main2.c -o rezult2dll -ldl
cleanLib:
	rm add.o main.o multi.o rezult libmat.a
cleanDll:
	rm add.o multi.o rezultdll libmat.so	
cleanDll2:
	rm add.o multi.o rezult2dll libmat.so