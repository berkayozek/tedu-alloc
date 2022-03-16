#include <stdio.h>
#include "mem_worst.c"

int main(){
    Mem_Init(50 * (1024 * 1024)); // 50 MB via Mem_init


    printf("\n--------ORDER A--------\n");
    char *name = (char *) Tedu_alloc(10);
    float *fNum = (float *) Tedu_alloc(sizeof(float));
    double *dNum = (double *) Tedu_alloc(sizeof(double));
    int *iNum = (int *) Tedu_alloc(sizeof(int));

    TEDU_GetStats();
    
    printf("----After Free----\n");
    TEDU_Free(name);
    TEDU_Free(fNum);
    TEDU_Free(dNum);
    TEDU_Free(iNum);

    TEDU_GetStats();


    printf("\n------ORDER B--------\n");
    char *first = (char *)Tedu_alloc(6);
    char *second = (char *)Tedu_alloc(10);
    char *third = (char *)Tedu_alloc(5);
    char *fourth = (char *)Tedu_alloc(10);
    char *fifth = (char *)Tedu_alloc(5);

    TEDU_GetStats();

    TEDU_Free(fifth);
    TEDU_Free(first);
    TEDU_Free(third);

    printf("----After Free----\n");

    TEDU_GetStats();

    printf("\n-----------------\n");
    printf("Allocating the freed memory again");
    printf("\n-----------------\n");
    
    fifth = (char *) Tedu_alloc(5);
    first = (char *) Tedu_alloc(6);
    third= (char *) Tedu_alloc(10);

    printf("fifth is Valid: %d\n", Mem_IsValid(fifth));
    printf("first is Valid: %d\n", Mem_IsValid(first));
    printf("third is Valid: %d\n", Mem_IsValid(third));

    TEDU_GetStats();

    printf("\n-----------------\n");
    printf("Allocating 100 Number of integer array");
    printf("\n-----------------\n");

    int *intArr = (int *) Tedu_alloc(sizeof(int) * 100);
    TEDU_GetStats();
    printf("Filling the array between 0 to 100\n");
    if(Mem_IsValid(intArr)) {
        for (int i=0; i<100; i++){
            *(intArr + i) = i;
        }
    }

    if (Mem_IsValid((intArr + 30)))
        printf("Array elements with offset 30 is: %d\n", *(intArr + 30));

    if (Mem_IsValid((intArr + 54)))
        printf("Array elements with offset 54 is: %d\n", *(intArr + 54));

    if (Mem_IsValid((intArr + 30)))
        printf("Array elements with offset 78 is: %d\n", *(intArr + 78));

    printf("Freeing the memory which allocated above\n");
    TEDU_Free((intArr + 99)); // This is also free all memory of intArr
    TEDU_GetStats();
    printf("After Freeing intArr, calling Mem_IsValid returns %d \n", Mem_IsValid(intArr));

    printf("\n-----------------\n");
    printf("Allocating Large Memories");
    printf("\n-----------------\n");

    printf("Allocating 100kb, firstBig variable\n");
    char *firstBig = (char *) Tedu_alloc(100 * 1024); // 100 KB allocation
    if (Mem_IsValid(firstBig)) {
        printf("firstBig is valid\n");
        printf("firstbig size is %d \n", Mem_GetSize(firstBig));
    } else {
        printf("firstBig is not valid\n");
    }



    TEDU_GetStats();
    printf("\nAllocating 5mb, secondBig variable\n");

    char *secondBig = (char *) Tedu_alloc(5 * (1024 * 1024));

    if (Mem_IsValid(secondBig)) {
        printf("secondBig is valid\n");
        printf("secondBig size is %d \n", Mem_GetSize(secondBig));
    } else {
        printf("secondBig is not valid\n");
    }


    printf("\nAllocating 800kb, thirdBig variable\n");
    char *thirdBig = (char *) Tedu_alloc(800 * (1024));
    if (Mem_IsValid(thirdBig)) {
        printf("thirdBig is valid\n");
        printf("thirdBig size is %d \n", Mem_GetSize(thirdBig));
    }  else {
        printf("thirdBig is not valid\n");
    }


    TEDU_GetStats();

    printf("\nFreeing secondBig (5mb)\n");
    TEDU_Free(secondBig);

    printf("\nAllocating 4.5mb, fourthBig variable\n");
    char *fourthBig = (char *) Tedu_alloc(4.5 * (1024 * 1024));
    if (Mem_IsValid(fourthBig)) {
        printf("fourthBig is valid\n");
        printf("fourthBig size is %d \n", Mem_GetSize(fourthBig));
    } else {
        printf("fourthBig is not valid\n");
    }

    TEDU_GetStats();

    printf("\nAllocating 450kb, fifthBig variable\n");
    char *fifthBig = (char *) Tedu_alloc(450 * ( 1024));
    if (fifthBig != NULL && Mem_IsValid(fifthBig)) {
        printf("fifthBig is valid\n");
        printf("fifthBig size is %d \n", Mem_GetSize(fourthBig));
    } else {
        printf("fifthBig is not valid\n");
    }
    TEDU_GetStats();

    printf("\nAllocating 44mb, sixBig variable\n");
    char *sixBig = (char *) Tedu_alloc(44 * (1024 * 1024));
    if (Mem_IsValid(sixBig)) {
        printf("sixBig is valid\n");
        printf("sixBig size is %d \n", Mem_GetSize(sixBig));
    } else {
        printf("sixBig is not valid\n");
    }
    TEDU_GetStats();

    return 0;
}
