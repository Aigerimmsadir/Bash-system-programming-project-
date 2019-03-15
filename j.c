    #include <stdio.h>
    #include <dirent.h>   
    #include <string.h>   
	#include <stdlib.h>
	#include <unistd.h> 
	#include <fcntl.h> 
	#define _GNU_SOURCE
	#include <sys/stat.h>
	#include <sys/syscall.h>
	#include <assert.h>
#include <limits.h>

       #define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

       struct linux_dirent {
           long           d_ino;
           off_t          d_off;
           unsigned short d_reclen;
           char           d_name[];
       };

#define BUF_SIZE 8192
       
	


   static char*  currentdir = "/home/aigerim/Desktop/systemprog/Bash-system-programming-project-" ;
typedef struct char80 { char c[80]; } char80;

char80 get_line ()
{
    char80 *mymessage;
    mymessage = malloc (sizeof (char80));
    char next,i=0;
    while(next=getchar()){
          if(next!='\n' && next!='\0'){
            mymessage->c[i]=next;
            i++;
          }
          else break;
        }
    
    
    return *mymessage;
}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
	 void print_dir_with_hidden(int ishidden,int inode,int m){
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
              if (inode==1) printf("inode       ");
               printf("d_name              file_type\n\n");

               for (bpos = 0; bpos < nread;) {
                   d = (struct linux_dirent *) (buf + bpos);
                   
                   d_type = *(buf + bpos + d->d_reclen - 1);
                  if (ishidden==1)
                  {
                  if (inode==1) printf("%-10ld  ", d->d_ino);
                   printf("%-20s",  d->d_name);
                   if (m==1) printf(", " );
                   else 
                   printf("%s\n", (d_type == DT_REG) ?  "regular" :
                                    (d_type == DT_DIR) ?  "directory" :
                                    (d_type == DT_FIFO) ? "FIFO" :
                                    (d_type == DT_SOCK) ? "socket" :
                                    (d_type == DT_LNK) ?  "symlink" :
                                    (d_type == DT_BLK) ?  "block dev" :
                                    (d_type == DT_CHR) ?  "char dev" : "???");
                   
                    
                  }
                  else{
                    if ((d->d_name)[0]!='.')
                    {
                      if (inode==1) printf("%-10ld  ", d->d_ino);
                          printf("%-20s ",  d->d_name);
                      if (m==1) printf(", " );
                      else 
                          printf("%s\n", (d_type == DT_REG) ?  "regular" :
                                    (d_type == DT_DIR) ?  "directory" :
                                    (d_type == DT_FIFO) ? "FIFO" :
                                    (d_type == DT_SOCK) ? "socket" :
                                    (d_type == DT_LNK) ?  "symlink" :
                                    (d_type == DT_BLK) ?  "block dev" :
                                    (d_type == DT_CHR) ?  "char dev" : "???");
                   
                                           /* code */
                    }
                   
                 }bpos += d->d_reclen;        
               }
           }

     
    }



	void PrintFileInfo(){
	    printf("\n");
		char kek[80];
		scanf("%s",kek);
		printf("File content is below:\n");
		int fd; 

    	char buf2[100000]; 
        
 		fd= open(kek, O_RDWR); 
  
    	write(1, buf2, read(fd, buf2, 100000)); 
  		

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
			printf("\n\n");
	
	}


	void copy(){
	    int input_fd, output_fd;    
	    ssize_t ret_in, ret_out;    
	    char buffer[BUF_SIZE];   
	 

	            char kek1[80],kek2[80];
	        scanf("%s",kek1);
	        scanf("%s",kek2);


	    input_fd = open (kek1, O_RDONLY);
	    if (input_fd == -1) {
	            perror ("open");
	          
	    }
	 

	    output_fd = open(kek2, O_WRONLY | O_CREAT, 0644);
	    if(output_fd == -1){
	        perror("open");
	        
	    }
	 

	    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
	            ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
	            if(ret_out != ret_in){

	                perror("write");
	              
	            }
	    }
	 

	    close (input_fd);
	    close (output_fd);
	 
	 
	}	

    int main (int c, char *argv[]) {

		printf("Welcome!\n" );
		printHelp();
		char option[80];
		   char cwd[PATH_MAX];

   
		while(1){
			if (getcwd(cwd, sizeof(cwd)) != NULL) {
       		strcpy(currentdir,cwd);
			printf("\n%s : ",currentdir);	
			 char80 *message;
            message = malloc (sizeof (char80));
    
            *message = get_line ();
            char** tokens;
             tokens = str_split(message->c, ' ');
          char option[80];
            strcpy(option,tokens[0]);

		 	if (strcmp(option,"ls")==0) {

		     	printf("\nBelow is content of current directory:\n\n" );
		     	int a=0,i=0,m=0;
		     	if(contains)
		    	print_dir_with_hidden(0,0,0);

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
			 	
			 	copy();
			 	
			 }
	}
	    return 0;
    
    }