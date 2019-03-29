#ifndef COCPP_BIT_OP
#define COCPP_BIT_OP

/*getbits: get n bits from position p*/
unsigned getbits(unsigned x, int p, int n);

void output_by_binary(unsigned n);

void output_by_binary_(unsigned n);

/*set the n bits from position p of x to the right n bits of y*/
unsigned setbits(unsigned x, int p, int n, unsigned y);

/*invert the n bits from position p of x*/
unsigned invertbits(unsigned x, int p, int n);

/*right rotate*/
unsigned rightrot(unsigned x, int n);

#endif