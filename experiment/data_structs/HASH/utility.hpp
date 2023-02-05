#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef UTILITY_H
#define UTILITY_H
// Defenitions:
#define HASH_TABLE_INITIAL_CAPACITY 1000
#define OUT_FILE_NAME "hash_table.csv"
// #define IN_FILE_NAME "case_1_data.txt"
// #define SECTION_END "\t==========END==========\n\n"

void data_stats(FILE *file_name, int *counted_row_size, int *counted_rows);
void out_of_memory(void);
// void is_key_present();
void test_function(int adjusted_row_size);
char data_file[3][20];
int case_4();
#endif