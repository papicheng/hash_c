#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "global.h"
#include "bstree.h"

//2 variables to find the average number of comparions
int comparision = 0;
int found = 0;

// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}


struct bstree* initialize_set (int size)  
{
  // An empty tree is represented by NULL
  return NULL;
}

void tidy(struct bstree* tree)
{
  if(tree){
    tidy(tree->left);
    tidy(tree->right);
    // assumes tree owns value memory
    free(tree->value);
    free(tree);
  }
}

int size(struct bstree* tree){
  if(tree){
    return 1 + size(tree->left) + size(tree->right);
  }
  return 0;
} 

struct bstree* insert (Value_Type value, struct bstree* tree)
{
  if(tree){
    // TODO if tree is not NULL then insert into the correct sub-tree
    if(compare(value, tree->value) < 0){
      tree->left = insert(value, tree->left);
      tree->height++;
    }
    //if the value is greater, insert to right tree
    if(compare(value, tree->value) > 0){
      tree->right = insert(value, tree->right);
      tree->height++;
    }
    //if the value is a duplicate, don't inset it
    if(compare(value, tree->value) == 0) return tree;
  }
  else{
    // TODO otherwise create a new node containing the value
    tree = (struct bstree*) malloc(sizeof(struct bstree));
    //check if memory was allocated
    if(tree){
      //strdup, it basically retruns a pointer to the duplicated value
      tree->value = strdup(value);
      tree->left = initialize_set(0);
      tree->right = initialize_set(0);
      tree->height = 0;
    }
    else
    {
      printf("%s can't be inserted as memory could not be allocated.\n", value);
    }
  }
  return tree;
}

bool find (Value_Type value, struct bstree* tree)
{
  if(tree){
    //TODO complete the find function
    comparision++;
    if(compare(value, tree->value) == 0){
      found++;
      return true;
    }
    // if the value to be found is less than the value of the node in the tree, go down into the left sub tree.
    comparision++;
    if(compare(value, tree->value) < 0){
        bool foundLeft = find(value, tree->left);
        if(foundLeft) return true;
    }
    //if the value is greater, go down into right tree
    comparision++;
    if(compare(value, tree->value) > 0){
      bool foundRight = find(value, tree->right);
      if(foundRight) return true;
    }
  }
  // if tree is NULL then it contains no values
  return false;
}

// You can update this if you want
void print_set_recursive(struct bstree* tree, int depth)
{
  if(tree){
    for(unsigned i=0;i<depth;i++){ printf(" "); }
    printf("%s\n",tree->value);
    print_set_recursive(tree->left,depth+1);
    print_set_recursive(tree->right,depth+1);
  }
} 
// You can update this if you want
void print_set (struct bstree* tree)
{
 printf("Tree:\n");
 print_set_recursive(tree,0);
}

void print_stats (struct bstree* tree)
{
 // TODO update code to record and print statistics
  printf("size of tree: %d\n", size(tree));
  printf("Height of tree : %d \n", tree->height);
  if(found != 0){
    float average_comparisons = comparision / found;
    printf("average number of comparisions:%f\n", average_comparisons);
  }
}
