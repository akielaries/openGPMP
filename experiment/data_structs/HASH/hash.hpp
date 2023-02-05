#ifndef HASH_TABLE_DATA_STRUCTURE_H
#define HASH_TABLE_DATA_STRUCTURE_H
// Hash table stuct
typedef struct hash_table hash_table;

// Hash table entry (slot may be filled or empty).
typedef struct {
    const char *key; // key is NULL if this slot is empty
    void *value;
} hash_table_entry;

// Hash table structure
struct hash_table {
    hash_table_entry *entries; // hash slots
    int capacity;              // size of _entries array
    int length;                // number of items in hash table
};

// TO DO in C file
/*
Name: hash_table_create
Process: Create hash table (allocates memory) and return pointer to it,
or NULL if out of memory
Function input/parameters:
Function output/parameters:
Function output/returned: created hash_table*
Device input/file: none
Device output/monitor: none
Dependencies: malloc, calloc, free
*/
hash_table *hash_table_create(void);

// Free memory allocated for hash table
void hash_table_destroy(hash_table *table);

// Get item with given key (NUL-terminated) from hash table. Return
// value (which was set with hash_table_set), or NULL if key not found.
void *hash_table_get(hash_table *table, const char *key);

// TO DO in C file
/*
Name: hash_table_create
Process: Set item with given key to hash(value). Terminate if key or hash
is null, If not already present in table, key is copied to newly allocated
memory Return address of copied key, or NULL if out of memory. Function
input/parameters: table, key, hash(value) Function output/parameters:
Function output/returned: call to hash_table_set_entry or NULL
Device input/file: none
Device output/monitor: none
Dependencies: hash_table_expand, hash_table_set_entry
*/
const char *hash_table_set(hash_table *table, const char *key,
                           void *value);

// TO DO in C file
/*
Name: hash_table_length
Process: return number of items in hash table.
Function input/parameters: hash_table
Function output/parameters:
Function output/returned: created hash_table*
Device input/file: none
Device output/monitor: table length
Dependencies:
*/
int hash_table_length(hash_table *table);

// TO DO in C file
/*
Name: key_to_hash
Process: Takes in key and produces hash via hash function,
details on hash function provided separately
Function input/parameters: key
Function output/parameters:
Function output/returned: hash
Device input/file: none
Device output/monitor: none
Dependencies: strlen
*/
void *key_to_hash(const char *key);

#endif