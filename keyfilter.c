#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LENGHT 101
#define ADDRESSES_ROWS 42

struct Address{
  char buffName[NAME_LENGHT];
};

int main() {
    
  FILE* pFile = stdin;
  
  struct Address addresses[ADDRESSES_ROWS];
  
  int filled_address = 0;
  char temp_buff[NAME_LENGHT]; // temp buffer

  while((fgets(temp_buff, NAME_LENGHT, pFile) != NULL) && (filled_address < ADDRESSES_ROWS)){
    
    // replacing \n for \O + filling up the 
    temp_buff[strcspn(temp_buff, "\n")] = '\0';
    strcpy(addresses[filled_address].buffName, temp_buff);

    printf("%s", addresses[filled_address].buffName);

    filled_address++;
  }

  if((filled_address >= ADDRESSES_ROWS) && (fgets(temp_buff, NAME_LENGHT, pFile))){
    printf("Too much addresses...:(");
  }

  return 0;
}
