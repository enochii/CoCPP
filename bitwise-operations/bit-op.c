#include <stdlib.h>
#include <stdio.h>

/*getbits: get n bits from position p*/
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