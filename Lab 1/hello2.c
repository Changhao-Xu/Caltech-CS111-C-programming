#include <stdio.h>

int main(void)
{
    char s[100];  /* N.B. strings are arrays of chars in C */
    printf("Enter your name: ");
    scanf("%99s", s);

    printf("hello, %s!\n", s);
    return 0;
}