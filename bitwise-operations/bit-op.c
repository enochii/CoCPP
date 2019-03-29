#include <stdlib.h>
#include <stdio.h>

unsigned getbits(unsigned x, int p, int n)
{
    //here we assump that the index begins at zero
    //and p,n is a valid positive num
    return (x>>(p-n+1))&(~(~0<<n));
}

void output_by_binary(unsigned n)
{
    static char buf[33];
    itoa(n, buf, 2);
    printf("%s", buf);
}

void output_by_binary_(unsigned n)
{
    //use recursion and bit op
    if(!n)return;
    output_by_binary_(n>>1);

    if(n&1){
        printf("1");
    }
    else{
        printf("0");
    }
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned mask = ~(~0<<n)<<(p-n+1);
    return ((~mask)&x)|((~(~0<<n)&y)<<(p-n+1));
}

unsigned invertbits(unsigned x, int p, int n)
{
    unsigned mask = ~(~0<<n)<<(p-n+1);
    return (mask|x)//set the n bits on 1, keep the others
            &
            ~(mask&x);//extract the n bits and invert
}

unsigned rightrot(unsigned x, int n)
{
    return (
            (x<<(sizeof(x)*8-n))
            |
            (x>>n)
            );
}