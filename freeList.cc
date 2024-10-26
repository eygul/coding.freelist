#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM;
  head[0] = size - 2;
  head[1] = NULL;
}

long int*
freeList::reserve_space( int size ) {
  long int* loc = NULL;
  if (size + 2 > head[0]) {
    return NULL; 
  }
  long int* loc = head + 2;
  int old_size = head[0];
  head[0] = size;
  head += size + 2;
  head[0] = old_size - size - 2;
  
  return loc;
}

void
freeList::free_space( long int* location ) {
  long int* prev = head;
  head = location - 2;
  head[1] = (long int)prev;
}

void
freeList::coalesce_forward() {
  long int* traveling_point = head;
  while (traveling_point != NULL && (long int*)traveling_point[1] != NULL) {
    long int* next_block = (long int*)traveling_point[1];
    if (next_block == traveling_point + traveling_point[0] + 2) {
      traveling_point[0] += next_block[0] + 2; 
      traveling_point[1] = next_block[1];      
    } else {
      traveling_point = next_block;
    }
  }
}
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
