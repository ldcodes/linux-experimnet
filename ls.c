
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <string.h>// strcmp
#include <stdio.h>
#include <grp.h>
/*
ls 
ls -a 
ls -l
ls -a -l
ls -a aaa
ls -l aaa
ls -a -l aaa
ls -r aaa



*/
int judge(char *);
void showinf(struct dirent  a,char* n);
int do_dir(char * name , int a ,int l ,int r);
struct passwd* idtoName(int id);
void showmode(int n);
int main(int ac ,char *n[]){
	int arg[3]={0,0,0},result;//,a=0,l=1,r=2,
	char  name[100];
	strcpy(name,".");
	if(ac == 1){
		;
	}else if(ac ==2){
		
		result =judge(n[1]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[1]);
		}
		
	}else if(ac == 3){
		// 1
		result =judge(n[1]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[1]);
		}
		//2
		result =judge(n[2]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[2]);
		}


	}else if(ac == 4){
		// 1
		result =judge(n[1]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[1]);
		}
		//2
		result =judge(n[2]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[2]);
		}
		// 3
		result =judge(n[3]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[3]);
		}
	}else if(ac ==5){
		// 1
		result =judge(n[1]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[1]);
		}
		//2
		result =judge(n[2]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[2]);
		}
		// 3
		result =judge(n[3]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[3]);
		}
		//4
		result =judge(n[4]);
		if(result != -1){
			arg[result] =1;
		}else{
			strcpy(name,n[4]);
		}
	}else{
		printf("too much arg \n");
		return 0;
	}
	//printf("dir :%s, a = %d, l= %d, r =%d ",name,arg[0],arg[1],arg[2]);
	do_dir(name,arg[0],arg[1],arg[2]);
	return 0;
}

/*
 a,l, r =0 without
  a,l, r = 1, with
  name :1 aaa/
        2 /home/computer/CloudMusic 
*/
/*
dir 0
a  1
l 2
r 3
*/
int judge(char * n){
		
			if(strcmp(n,"-a")==0){
				return 0;
			}else if(strcmp(n,"-l")==0){
				return 1;
			}else if(strcmp(n ,"-R")==0){
				return 2;
			}else{
				return -1;		
		}
		

}
int do_dir(char * nam , int a ,int l ,int r){
	DIR * dir;
	struct dirent * d,list[200] ,subdir[100] ;
	int num = 0 ,i=0,j =0,dirnum =0;
	char next[100] ,name[100] ;
	strcpy(name,nam);
	//printf(" will to do %s\n",name);
	fflush(NULL);
	if( (dir = opendir(name))== NULL){
		perror("can not open");
		return 0;
	}else{
		while( (d = readdir(dir)) != NULL){
			list[i] =*d;
			if(d->d_type ==DT_DIR){
			        subdir[dirnum] =*d;
				dirnum++;			
			}
			i++;
		}
	}
	closedir(dir);
	//printf(" will to do %s i=%d\n",name,i);
	//check the name ,judge if need to change dir
	if(strncmp(name,"/",1)==0)
		chdir(name);
			
	if(r == 1){
		printf("%s:\n",getcwd(NULL, 0));
	}
	
	if(l == 0){
		while(j <i){ // i = 0  -a ,i =1 non-a;
			if(a==1 || list[j].d_name[0] != '.')
				printf("%s\t",list[j].d_name);	
			j++;
		}
	}else{ 
		while(j <i){ // i = 0  -a ,i =1 non-a;
			if(a==1 || list[j].d_name[0] != '.')
				showinf(list[j],name);
			j++;
		}
	}
	if(r == 1){
		for(i = 0; i<dirnum;i++)
			//memset(next, 0, sizeof(next));
			if(strncmp(subdir[i].d_name,".",1)!=0){
				//printf("\n this dir %s\n",name);
				//printf("\n aim  dir %s\n",next);
				strcpy(next,name);
				strcat(next,"/");
				//printf("\n aim  dir %s\n",next);
				//printf("\n sub0s dir %s\n",subdir[i].d_name);
				strcat(next,subdir[i].d_name);
				//printf("\n aim  dir %s\n",next);
				//fflush(NULL);
				printf("\n\n");
				do_dir(next , a , l , r);

		}
	}
	return 0;
}

void showinf(struct dirent dir,char * name){
        char *buff  ;//= getcwd(NULL, 0);// get current dir 
	struct  stat buf;
	struct passwd* pw,*u;
        struct group *g ;
        char  tt[100] = "",*ctime();
	//printf("this is %s\n",dir.d_name);
        fflush(NULL);
       /* if(strncmp(name,"/",1)!= 0 ){
	       // strcpy(tt,buff);
                // strcat(tt,".");
               
 		strcat(tt,"/");
	}*/
	strcat(tt,name);
	strcat(tt,"/");
        strcat(tt,(char*)dir.d_name);       
	stat(tt,&buf);/// bug !!!!!!!!!!!!!!!!!!      
	showmode(buf.st_mode);
	printf(" %-4d ",(int)buf.st_nlink);
	printf("%s %s ",getpwuid(buf.st_uid)->pw_name ,getgrgid(buf.st_gid)->gr_name);  
	printf("%9d %.12s %s\n",(int)buf.st_size,4+ctime((const time_t *) &(buf.st_mtim)),dir.d_name);
}

void showmode(int n){
	char str[10]  ="----------";
	if(S_ISDIR(n)) str[0] = 'd';
	if(S_IRUSR & n) str[1] ='r';
	if(S_IWUSR & n) str[2] ='w';
	if(S_IXUSR & n) str[3] ='x';

	if(S_IRGRP & n) str[4] ='r';
	if(S_IWGRP & n) str[5] ='w';
	if(S_IXGRP & n) str[6] ='x';

	if(S_IROTH & n) str[7] ='r';
	if(S_IWOTH & n) str[8] ='w';
	if(S_IXOTH & n) str[9] ='x';
	printf("%.9s ",str);
}
/*
struct passwd* idtoName(int id)
{
	struct passwd pw, *pwp;
	int i,b=4096;

	char buf[b];
	setpwent();
        
	while (1) {
		i = getpwent_r(&pw, buf, b, &pwp);
		if(i){
			endpwent();
			return NULL;
		}
		if (id == pwp->pw_uid){
                       endpwent();
			return pwp;
                }
	}
}
*/
