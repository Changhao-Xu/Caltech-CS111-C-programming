/* 
 * This program computes the day of the year
 * on which Easter falls, given the year.
 */
#include <stdio.h>

#define YEAR_LOWER 1582
#define YEAR_UPPER 39999

/* This algorithm is taken from Donald Knuth’s
 * famous book The Art of Computer Programming
 */

/* Function prototypes */
int calculate_Easter_date(int year);

int calculate_Easter_date(int year) {
    if (year < YEAR_LOWER || year > YEAR_UPPER)
    /* The allowable years are in the range 1582 to 39999 */
    {
        return 0;
    }
    else
    {
        int golden_year, century, skipped_leap;
        int correction_factor, d_sunday, epact, N;

        golden_year = (year % 19) + 1 ;
        /* (Y mod 19) + 1 is the "golden year" in the 19-year Metonic cycle */
        century = (year / 100) + 1;
        /* definition of the century */
        skipped_leap = (3 * century / 4) - 12;
        /* definition of skipped leap years */
        correction_factor = ((8 * century + 5) / 25) - 5;
        /* correction factor for the moon's orbit */
        d_sunday = (5 * year / 4) - skipped_leap - 10;
        /* March ((-D) mod 7 + 7) is a Sunday */
        epact = (11 * golden_year + 20 + correction_factor - skipped_leap) % 30;
        /* the "epact" which specifies when a full moon occurs */

        if( ((epact == 25) && (golden_year > 11)) || epact == 24 )
        {
            epact++;
        }

        N = 44 - epact; /* March N is a "calendar full moon" */

        if (N < 21)
        {
            N = N + 30;            
        }

        N = N + 7 - ((d_sunday + N) % 7 );
        /* N is a Sunday after full moon */

        if (N > 31)
        {
            return (N - 31); /* the date is APRIL (N - 31) */
        }
        else
        {
            return (-N);
            /* the date is MARCH N so need to return negative */ 
        }
    }
}

int main(void)
{
    while(1)
        {
            int year;
            int result;
            int easter;
            result = scanf("%d", &year);
        
            if( result == EOF)
            /* check scan input from stdin,
             * ("end of file") when there is no more input
             */
            {
                break;
            }

            easter = calculate_Easter_date(year);
            if (easter > 0)
            /* April */
            {
                printf("%d - April %d\n", year, easter);
            }
            else if (easter < 0)
            /* March */
            {
                printf("%d - March %d\n", year, -easter);
            }
            else
            /* year not in range */
            {
                fprintf(stderr, "year not in range of 1582 and 39999 \n");
            }                                                             
        }
    return 0 ;
}
