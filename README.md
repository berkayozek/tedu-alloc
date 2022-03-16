#Authors
- Berkay ÖZEK
- Berke ÖCAL

#Design Overview:
- First fit, best fit and worst fit algorithms are implemented seperately. All three algorithm implementations keep
track of allocated memory blocks via memory structs. Checking fragmentation is identical for every algorithm.
All implementations check if there is an unused memory block between the starting address of the heap and the
address mapped by head memory struct. Fragmentations between memory blocks are also checked by mapped
memory addresses. If a structs mapped address ending is equal to next structs mapped starting memory address,
then there isn’t any empty space between two mapped memories and there isn’t any fragmentation. Finally,
memory fragmentation between last memory struct and end of the heap is checked by calculating the difference
between last address of the heap and last address mapped by the last memory struct in the data structure.
- We implemented a linked list to map between addresses and memory structs. Each struct has following variables:
- char *mem: mem pointer points to the starting address of the memory block in the heap, requested via
TEDU_alloc function.
- int size: int size holds the length of the requested memory block requested with a TEDU_alloc call.
- struct memory_block *next: next pointer holds the address of the next struct in the linked list.
- Memory address mapped by the head of the linked list is always the closest one to the initialized heap address.
In this way, we don’t have to traverse linked list to check fragmentation between head nodes mapped adress and
the heap. When user allocates a new memory address from the heap a new node is created and added to linked
list. Location of the new node in the linked list is parallel with the allocated memory address from the heap. As
an example, if the linked list has nodes A and C where A is the head node. Assuming there is sufficient memory
space between mapped memories of A and C nodes in the heap, newly created node will be inserted between
nodes A and C.
- First fit algorithm allocates first sufficient memory block from the heap. The algorithm doesn’t traverse all of the
linkled list if a sufficent memory block is found. It is the fastest among the three.
- Best fit algorithm allocates smallest sufficent memory block from the heap. The algorithm has to traverse all of
the linked list to find the smallest sufficient memory block. Even though this algorithm is slower than first fit
algorithm, it is the best one to minimize memory fragmentation.
- Worst fit algorithm allocates largest sufficent memory block from the heap. Similarly to best fit, this algorithm
has to traverse all of the linked list. In order to find largest sufficient memory block. This algorithm is also slower
than first fit algorithm but it has an advantage. Internal fragmentation is high and leftover partitions can be filled
by other allocation calls.
##Complete Specification:
- Mem_init(int sizeOfRegion) function allocates a heap memory with the size of sizeOfRegion in bytes with a
malloc() call. If malloc() call fails or requested size is zero or less, -1 is returned. Otherwise, size of memory
requested in bytes is returned.
- Tedu_alloc(int size) allocates suitable memory block with the size of “int size”, if it is available.
- Tedu_alloc(int size) function is implemented differently for every memory management algorithm. Every
algorithm checks fragmentation from the start of the heap, between allocated memory blocks in the heap and
fragmentation between the last mapped heap address and final address of the heap, respectively.
- First fit algorithm doesn’t check other fragmentations if a sufficent memory block is found. As an example, if
there is a fragmentation at the start of the heap and size of the memory block is suitable, first fit algorithm will
not check inbetween and end fragmentations. Implementation has “int checker” variable and initially is set to 0.
When a suitable memory block is found checker is set to 1. If checker is 1 other fragmentations are neglected and
linked list is not traversed furthermore. If checker is 0 after traversing the whole linked list null is returned as
there isn’t an available memory block.
- Best fit algorithm checks every fragmentation and will traverse whole linked list in order to find smallest
sufficient memory block. Implementation has “long bestSize” variable and it is set to LONG_MAX initally. This
variable keeps track of the size of smallest sufficient memory block and used for comparison between fragmented
memory blocks. If bestSize is equal to LONG_MAX after traversing the linked list null is returned as there is not
an available memory block.
- Worst fit algorithm is the opposite of the best fit algorithm. This algorithm checks every fragmentation in order
to find largest sufficient memory block. Implementation has “long bestSize” variable and it is set to LONG_MIN
initially. If worstSize is equal to LONG_MIN after traversing the linked list null is returned as there is not a
suitable memory block.
- Tedu_Free(void *ptr) function is same for all of the implementations. Linked list is traversed until NULL pointer
is reached. Void *ptr is checked if it points to a memory block allocated by TEDU_alloc(int size) function. Void
*ptr does not has to be inital address of the memory block. Every single byte in the memory block of void *ptr is
set to 0. Afterwards, associated memory struct used for mapping addresses is freed. In order to manipulate linked
list, memory_block *prev is used to keep track of previous node in the linked list. In this way we can free memory
blocks inbetween two nodes and tail node. If head of the linked list is freed, new head is set to the next node in
the linked list. If void *ptr does not point to an allocated memory address -1 is returned.
- Mem_IsValid(void *ptr) is implemented as a similar code to TEDU_Free(void *ptr). Linked list is traversed until
NULL pointer is reached. Every iteration checks if void *ptr falls within an allocated memory address allocated
by TEDU_alloc(int size) function. If void *ptr falls within range of an allocated memory block, 1 is returned.
Otherwise, 0 is returned.
- Mem_GetSize(void *ptr) is similar to Mem_IsValid(void *ptr) function. Linked list is traversed until NULL
pointer is reached. Every iteration checks if void *ptr falls within an allocated memory address allocated by
TEDU_alloc(int size) function. If void *ptr falls within range of an allocated memory block, size of that memory
block is returned. Otherwise, -1 is returned.
- Mem_GetStats() function traverses linked list until NULL pointer is reached. Memory usage, total fragment size,
number of fragments, largest fragment size are all updated while traversing the linked list. All of the mentioned
variables and memory usage percentage and average fragment size is printed to the console. Upon successfull
call 1 is returned.
- Memory_block *createNode(int size, void *mem, memory_block *prev, memory_block *next) function creates
a new memory block struct and sets newly created structs variables to the parameters. Upon successfull call
address of the newly created node is returned. Otherwise NULL is returned.
# Performance evaluation:
- First fit algorithm is the fastest among the three algorithms. Worst case time complexity of the first fit algorithm
is O(n) where n is previously allocated memory blocks. Advantage of the first fit algorithm over best fit and worst
fit algorithms is that first fit generally doesn’t has to traverse all of the linked list and average performance is
faster than O(n). Worst fit and best fit algorithms time complexity is always O(n) as both algorithms has to
traverse all of the linked list to find the most suitable memory block with respective to their criteria. Best, average,
and worst time complexities are all same, O(n). Worst case time complexity for traversing the linked list is O(n)
where n is number of nodes. In order to increase the speed of our program we could use a priority queue or a
binary search tree for accessing suitable memory blocks faster. However, under given conditions they were not
worth to implement.
- Best fit algorithm utilizes memory for usability far more efficently than first and worst fit algorithms by keeping
fragmentation to a minimum. It is shown by the example test case that best fit algorithm has two fragmentations,
worst and first algorithms has four fragmentations. Furthermore, worst fit algorithm cannot allocate 44MB at the
end of the sample test case where as best and first fit algorithms both can. To conclude first fit algorithm is more
favorable considering speed and simplicity. It is easier to implement, it is faster and there is less overhead. Only
downside of the first fit algorithm is memory fragmentation. Best fit algorithm is more favorable considering
memory utilization and reducing fragmentation. It over performs other two algorithms when it comes to memory
management.
# Known bugs and erros:
- None. Code has passed allocation tests for various data types such as int, float, double, char, int *, char* etc.

# How to Compile
`$ make`

# How to Run
### For example running best fit algorithm:
`$ ./main_best.c`