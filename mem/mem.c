#include "mem.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

typedef double Align;/*for alignment to long boundary*/

//block header
union header{
    /* data */
    struct {
        /* data */
        unsigned size;
        union header* next;
    };
    Align _;
};

typedef union header Header;


static Header base;//哨兵节点
static Header *freep = NULL;
static Header *morecore(unsigned nu);

void *smalloc(unsigned nbytes)
{
    Header *p, *prevp;
    // Header* moreroce(unsigned);
    unsigned nunits;//the number of block we malloc

    //这里多申请了一个block，作为给出去的blck的header
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) +1;
    if((prevp=freep)==NULL){
        //循环链表
        base.next=freep=prevp = &base;
        base.size = 0;
    }

    for(p=prevp->next;/*loop until find a block*/;prevp=p,p=p->next){
        if(p->size >= nunits){
            if(p->size==nunits){
                //整块给出去，需要调整指针
                prevp->next=p->next;
            }
            else{
                //把大的块分成两部分
                //分别设置size
                p->size-=nunits;
                p+= p->size;
                p->size=nunits;
            }
            //**********************************//
            freep=prevp;//每次都从上一次获得的地方重新开始
            return (void*)(p+1);
        }
        //
        if(freep==p)//扫了一遍回到起点
        {
            //**********************************//
            if((p=morecore(nunits))==NULL){
                return NULL;
            }
            // printf("%p\n",p);
        }
    }
    printf("should never get here!\n");
    // return NULL;
}

#define NALLOC 0 //minimum size
static Header *morecore(unsigned nu)
{
    char *request, *oldp;
    Header* up;

    oldp = sbrk(0);

    if(nu<NALLOC)nu = NALLOC;/*avoid frequently calling (system call) sbrk*/

    request = sbrk(nu*sizeof(Header));

    if(request==(char*)-1){
        printf("can not request memory!\n");
        return NULL;
    }
    assert(request==oldp);
    
    up = (Header*)request;
    up->size = nu;
    //假装free，其实是把up放进链表
    sfree((void*)(up+1));

    // printf("up:%p\n",up);

    /*这里注意up的next不一定是有效的，考虑up被连接成一块大的内存
     *所以不要返回up，会segment fault
    */
    return freep;
}

void sfree(void* ap)
{
    Header* hp = (Header*)ap - 1;//回退到头部
    Header *prevp, *p;

    for(prevp=freep,p=prevp->next;
        !(hp>prevp&&hp<p); prevp=p,p=p->next
    ){
        if(p<=prevp&&(hp>prevp||hp<p))
        break;
    }
    //
    if(hp+hp->size==p){
        hp->size+=p->size;
        prevp->next=hp;
        hp->next=p->next;
    }
    else if(prevp+prevp->size==hp){
        prevp->size+=hp->size;
    }
    else{
        // printf("hp:%p\n",hp);
        hp->next=p;
        prevp->next=hp;
    }
    // freep=hp;
}

void dump_addr()
{
    printf("%p", freep);
    Header* p = freep->next;
    // printf("->%p", p);

    for(;p!=freep;p=p->next){
        printf("->%p", p);
    }
    printf("\n");
}