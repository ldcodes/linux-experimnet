#include <stdio.h>
#include <unistd.h>//implicit declaration of function 'read' is invalid in
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int main(int ac ,char * av[]){

	int fd,fo,rn ;
	char buff[1024];
	printf("%d\n",ac);
	if(ac <2){
		perror("lack name\n");
		exit(0);
	}
	if ((fd=open(av[1],O_RDONLY))==-1){

		perror("can not open\n");
		exit(0);
	}  

         while((rn=read(fd,buff,1024))>0)
                printf("%*s",rn-1,buff);
	// if( (fo= open()) ==3 )
	//if((fd=open("h.c")))
}
