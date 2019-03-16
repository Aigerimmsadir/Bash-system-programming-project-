#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
   // char cwd[PATH_MAX];
   // if (getcwd(cwd, sizeof(cwd)) != NULL) {
   //     printf("Current working dir: %s\n", cwd);
   // } else {
   //     perror("getcwd() error");
   //     return 1;
   // }
	const char fname[] = "hello.txt";
const char w[] = "hello";

    int fd;
    char c;
    char str[152];
    int i = 0, j = 0;
    int bytesread;
    int flag = 1;
    int found = 0;
    int line = 1;
    int foundflag = 1;
    int n=0;
    char w[] = {'h', 'e', 'l', 'l', 'o'};
    int len = strlen(w);
while (read(fd, &buffer[i], 1) == 1) {
    /* end of line */
    if (buffer[i] == '\n' || buffer[i] == 0x0) {
        buffer[i] = 0;
        if (!strncmp(buffer, w, strlen(w))) {
            printf("w was found in line %d\n", line);
            puts(buffer);
            n++;
        }
        line++;
        i = 0;
        continue;
    }
    i++;
}
   return 0;
}