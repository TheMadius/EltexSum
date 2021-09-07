#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int main(int argc,char** argv)
{
	void * lib_handler;
    int (*multi)(int,int);
    int (*add)(int,int);
	
	lib_handler = dlopen("libmat.so",RTLD_LAZY);
	
	if(!lib_handler)
	{
		fprintf(stderr,"dlopen error");
		return -1;
	}
	
	multi = dlsym(lib_handler,"multi");
	add = dlsym(lib_handler,"add");
	
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("Res add = %d\nRes multi = %d\n",add(a,b), multi(a,b));
	
	dlclose(lib_handler);
	
}