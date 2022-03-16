#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct memory_block {
    char *mem;
    long size;
    struct memory_block *next;
} memory_block;

char *heapPtr = NULL;
int sizeOfMemory = 0;
memory_block *allocatedBlocks;

memory_block *createNode(int size, void *mem, memory_block *prev, memory_block *next) {
    if (size <= 0 || mem == NULL) return NULL;
    memory_block *newNode = (memory_block *)malloc(sizeof(memory_block));
    if (newNode == NULL) return NULL;
    newNode->size = size;
    newNode->mem = mem;
    newNode->next = next;
    if (prev) prev->next = newNode;
    return newNode;
}

int Mem_Init(int sizeOfRegion){
    heapPtr = (char *) malloc(sizeof (char) * sizeOfRegion);
    if (heapPtr == NULL || sizeOfRegion <= 0) {
        return -1;
    }
    sizeOfMemory = sizeOfRegion;
    return sizeOfRegion;
}

void *Tedu_alloc(int size) {
    if (sizeOfMemory < size || size < 1) return NULL;
    char *mem = heapPtr;
    long availableSize = 0;
    memory_block *prev = NULL;
    memory_block *next = NULL;
    memory_block *temp = allocatedBlocks;
    int checker = 0;

    if (allocatedBlocks == NULL) {
        allocatedBlocks = createNode(size, mem, NULL, NULL);
        return allocatedBlocks->mem;
    }

    availableSize = temp->mem - heapPtr;
    if (availableSize >= size) {
        mem = heapPtr;
        prev = NULL;
        next = temp;
        checker = 1;
    }

    while (temp->next && checker == 0) {
        availableSize = temp->next->mem - (temp->mem + temp->size);
        if (availableSize >= size) {
            mem = temp->mem + temp->size;
            prev = temp;
            next = temp->next;
            checker = 1;
        }
        temp = temp->next;
    }

    availableSize = (heapPtr + sizeOfMemory) - (temp->mem + temp->size);
    if (availableSize >= size && checker == 0) {
        mem = temp->mem + temp->size;
        prev = temp;
        next = temp->next;
        checker = 1;
    }

    if (checker == 0) return NULL;
    memory_block *newMemoryBlock = createNode(size, mem, prev, next);
    if (newMemoryBlock->mem == heapPtr) allocatedBlocks = newMemoryBlock;
    return mem;
}

int TEDU_Free(void *ptr) {
    if (ptr == NULL) return -1;
    memory_block *prev = NULL;
    memory_block *temp = allocatedBlocks;

    while (temp != NULL) {
        if (temp->mem <= (char *)ptr && (char *)ptr < temp->mem + temp->size) {
            if (temp == allocatedBlocks) {
                allocatedBlocks = temp->next;
            } else {
                prev->next = temp->next;
            }
            for (int i = 0; i < temp->size; i++) {
                *(temp->mem + i) = 0;
            }
            temp->next = NULL;
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }
    return -1;
}

int Mem_IsValid(void *ptr) {
    if (ptr == NULL) return 0;
    memory_block *temp = allocatedBlocks;
    while (temp != NULL) {
        if (temp->mem <= (char *)ptr && (char *)ptr < temp->mem + temp->size) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int Mem_GetSize(void *ptr) {
    if (ptr == NULL) return 0;
    memory_block *temp = allocatedBlocks;
    while (temp != NULL) {
        if (temp->mem <= (char *)ptr && (char *)ptr < temp->mem + temp->size) {
            return (int)temp->size;
        }
        temp = temp->next;
    }
    return -1;
}

int TEDU_GetStats() {
    long memoryUsage = 0;
    long availableSize = 0;
    int numberOfFragments = 0;
    long totalFragmentSize = 0;
    long largestFragmentSize = 0;
    memory_block *temp = allocatedBlocks;

    if (temp != NULL && temp->mem != heapPtr) {
        availableSize = temp->mem - heapPtr;
        if (availableSize > 0) {
            numberOfFragments++;
            totalFragmentSize += availableSize;
            largestFragmentSize = availableSize;
        }
    }

    if (temp != NULL) {
        while (temp->next != NULL) {
            memoryUsage += temp->size;
            availableSize = temp->next->mem - (temp->mem + temp->size);
            if (availableSize > 0) {
                numberOfFragments++;
                totalFragmentSize += availableSize;
                if (largestFragmentSize < availableSize) {
                    largestFragmentSize = availableSize;
                }
            }
            temp = temp->next;
        }

        memoryUsage +=  temp->size;
        availableSize = (heapPtr + sizeOfMemory) - (temp->mem + temp->size);
        if (availableSize > 0) {
            numberOfFragments++;
            totalFragmentSize += availableSize;
            if (largestFragmentSize < availableSize) {
                largestFragmentSize = availableSize;
            }
        }
    }
    printf("Memory used is %ld and %.4lf%% is used\n", memoryUsage, ((double)memoryUsage / (double)sizeOfMemory) * 100);
    printf("Number of Fragments %d\n", numberOfFragments);
    printf("Average fragment size: %.2lf\n", numberOfFragments == 0 ? 0: ((double)totalFragmentSize / numberOfFragments));
    printf("Largest Fragment Size %ld \n", largestFragmentSize);
    return 1;
}
