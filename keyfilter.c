#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



int main() {
  // file pointer
  FILE* fptr = stdin;

  // buffer to hold each line of input
  char data[101];

  while(fgets(data, 101, fptr) != NULL ){
    
    
    // finding \n in buffer data[];
    // returns pointer (address) to first occurrence of \n
    char* newline = strchr(data, '\n');
    
    // if \n found, replace it with \0 
    if(newline != NULL){  
      *newline = '\0';
    }

    printf("%s", data);
  }

  
  fclose(fptr);

  
  return 0;
}
