#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>// write
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
int main(int ac ,char * av[]){
	int fi,fo,rn;
	char buff[1024];

	//umask(0000);
	if(ac != 3){
		perror("need 3 parameter,like mycp sour_file ,aim_file");
		exit(0);
	}
	if((fi = open(av[1],O_RDONLY))==-1 ){
		perror("can not open souce file");
		exit(0); 
	}
	if((fo = open(av[2],O_WRONLY|O_CREAT,0640))<0 ){
		perror("aim file error");
		exit(0);
	}
	while( (rn= read (fi,buff,1024)) >0  ){
		write(fo,buff,rn);

	}	
	close(fo);
	close(fi);
return 0;

}
