#include "utility.h"

void out_of_memory(void) {
    fprintf(stderr, "Out of memory\n");
    exit(1);
}

void data_stats(FILE *file_name, int *counted_row_size,
                int *counted_rows) {
    printf("START: %s\n", __func__);
    // initializing variables
    int char_counter = 0;
    int row_count = 0;
    char temp_char;
    int max_char_counter = 0;

    while (temp_char != EOF) {
        temp_char = fgetc(file_name);
        // printf("%c\t", temp_char);

        if (temp_char == '\n' || temp_char == EOF) {
            // printf("\n");
            char_counter = 0;
            row_count++;
            // printf("row count: %d\n", row_count);
        } else {
            char_counter++;
            // printf("char_count: %d\t", char_counter);
            if (max_char_counter < char_counter) {
                max_char_counter = char_counter;
            }
        }
    }
    // printf("\n");

    // +1 for \n
    *counted_row_size = max_char_counter + 1;
    // devided by 2 sine we counted both commas and end line chars
    *counted_rows = row_count;
    printf("%s: Max characters in the row: %d\n", __func__,
           (max_char_counter + 1));
    printf("%s: Total rows in the file: %d\n", __func__, row_count);
    printf("DONE: %s\n", __func__);
}

void test_function(int adjusted_row_size) {
    printf("\n%s\n", __func__);
    printf("\n%d\n", adjusted_row_size);
}

char data_file[3][20] = {"case_1_data.txt\0", "case_2_data.txt\0",
                         "case_3_data.txt\0"};
//	There is nothing below this point

int case_4() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");
    for (;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g -
                             l * d * n);
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\n\r");
        for (k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000);
    }
    return 0;
}
