/* 
 * function implementation of swap() function
 * seen in cpp but no in C by default. 
 * This function swaps the two numbers passed in
 */

int swap(int *dataOne, int *dataTwo) {
    int swap = *dataOne;
    *dataOne = *dataTwo;
    *dataTwo = swap;
    return 0;
}

