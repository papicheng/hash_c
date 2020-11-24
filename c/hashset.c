#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "global.h"
#include "hashset.h"

//global variable for collisions
int collisionTotal = 0;

// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}

// Helper functions for finding prime numbers 
bool isPrime (int n)
{
  for (int i = 2; i*i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
}

int nextPrime(int n)
{
  for (; !isPrime(n); n++);
  return n;
}

// Your code

struct hashset* initialize_set (int size)  
{
// TODO create initial hash table
  printf("initialize_set begining...\n");
  struct hashset * set = malloc(sizeof(struct hashset));
  if(!set){
    printf("initialize_zet error: Memory allocation failed!\n");
    exit(0);
  }
  int n_size = nextPrime(size);
  set->cells = (cell*) (malloc(sizeof(cell) * n_size));
  if(!set->cells){
    printf("initialize_zet error: Memory allocation failed!\n");
    exit(0);
  }
  set->size = n_size;
  set->num_entries = 0;

  for(int i = 0; i < set->size; ++i){
    set->cells[i].state = empty;
    set->cells[i].element = NULL;
  }
  printf("initialize_set done!\n");
  return set;
}

void tidy(struct hashset* set)
{
// TODO tidy up
  if(set){
    for(int i = 0; i < set->size; ++i){
      if(set->cells[i].state == in_use){
        set->cells[i].state = deleted;
        if(set->cells[i].element != NULL) {
          free(set->cells[i].element);
          set->cells[i].element = NULL;
        }
      }
    }
    if(set->cells != NULL) {
      free(set->cells);
      set->cells = NULL;
    }
    if(set) {
      free(set);
      set = NULL;
    }
    printf("free_done\n");
  }
}

int size(struct hashset* set){
// TODO return number of values stored in table
  return set->num_entries;
} 
struct hashset* resizing(struct hashset* set){
  printf("hash set resizing begining!\n");
  int oldsize = set->size;
  int newsize = oldsize * 2;
  struct hashset* newSet = initialize_set(newsize);
  for(int i = 0; i <= set->size; ++i){
    if(set->cells[i].state == in_use){
      Value_Type value = set->cells[i].element;
      insert(value, newSet);
    }
  }
  tidy(set);
  printf("hash set resized!\n");
  return newSet;
}
int hashKeyA(Value_Type value){
  //first method is using the acii value of the code
  //find the total then mod it using how many characters there were.
  int characterCount = 0;
  int asciiTotal = 0;
  //convert to string
  char* value2String = value;
  sscanf(value, "%s", value2String);
  while (*value2String)
  {
    /* code */
    int thisValue = (int)* value2String;
    value2String++;
    characterCount++;
    asciiTotal += thisValue;
  }
  int keyA = asciiTotal % characterCount;
  return keyA;
}
int powerMethod(int value, int power){
  if(power == 0) return 1;
  if(power == 1) return value;
  if(power > 1){
    int multiply;
    int multiplyTotal = value;
    for(multiply = 2; multiply < power; ++multiply) multiplyTotal *= value;
    return multiply;
  }
  return 0;
}
int hashKeyB(Value_Type value){
  //second metho using the power method as discussed in lectures
  //take the ascii code and multiply by itself by the position in the string.(weighted)
  int characterCount = 0;
  int asciiTotal = 0;
  //convert to string
  char* value2string = value;
  sscanf(value, "%s", value2string);
  while (*value2string)
  {
    /* code */
    int thisValue = (int)*value2string;
    thisValue = powerMethod(thisValue, characterCount);
    value2string++;
    characterCount++;
    asciiTotal += thisValue;
  }
  int keyB = asciiTotal % characterCount;
  return keyB;
}
struct hashset* insert (Value_Type value, struct hashset* set)
{
// TODO code for inserting into hash table 
  printf("hash_set insert!\n");
  if(set->num_entries > set->size){
    printf("No Room left in Hash Set \n");
    set =  resizing(set);
  }
  int key;
  if(mode == HASH_1_LINEAR_PROBING){
    key = hashKeyA(value);
  }
  else{
    key = hashKeyB(value);
  }
  //if cells is empyt - fill with value
  if(set->cells[key].state == empty){
    set->cells[key].element = strdup(value);
    set->cells[key].state = in_use;
    set->num_entries++;
    printf("hash set insert done!\n");
    return set;
  }
  else if(set->cells[key].state == in_use){
    //check if the values are the same - if so don't add to the hashset
    if(strcmp(value, set->cells[key].element) == 0) return set;
    // if they are different - use linear probing to go along the set and find next available space
    collisionTotal++;
    while (set->cells[key].state == in_use){
      key++;
      if(key >= set->size){
        printf("element could not be inserted...\n");
        set = resizing(set);
      }
    }
    set->cells[key].element = strdup(value);
    set->cells[key].state = in_use;
    set->num_entries++;
    printf("hash set insert done!\n");
    return set;
  }
  return set;
}

bool find (Value_Type value, struct hashset* set)
{
// TODO code for looking up in hash table
  int key;
  //method very similar to insert see above.
  //key dependent on the mode chosen
  if(mode == HASH_1_LINEAR_PROBING){
    key = hashKeyA(value);
  }
  else key = hashKeyB(value);
  if(key < set->size && set->cells[key].element && strcmp(value, set->cells[key].element) == 0){
    return true;
  }
  else{
    //cycle through the elements after this and find see if it is present.
    while (key != set->size)
    {
      /* code */
      if(set->cells[key].state != empty){
        if(strcmp(value, set->cells[key].element) == 0){
          return true;
        }
      }
      key++;
    }
    return false;
  }
}

void print_set (struct hashset* set)
{
// TODO code for printing hash table
  for(int i = 0; i < size(set); ++i){
    if(set->cells[i].state == in_use){
      printf("element at position %d is %s \n", i, set->cells[i].element);
    }
  }
}

void print_stats (struct hashset* set)
{
// TODO code for printing statistics
  printf("print stats \n");
  printf("total number of cells is %d\n", set->size);
  printf("total number of used cells is %d\n", size(set));
  printf("total number of collions on insertion are %d\n", collisionTotal);
}
