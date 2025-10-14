#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ROW_LENGHT 101

int main() {
    
  FILE* pFile = stdin;
  char buffAddresses[ROW_LENGHT];

  while(fgets(buffAddresses, ROW_LENGHT, pFile) != NULL){
    printf("%s", buffAddresses);
  }

  return 0;
}
