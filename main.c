#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test{
	int i1;
	int i2;
	double d;
	char i3;
};

double
average (int count, ...)
{
	va_list ap;
	int i;
	double av = 0;
	va_start(ap,count);
	for(i = 0;i <count; i++)
		av+= va_arg(ap,double);
	va_end(ap);
	return av/count;
}


void*
alloc(const char * format, ...){
	va_list ap;
	int i;
	int licznik=0;

	struct test *p;
	p = malloc(sizeof(*p));
	if(p==NULL){
		fprintf(stderr,"Brak pamieci");
		return NULL;
	}

	va_start(ap,format);
	for(i=0;i<strlen(format);i++){
		if(format[i]=='i'){
			if(licznik==0){
				p->i1 = va_arg(ap,int);
				}
			else if(licznik==1){
				p->i2 = va_arg(ap,int);
				}
			else if(licznik==2){
				p->i3= va_arg(ap,int);
				}
			licznik++;
		}
		else if(format[i]=='d'){
			p->d = va_arg(ap,double);
			}
		else if(format[i]=='c'){
			p->i3 = va_arg(ap,int);
			}
	}
	va_end(ap);
	return p;
}

int
main(int argc, char ** argv){
	struct test *p = alloc("iidi",33,44,3.14,55);
	if(p==NULL)
		return EXIT_FAILURE;
	printf("%d %d %f %d\n",p->i1,p->i2,p->d,p->i3);
	return 0;
}
