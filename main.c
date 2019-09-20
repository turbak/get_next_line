#include "get_next_line.h"
#include <stdio.h>

int main()
{
   char *str;
   int fd;
   fd = open("2.txt", O_RDONLY);
   while  (get_next_line(fd, &str) > 0)
   {
       printf("%s", str);
       free(str);
   }
   close(fd);
   return (0);
}
