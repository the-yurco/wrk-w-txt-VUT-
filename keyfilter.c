#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <strings.h>

#define NAME_LENGTH 101
#define ADDRESSES_ROWS 42
#define MAX_CHARS 27

struct Address {
    char buffName[NAME_LENGTH];
};

// Checks whether str starts with prefix
bool starts_with(const char* str, const char* prefix) {
    if (strlen(str) < strlen(prefix)) return false;

    int i = 0;
    while (prefix[i] != '\0') {
        if (tolower(str[i]) != tolower(prefix[i])) return false;
        i++;
    }
    return true;
}

// Checks for exact match
bool is_exact_match(const char* str, const char* prefix) {
    return strcasecmp(str, prefix) == 0;
}

// Collects unique next characters after the prefix
void collect_next_chars(char* next_chars, int* char_count, struct Address* addresses, int filled, const char* prefix) {
    *char_count = 0;
    size_t prefix_length = strlen(prefix);

    for (int i = 0; i < filled; i++) {
        if (starts_with(addresses[i].buffName, prefix) && strlen(addresses[i].buffName) > prefix_length) {
            char next_char = tolower(addresses[i].buffName[prefix_length]);        
            int unique = 1;

            // Check if the char is already in the array
            for (int j = 0; j < *char_count; j++) {
                if (next_chars[j] == next_char) {
                    unique = 0;
                    break;
                }
            }
            
            // If unique, add it to the array
            if (unique) {
                next_chars[(*char_count)++] = next_char;
            }
        }
    }
    
    next_chars[*char_count] = '\0';  
}

// Sorts chars (ASC)
void sort_chars(char* chars, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (chars[i] > chars[j]) {
                char temp = chars[i];
                chars[i] = chars[j];
                chars[j] = temp;
            }
        }
    }
}

void print_found(const char* prefix) {
    fprintf(stderr, "Found: %s\n", prefix);
}

void print_enable(const char* chars) {
    fprintf(stderr, "Enable: %s\n", chars);
}

void print_not_found() {
    fprintf(stderr, "Not found\n");
}

void handle_error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int main(int argc, char* argv[]) {
    const char* prefix = (argc > 1) ? argv[1] : "";

    struct Address addresses[ADDRESSES_ROWS];
    int filled_address = 0;
    char temp_buff[NAME_LENGTH];

    while (fgets(temp_buff, NAME_LENGTH, stdin) != NULL && filled_address < ADDRESSES_ROWS) {
        temp_buff[strcspn(temp_buff, "\n")] = '\0';
        strcpy(addresses[filled_address].buffName, temp_buff);
        filled_address++;
    }

    // Error check
    if (filled_address >= ADDRESSES_ROWS && !feof(stdin)) {
        handle_error("Too many addresses...:p");
    }

    int match_count = 0;
    int exact_found = 0;
    
    for (int i = 0; i < filled_address; i++) {
        if (starts_with(addresses[i].buffName, prefix)) {
            match_count++;
            if (is_exact_match(addresses[i].buffName, prefix)) {
                exact_found = 1;
            }
        }
    }

    char next_chars[MAX_CHARS];
    int char_count = 0;
    collect_next_chars(next_chars, &char_count, addresses, filled_address, prefix);
    sort_chars(next_chars, char_count);

    // Output results
    if (match_count == 0) {
        print_not_found();
    } else {
        if (exact_found) {
            print_found(prefix);
        }
        if (char_count > 0) {
            print_enable(next_chars);
        }
    }

    return 0;
}
