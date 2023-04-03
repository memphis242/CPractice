#include <stdio.h>


int greater_common_divisor(int u, int v)
{
    int temp;

    while ( u > 0 )
    {
        // If u is less than v, swap them.
        if ( u < v )
        {
            temp = u;
            u = v;
            v = temp;
        }

        u = u - v;
    }

    return v;
}


int main(void)
{
    int u, v;

    scanf("%d", &u);
    scanf("%d", &v);

    if ( u>0 && v>0 )
    {
        printf( "%d %d %d\n", u, v, greater_common_divisor(u,v) );
    }

    return 1;
}
