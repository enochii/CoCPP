#include "bit-op.h"
#include "stdio.h"

int main()
{
    unsigned i = 1211;
    output_by_binary(i);
    putchar('\n');
    output_by_binary_(i);

    putchar('\n');
    output_by_binary(getbits(i, 5, 4));

    return 0;
}