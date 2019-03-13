    #include <stdio.h>
    #include <dirent.h>   
    #include <string.h>   
	#include <stdlib.h>
	#include <unistd.h> 
	#include <fcntl.h> 
	#define _GNU_SOURCE
	#include <sys/stat.h>
	#include <sys/syscall.h>
	#include <limits.h>


       #define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

       struct linux_dirent {
           long           d_ino;
           off_t          d_off;
           unsigned short d_reclen;
           char           d_name[];
       };
	#define BUF_SIZE 1024
       
	char line1[80];

	void getLine(){
		char next;// = getchar();	
			int i=0;
			memset(line1,0,255);
			while(next=getchar()){
				if(next!='\n' && next!='\0'){
					line1[i]=next;
					i++;
				}
				else break;
			}
	}



   static char*  currentdir = "/home/aigerim/Desktop/systemprog/Bash-system-programming-project-" ;
    char* filename1 = "textfile1.txt";
        char *filename2="";
	void printDirInfo(){
           int fd, nread;
           char buf[BUF_SIZE];
           struct linux_dirent *d;
           int bpos;
           char d_type;

           fd = open(currentdir, O_RDONLY | O_DIRECTORY);
           if (fd == -1)
               handle_error("open");

           for ( ; ; ) {
               nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
               if (nread == -1)
                   handle_error("getdents");

               if (nread == 0)
                   break;

               printf("d_name              file_type\n\n");
               for (bpos = 0; bpos < nread;) {
                   d = (struct linux_dirent *) (buf + bpos);
                   
                   d_type = *(buf + bpos + d->d_reclen - 1);
                   printf("%-20s",  d->d_name);
                   printf("%s\n", (d_type == DT_REG) ?  "regular" :
                                    (d_type == DT_DIR) ?  "directory" :
                                    (d_type == DT_FIFO) ? "FIFO" :
                                    (d_type == DT_SOCK) ? "socket" :
                                    (d_type == DT_LNK) ?  "symlink" :
                                    (d_type == DT_BLK) ?  "block dev" :
                                    (d_type == DT_CHR) ?  "char dev" : "???");
                   
                   bpos += d->d_reclen;
               }
           }

     
	}

char filepath[80];
char filepath2[80];
	
	void catStr(){
		strcpy(filepath,"");
		strcat(filepath,currentdir);
		strcat(filepath,"\\");
		strcat(filepath,filename1);
		strcpy(filepath2,"");
		strcat(filepath2,currentdir);
		strcat(filepath2,"\\");
		strcat(filepath2,filename2);
	}
	
	void PrintFileInfo(){
	    printf("\n");
		char kek[80];
		scanf("%s",kek);
		printf("File content is below:\n");
		int fd; 

    	char buf2[INT_MAX]; 
        
 		fd= open(kek, O_RDWR); 
        while(read(fd, buf2, INT_MAX)!=EOF)     
    	write(1, buf2, read(fd, buf2, INT_MAX)); 
  		

    	close(fd);
	}



	void printHelp(){

		    char ch, file_name[25];
		    FILE *fp;
			int fd; 
			char buf2[1000]; 
        
			fd= open("commands.txt", O_RDWR); 
            printf("Below is all possible commands:\n"); 
			write(1, buf2, read(fd, buf2, 1000)); 
  

			close(fd);
	
	}
	char compilePath[80] ;
	void concatPathToCompile(){
		catStr();
		memset(compilePath,0,255);
		strcat(compilePath,"cd ");
		strcat(compilePath,currentdir);
		strcat(compilePath," && gcc ");
		strcat(compilePath,filename1);
		strcat(compilePath," -o a && ./a");
	}

	void compile(){
		concatPathToCompile();
		system(compilePath);
	}
	void copy(){
		char kek1[80],kek2[80];
		scanf("%s",kek1);
		scanf("%s",kek2);
		int filedesc = open("testfile.txt", O_WRONLY | O_APPEND);
 
    	if (filedesc < 0) {
        	write(2, "There was an error writing to testfile.txt\n", 43);
   		}
 
    	if (write(filedesc, "This will be output to testfile.txt\n", 36) != 36) {
       		write(2, "There was an error writing to testfile.txt\n", 43);
       		
   		}
	}	

    int main (int c, char *argv[]) {

		printf("Welcome!\n" );
		printHelp();
		char option[80];
		while(1){
			printf("\n%s : ",currentdir);	
			scanf("%s",option);


		 	if (strcmp(option,"ls")==0) {

		     	printf("\nBelow is content of current directory:\n\n" );
		    	printDirInfo();

		   	 }
		    else if(strcmp(option,"cd")==0){
		    	char kek[80];
		    	scanf("%s",kek);
		    	currentdir = kek;
		    	printf("this is new currentdir%s\n",currentdir );
		    	printf("current directory successfully changed!" );
		    
		    	
		    }    
		     else if(strcmp(option,"cat")==0){
				PrintFileInfo();
			}

			 else if(strcmp(option,"help")==0){
		     	printHelp();
			}

			 else if(strcmp(option,"rm")==0){
			 	
			 	char kek[80];
		     	scanf("%s",kek);
		     	int rm = unlink(kek);
		   		if(rm==0)
		   		printf("File %s was deleted successfully!\n",kek );		     	
			}
			 else if(strcmp(option,"0")==0){
			 	printf("Bye!\n");
			 	break;
			}
			 else if(strcmp(option,"touch")==0){
			 	char kek[80];
		     	scanf("%s",kek);

		   		int fd= open(kek, O_CREAT); 
		   		if(fd!=-1)
		   		printf("File %s was created successfully!\n",kek );

			}
			else if(strcmp(option,"mkdir")==0){
			 	char kek[80];
		     	scanf("%s",kek);
		     	int mk = mkdir(kek,S_ISVTX);
		     	if(mk!=-1)
		   		printf("Directory %s was created successfully!\n",kek );
		   		

			}
			 else if(strcmp(option,"cp")==0){
			 	
			 	
			 	
			 }
	}
	    return 0;
    
    }
