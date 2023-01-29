/* function implementation of compareData function
 */

/*
Name: compareData
Process: compares data, returns value greater than 0 if dataOne is larger
than dataTwo, returns value less than 0 if dataOne is less than dataTwo,
and returns 0 is data are the same.
Function input/parameters: the two values to be compared (int)
Function output/parameters: none
Function output/returned: value as specified (int)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/


int compareData(int dataOne, int dataTwo) {
    if (dataOne > dataTwo) {
        return 1;
    }
    if (dataOne < dataTwo) {
        return -1;
    }
    else {
        return 0;
    }
}

