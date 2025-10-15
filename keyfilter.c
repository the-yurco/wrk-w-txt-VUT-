#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define NAME_LENGHT 101
#define ADDRESSES_ROWS 42

struct Address{
  char buffName[NAME_LENGHT];
};

// checks wether str starts with prefix + ignoring big/small lethers
bool starts_with(const char* str, const char* prefix){
  if(strlen(str) < strlen(prefix)) return false;

  int i = 0;

  while(prefix[i] != '\0'){
    if(tolower(str[i]) != tolower(prefix[i])) return false;
    i++;
  }

  return true;
}

int main(int argc, char* argv[]) {
  char* prefix = (argc > 1) ? (argv[1]) : "";
  printf("%s\n", prefix);

  FILE* pFile = stdin; 
  struct Address addresses[ADDRESSES_ROWS];
  
  int filled_address = 0;
  char temp_buff[NAME_LENGHT]; // temp buffer

  while((fgets(temp_buff, NAME_LENGHT, pFile) != NULL) && (filled_address < ADDRESSES_ROWS)){
    
    // replacing \n for \O + filling up the 
    temp_buff[strcspn(temp_buff, "\n")] = '\0';
    strcpy(addresses[filled_address].buffName, temp_buff);

    // printf("%s", addresses[filled_address].buffName);

    filled_address++;
  }

  if((filled_address >= ADDRESSES_ROWS) && (fgets(temp_buff, NAME_LENGHT, pFile))) printf("Too much addresses...:(");
  
  for(int i = 0; i < filled_address; i++){
    if(starts_with(addresses[i].buffName, prefix)){
      printf("- %s\n", addresses[i].buffName);
    }
  }

  return 0;
}
