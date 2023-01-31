#include "utility.h"
#include "hash_table_data_structure.h"

// Declaration of static functions
static const char* hash_table_set_entry(hash_table_entry* entries,
										int capacity,
										const char* key,
										void* value, int* plength);
										
static bool hash_table_expand(hash_table* table);

// TO DO
hash_table* hash_table_create(void)
{
    printf("\n\nSTART: %s\n", __func__);
	printf("%s: Hash table is created\n",__func__);
    // Allocate memory for hash table struct
	// CODE HERE
	hash_table* table = malloc(sizeof(hash_table));
	printf("%s: Memmory alocation is successfull\n",__func__);

    if (table == NULL) {
		printf("%s: ERROR: Table was not created\n", __func__);
        return NULL;
    }


	// Set initial table length
	// CODE HERE
    table->length = 0;

	// Set initial table capacity
	// CODE HERE
    table->capacity = HASH_TABLE_INITIAL_CAPACITY;

    // Allocate space for table entries and fill them with zeroes
	// CODE HERE
    table->entries = calloc(table->capacity, sizeof(hash_table_entry));

    if (table->entries == NULL)
	{
		// Error!
		// Free table before we return
        free(table);
		printf("%s: ERROR: Table was not created\n", __func__);
        return NULL;
    }
	printf("DONE: %s\n", __func__);

	// return
    return table;
}

void hash_table_destroy(hash_table* table)
{
	printf("\n\nSTART: %s\n", __func__);
    // Free allocated keys
    for (int iterator = 0; iterator < (table->capacity); iterator++)
	{
        free((void*)table->entries[iterator].key);
    }

    // Then free entries array and table itself.
    free(table->entries);
    free(table);
	printf("DONE: %s\n", __func__);
}


// TO DO
int hash_table_length(hash_table* table)
{
	// CODE HERE
    return table->length;
}

// TO DO
void* key_to_hash(const char* key) {
	
	// initialize variables

	// initialize variables
	// CODE HERE
    void* hash = 0;

    // Iterate through chars in key and transform it into hash
	// CODE HERE (loop)
    for(int current_char = 0; current_char < strlen(key); current_char++)
	{
			hash = hash + key[current_char];
    }
	// Return
	// CODE HERE
    return hash;
}

// TO DO
const char* hash_table_set(hash_table* table, const char* key, void* value)
{
    // If value NULL reutrn NULL
	// CODE HERE (if)
	if (value == NULL)
	{
        return NULL;
    }

    // If length exceed half of current capacity, expand it
	// CODE HERE (nested if)
    if (table->length >= (table->capacity / 2))
	{
        if (!hash_table_expand(table))
		{
            return NULL;
        }
    }

    // Set entry and update length via hash_table_set_entry
	// CODE HERE
    return hash_table_set_entry(table->entries,
								table->capacity,
								key, value,
								&table->length);
}


void* hash_table_get(hash_table* table, const char* key)
{
	// initialize variables
    int hash, index;
	
    hash = key_to_hash(key);
    index = (int)(hash & (int)(table->capacity - 1));


    // Advance in table till sure key is not in the table
    while (table->entries[index].key != NULL)
	{
		// If key matches entery
        if (strcmp(key, table->entries[index].key) == 0)
		{
            // Return value
            return table->entries[index].value;
        }
		
        // If entery do not match key
		// Probe to next via linear probing (e.g. increment index)
        index++;
        if (index >= table->capacity)
		{
            // At end of entries array, wrap around.
            index = 0;
        }
    }
    return NULL;
}




// Internal function to set an entry (without expanding table).
static const char* hash_table_set_entry(hash_table_entry* entries,
										int capacity,
										const char* key,
										void* value, int* length)
{
    int hash = key_to_hash(key);
    int index = (int)(hash & (int)(capacity - 1));

    // Loop till we find an empty entry.
    while (entries[index].key != NULL)
	{
        if (strcmp(key, entries[index].key) == 0)
		{
            // Found key alredy in the table update value
			printf("\t%s: key: %s is already in the table\n", __func__, key);
			printf("\t%s: key: %s is ignored table is not modified\n", __func__, key);
            entries[index].value = value;
            return entries[index].key;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
		printf("\t%s: hash: %d is already in the table\n", __func__, value);
		printf("\t%s: probing linearly to place hash: %d \n", __func__, value);
        if (index >= capacity)
		{
            // At end of entries array, wrap around.
            index = 0;
        }
    }

    // Didn't find key, allocate + copy if needed, then insert it.
    if (length != NULL)
	{
        key = strdup(key);
        if (key == NULL)
		{
            return NULL;
        }
        (*length)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;

    return key;
}




//TO DO
/*
Name: hash_table_expand
Process: Expands hash table to twice its current size
 Return true on success, false if out of memory.
Function input/parameters: hash_table
Function output/parameters: 
Function output/returned: created hash_table*
Device input/file: none
Device output/monitor: table length
Dependencies: 
*/
static bool hash_table_expand(hash_table* table)
{
        // Allocate new entries array increas capacity x2
	// CODE HERE
    int new_capacity = table->capacity * 2;
	// If new capacity is less than old capacity (our array is too big)
	// CODE HERE(if)
    if (new_capacity < table->capacity)
	{
		// Overflow, return false
		// CODE HERE(return)
        return false;
    }
	// Allocate memory for new_entries according to new capacity
	// CODE HERE
    hash_table_entry* new_entries = calloc(new_capacity, sizeof(hash_table_entry));
	// If new entries not created, not enough memory
	// CODE HERE(if)
    if (new_entries == NULL)
	{
		// CODE HERE(return)
        return false;
    }

    // Iterate all old entries,and move all non-empty ones to new table's entries.
	// CODE HERE (for)
    for (int cutrrent_entry = 0; cutrrent_entry < table->capacity; cutrrent_entry++)
	{
		// Copy old entries to new table entries
		// CODE HERE
        hash_table_entry entry = table->entries[cutrrent_entry];
		// If key is not NULL
        if (entry.key != NULL)
		{

            hash_table_set_entry(new_entries, new_capacity,
								entry.key, entry.value, NULL);
        }
    }

    // Free old entries array and update this table's details.
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}
