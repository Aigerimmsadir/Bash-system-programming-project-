	#include <stdlib.h>	
	#include <assert.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
int contains(char ** line,char * command){
  for(int i=0;i<sizeof(line);i++){
    if(strcmp(line[i],command)==0) return 1;
  }
  return 0;
}   
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

int main(int argc,char *argv[])
{
char80 *message;
            message = malloc (sizeof (char80));
    
            *message = get_line ();
            char** tokens;
             tokens = str_split(message->c, ' ');
              
               int a;
               int i;
               int m;
                
                    if(tokens[1][1]=='a'){
                    	 a=1;
                    }else{ int a=0;}
                    if(tokens[2][1]=='i'){
                    	i=1;
                    }else{  i=0;}
                    if(tokens[3][1]=='m'){
                    	 m=1;
                    }else{ m=0;}
// if(contains(tokens,"-i")==1)
// printf("%s\n", "yes");
// if(contains(tokens,"-m")==1)
// printf("%s\n", "yes");

                print_dir_with_hidden(a,i,m);

return 0;
}
