#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    char s[100];  /* N.B. strings are arrays of chars in C */
    int randN;
    int i;

    srand(time(0));
    randN = rand() % 10 + 1;

    printf("Enter your name: ");
    scanf("%99s", s);

    if (randN % 2 == 0)
        {
            for (i = 0; i < randN; i++)
            {
                printf("%d: hello, %s!\n", randN, s);
            }
        }
        else
        {
            for (i = 0; i < randN; i++)
            {
                printf("%d: hi there, %s!\n", randN, s);
            }        
        }
    
    return 0;
}