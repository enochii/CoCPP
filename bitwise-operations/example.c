#include "bit-op.h"
#include "stdio.h"

int main()
{
    unsigned i = 1211;
    unsigned j = 2324;
    printf("i is:");
    output_by_binary(i);
    putchar('\n');
    printf("j is:");
    output_by_binary(j);
    putchar('\n');
    //output_by_binary_(i);

    // putchar('\n');
    printf("getbits(i,5,4) is:" );
    output_by_binary(getbits(i, 5, 4));
    putchar('\n');

    printf("setbits(i,5,4,j) is:");
    output_by_binary_(setbits(i,5,4,j));
    putchar('\n');

    printf("invertbits(i,5,4) is:");
    output_by_binary_(invertbits(i,5,4));
    putchar('\n');

    printf("rightrot(i,5) is:");
    output_by_binary_(rightrot(i,5));
    putchar('\n');

    return 0;
}