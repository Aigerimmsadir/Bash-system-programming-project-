#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
 
#define BUF_SIZE 8192
 
#define __getname()     kmem_cache_alloc(names_cachep, SLAB_KERNEL)
#define putname(name)   kmem_cache_free(names_cachep, (void *)(name))

char *getname(const char *filename) {
        char *tmp = __getname();        /* allocate some memory */
        strncpy_from_user(tmp, filename, PATH_MAX + 1);
        return tmp;
}