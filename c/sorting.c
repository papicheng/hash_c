
#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"

void sort(struct darray* arr, int select){

  switch(select){
    case BINARY_SEARCH_ONE   : insertion_sort(arr); break;
    case BINARY_SEARCH_TWO   : quick_sort(arr, 0, arr->size - 1); break;
    case BINARY_SEARCH_THREE :
    case BINARY_SEARCH_FOUR  :
    case BINARY_SEARCH_FIVE  :  // Add your own choices here
    default: 
      fprintf(stderr,
              "The value %d is not supported in sorting.c\n",
              select);
      // Keep this exit code as the tests treat 23 specially
      exit(23);
  }
}


// You may find this helpful
void swap(char* *a, char* *b)
{
        char* temp = *a;
        *a = *b;
        *b = temp;
}


void insertion_sort(struct darray* arr){
//  fprintf(stderr, "Not implemented\n");
//  exit(-1);
  Value_Type insertionArray[arr->size];
  insertionArray[0] = arr->cells[0];
  for(int i = 1; i < arr->size; ++i){
    insertionArray[i] = arr->cells[i];
    // 2 ints to sort each new element added to new arry
    int a;
    int b = i - 1;
    for(a = i; a > 0; a--){
      if(compare(insertionArray[a], insertionArray[b]) < 0){
        swap(&insertionArray[a], &insertionArray[b]);
      }
      b--;
    }
  }
  for(int index = 0; index < arr->size; index++){
    arr->cells[index] = insertionArray[index];
  }
}
int sortingQuick(Value_Type* arr, int frontIndex, int backIndex){
  //pivot will be element zero, we also will assign 2 pointers, one as the end of array one at the begining.
  int pivot = frontIndex;

  while(backIndex  != pivot){
    if(compare(arr[pivot], arr[pivot + 1]) < 0){
      swap(&arr[pivot + 1], &arr[backIndex]);
      backIndex--;
    }
    if(compare(arr[pivot], arr[pivot + 1]) > 0){
      swap(&arr[pivot], &arr[pivot + 1]);
      pivot++;
    }
  }
  return pivot;
}

// Hint: you probably want to define a helper function for the recursive call
void quick_sort(struct darray* arr, int frontIndex, int backIndex) {
  if(frontIndex < backIndex){
    int pivot = (sortingQuick(arr->cells, frontIndex, backIndex));
    quick_sort(arr, frontIndex, pivot - 1);
    quick_sort(arr, pivot + 1, backIndex);
  }
}
