/* 
   Write a C program to find out if the underlying 
   architecture is little endian or big endian. 
 */
 
#include <stdio.h>
int main ()
{
unsigned char a=0x03;
a=((a&0x01)<<5)|((a&0x02)<<3);
printf("%d",a); 
  return 0;
}
