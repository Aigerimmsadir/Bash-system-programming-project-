    #include <stdio.h>
    #include <dirent.h>   
    #include <string.h>   
	#include <stdlib.h>


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



   static char*  currentdir = "C:\\Users\\Lenovo\\Desktop\\work\\low-level-programming\\far" ;
    char* filename1 = "textfile1.txt";
        char *filename2="";
	// void printDirInfo(){
 //        int len;
 //       як struct dirent *pDirent;
 //        DIR *pDir;
	//     int isNull=0;
 //        printf("current directory: %s\n",currentdir );
 //        if (strcmp(currentdir,"")==0) {
 //            printf ("Usage: testprog <dirname>\n");
 //            	isNull=1;
 //        }
 //        pDir = opendir (currentdir);
 //        if(isNull==0)
 //        if (pDir == NULL) {
 //            printf ("Cannot open directory '%s'\n", currentdir);
 //    		isNull=1;
 //        }
 //        if(isNull==0)
 //        while ((pDirent = readdir(pDir)) != NULL) {
 //            printf ("%s\n", pDirent->d_name);
 //        }
 //        closedir (pDir);
     
	// }

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
		char content[80];
		int isNull=0;
		FILE *fp1;
		

		fp1 = fopen(filepath,"r");
		if (fp1 == NULL )
			{
			printf("No such file in the directory.");
			isNull=1;
			}
		if(isNull==0)
		while((fgets(content, sizeof(content), fp1) !=NULL)){
			printf("%s\n",content );
		}
		fclose(fp1);
	}

	void removeFile(){
		catStr();
		if(remove(filepath)==0)
		printf("File %s was successfully removed from directory! \n",filename1 );
		else printf("Errors occured while removing this element. Please check input data.\n");
	}



	void printHelp(){
		printf("Terminal commands:\n");

		printf("	1. cp - copies content of one file in the directory to the another one.\n");
			printf("Command line parametres are: cp, nameOfFile1, nameOfFile2 . Example: cp text1.txt text2.txt\n");
		printf("	2. rm - removes the file from current directory \n");
			printf("Command line parametres are: rm, nameOfFile . Example: rm text1.txt\n");
		printf("	3. cat - prints out all the content of selected file\n");
			printf("Command line parametres are: cat, nameOfFile . Example: cat text1.txt\n");
		printf("	4. cd -changes current directory\n");
			printf("Command line parametres are: cd, newDirectoryAbsolutePath . Example: cd C:\\Users\\Lenovo\\Desktop\\work\n");
		printf("	5. ls - prints out the list of content of current directory\n");
			printf("Command line parametres are: ls . Example:ls\n");
		printf("	6. touch - creates new text file in the directory\n");
			printf("Command line parametres are: touch, newFileName . Example:touch newfile.txt\n");
		printf("	7. gcc - compiles selected C program\n");
			printf("Command line parametres are: gcc nameOfProgramFile . Example:gcc myprog.c\n");
		printf("	7. help - prints out usage information\n");
			printf("Command line parametres are: help . Example:help\n");
	
	}
	char compilePath[80] ;
	void concatPathToCompile(){
		catStr();
		memset(compilePath,0,255);
		strcat(compilePath,"cd ");
		strcat(compilePath,currentdir);//"C:\\Users\\Lenovo\\Desktop\\work" 
		strcat(compilePath," && gcc ");
		strcat(compilePath,filename1);//2.c
		strcat(compilePath," && a");
	}

	void compile(){
		concatPathToCompile();
		system(compilePath);
	}
	void copy(){
		FILE *fp1,*fp2;
		fp1 = fopen(filepath,"r");
		fp2 = fopen(filepath2,"w");
		printf("%s\n",filepath2 );
		char content[80];
		while((fgets(content, sizeof(content), fp1) !=NULL)){
			fputs(content,fp2);
		}
		printf("Data from %s was successfully copied to %s!\n",filename1,filename2 );
		fclose(fp1);
		fclose(fp2);
	}	

    int main (int c, char *argv[]) {

		printf("Welcome!\n" );
		printf("enter <help> to get detailed info about commands and their usage\n");
		char option[80];
		while(1){
		printf("\nchoose operation:\n");	
			scanf("%s",&option);
		  if (strcmp(option,"ls")==0) {
		     	printf("\nBelow is content of current directory:\n\n" );
		    	// printDirInfo();
		    }
		    else if(strcmp(option,"cd")==0){
		    	char kek[80];
		    		scanf("%s",&kek);
		    	currentdir = kek;
		    	printf("this is new currentdir%s\n",currentdir );
		    	printf("current directory successfully changed!" );
		    
		    	
		    }    
		     else if(strcmp(option,"cat")==0){
		     	printf("\n");
		     	char kek[80];
		     	scanf("%s",&kek);
		     	filename1=kek;
		    	catStr();
				// PrintFileInfo();
			}
			 else if(strcmp(option,"help")==0){
		     		printHelp();
			}
			 else if(strcmp(option,"rm")==0){
			 		char kek[80];
		     		scanf("%s",&kek);
		     		filename1=kek;
			 		catStr();
		     		removeFile();
			}
			 else if(strcmp(option,"touch")==0){
			 		char kek[80];
		     		scanf("%s",&kek);
		     		filename1=kek;
		     		catStr();
		     		FILE *fp1;
					fp1 = fopen(filepath,"w+");
					if(fp1!=NULL)
					printf("File %s was created successfully!\n",filename1 );
					else 
						printf("Errors occured while creating this element.Please check input data.\n");

			}
			 else if(strcmp(option,"gcc")==0){
			 	printf("\n");
			 	char kek[80];
		     	scanf("%s",&kek);
		     	filename1=kek;
			 	compile();
			}
			 else if(strcmp(option,"0")==0){
			 	printf("Bye!\n");
			 	break;
			}
			 else if(strcmp(option,"cp")==0){
			 	char kek1[80],kek2[80];
			 	scanf("%s",&kek1);
			 	scanf("%s",&kek2);
			 	filename1=kek1;
			 	filename2=kek2;
			 	catStr();
			 	copy();
			 }
	}
	    return 0;
    
    }
