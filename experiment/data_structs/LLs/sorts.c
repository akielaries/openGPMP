// header files
#include <stdio.h>
#include <stdlib.h> // malloc/free
#include <time.h>
#include <string.h>
#include <stdbool.h>

// global constants
const int MAX_CAPACITY = 150000;
// data structure
typedef struct PasswordTypeStruct
   {
       
    int rank;
    unsigned long long int password;
    struct PasswordTypeStruct *nextPtr;
   } PasswordType;
   
// function declaration
PasswordType *importData(int size); // provided
void writeDataToFile(PasswordType *headPtr, FILE *fileName);
PasswordType *clearLinkedList(PasswordType *wkgPtr);
int compareData(int dataOne, int dataTwo);


// Students to write
void filterNonDigitCharacters(char inData[], char outData[]);
bool passwordLengthTest(char password[]);
unsigned long long int stringToNumber(char inStr[]);

PasswordType *runQuickSort(PasswordType *headPtr);
PasswordType *partition(PasswordType *wkgPtr, PasswordType **newHead);
PasswordType *mergeSort(PasswordType *headPtr);
PasswordType *runMerge(PasswordType *listOne, PasswordType *listTwo);
void splitLinkedList(PasswordType *headPtr, PasswordType **firstHeadPtr,
                                                 PasswordType **secondHeadPtr);
                                                 
// main driver
int main()
{
    // initialize variables
    int size;
    PasswordType *headPtr = NULL;
    FILE *mergeSortOutputFile, *quickSortOutputFile;
    clock_t startTime, endTime;
    double totalTime;
    
    // prompt for sizeof
    printf("Enter the number of values to be sorted: ");
	scanf("%d", &size);
    
    
    // check for size > 0
    if (size > 0 && size <= MAX_CAPACITY)
    {
        // import data into linked list
        headPtr = importData(size);
        // check for headPtr not null
        if(headPtr != NULL)
        {
            // open merge sort output file
            mergeSortOutputFile = fopen("mergeSortLL.csv", "w+");
            // write merge sort title to file
            fprintf(mergeSortOutputFile, "Linked List Merge Sort:\n");
            // start timer
            startTime = clock();
            // sort data
            headPtr = mergeSort(headPtr);
            endTime = clock();
            // calculate difference to get total
            totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            // write length of time to sort to file
            fprintf(mergeSortOutputFile, 
                 "It took %f seconds to sort %d elements.\n", totalTime, size);
            // write data to file
            writeDataToFile(headPtr, mergeSortOutputFile);
            // close file
            fclose(mergeSortOutputFile);
            // display success message to console
            printf("\nData written to mergeSortLL.csv\n");
            // clear list
            headPtr = clearLinkedList(headPtr);
        }
        // otherwise, headPtr is null
        else
        {
            printf("\nError: no data found.\n");
        }

        headPtr = importData(size);
        if (headPtr != NULL)
        {
            quickSortOutputFile = fopen("quickSortLL.csv", "w+");
            fprintf(quickSortOutputFile, "Linked List Quick Sort:\n");
            startTime = clock();
            headPtr = runQuickSort(headPtr);
            endTime = clock();
            totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            fprintf(quickSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", totalTime, size);
            writeDataToFile(headPtr, quickSortOutputFile);
            fclose(quickSortOutputFile);
            printf("\nData written to quickSortLL.csv\n");
            headPtr = clearLinkedList(headPtr);
        }
        else 
        {
            printf("\nError: No data found.\n");
        }

    }
    // otherwise, size is not valid
    else
    {
        // display error message
        printf("\nIncorrect input.\n");      
                
    }
    
    printf("\nEnd program\n");
    //return fuctions success
    return 0;
}

// function implementations

int compareData(int dataOne, int dataTwo)
{
    return dataOne - dataTwo;
}

void filterNonDigitCharacters(char inData[], char outData[])
{
    // initialize variables
    int strLen, index, outputIndex = 0;
   
    // get str length
    strLen = strlen(inData);
    
    // loop across string
    for (index = 0; index < strLen; index++)
    {       
        // test each character to see if it is a digit character
        if(inData[index] >= '0' && inData[index] <= '9')
        {
            // replace char
            outData[outputIndex] = inData[index];
            
            outputIndex++;
        }
    }
    
    outData[outputIndex] = '\0';
   
    // void, no return

}

bool passwordLengthTest(char password[])
{

    // return test to determine if it is 4 or more characters
    return strlen(password) >= 4;
}

PasswordType *clearLinkedList(PasswordType *wkgPtr)
{
    PasswordType *ptr = wkgPtr;

    while( ptr != NULL )
    {
        wkgPtr = wkgPtr->nextPtr;

        free(ptr);

        ptr = wkgPtr;
    }
    
    return NULL;

}

PasswordType *importData(int size)
{
    // initialize variables
    FILE *inputFile;
    int index = 1, rank;
    unsigned long long int finalPassword;
    char comma, password[40], filteredPassword[40];
    PasswordType *previousNodePtr, *nextNodePtr, *headPtr = NULL;
    
    // allocate memory for next node
    previousNodePtr = (PasswordType *)malloc(sizeof(PasswordType));
    
    // open input file
    inputFile = fopen("HW2_UNSORTED.txt", "r");
    
    // prime loop for reading in data
    // read in first number
    fscanf( inputFile, "%d", &rank );
    
    // capture comma
    fscanf( inputFile, "%c", &comma );
    
    // read in second number
    fscanf( inputFile, "%s", password );
    
    filterNonDigitCharacters(password, filteredPassword);
    
    // loop to ensure data is correct length after filtering
    while( !passwordLengthTest(filteredPassword) )
    {
        fscanf( inputFile, "%d", &rank );
    
        // capture comma
        fscanf( inputFile, "%c", &comma );
        
        // read in second number
        fscanf( inputFile, "%s", password );

        filterNonDigitCharacters(password, filteredPassword);

    }
    
    // convert password to integer
    finalPassword = stringToNumber(filteredPassword);

    // put data into node
    previousNodePtr->rank = rank;
    previousNodePtr->password = finalPassword;
    previousNodePtr->nextPtr = NULL;
    
    // assign headPtr
    headPtr = previousNodePtr;
    
    // enter loop to read in the rest of the data
    while(index < size)
    {
        // allocate new node
        nextNodePtr = (PasswordType *)malloc(sizeof(PasswordType));
        
        // set point list at new node
        previousNodePtr->nextPtr = nextNodePtr;
        
        // get data for next node
        // read in first number
        fscanf( inputFile, "%d", &rank );
        
        // capture comma
        fscanf( inputFile, "%c", &comma );
        
        // read in second number
        fscanf( inputFile, "%s", password );
        
        filterNonDigitCharacters(password, filteredPassword);

        
        // loop to ensure data is correct length after filtering
        while(!passwordLengthTest(filteredPassword))
        {
            
            fscanf( inputFile, "%d", &rank );
        
            // capture comma
            fscanf( inputFile, "%c", &comma );
            
            // read in second number
            fscanf( inputFile, "%s", password );
            
            filterNonDigitCharacters(password, filteredPassword);
        }
        
        // convert password to integer
        finalPassword = stringToNumber(filteredPassword);
        
        // put data into node
        nextNodePtr->rank = rank;
        nextNodePtr->password = finalPassword;
        nextNodePtr->nextPtr = NULL;
        
        previousNodePtr = nextNodePtr;
        
        index++;
    }
   
    return headPtr;
}

void writeDataToFile(PasswordType *headPtr, FILE *fileName)
{
    // initialize variables
    PasswordType *wkgPtr = headPtr;
    
    // loop across specified elements
    while(wkgPtr != NULL)
    {
        // write data pair to file
        fprintf( fileName, "%d, %I64llu\n", wkgPtr->rank, wkgPtr->password);
        
        wkgPtr = wkgPtr->nextPtr;

    }
    
    // void, no return
}

unsigned long long int stringToNumber(char inStr[])
{
    int strLen, strIndex;
    unsigned long long int result = 0;
    
    strLen = strlen(inStr);
        
    for(strIndex = 0; strIndex < strLen; strIndex++)
    {
       result = (result * 10 ) + (inStr[strIndex] - '0');
    }
        
    return result;
}
/*
Name: runQuickSort
Process: sorts the data using quick sort algorithm

Function input/parameters: headPtr of list to be sorted
Function output/parameters: none
Function output/returned: updated head pointer
Device input/file: none
Device output/monitor: none
Dependencies: runPartition, runQuickSort (recursive)

will want a traversal pointer and putting that value 
in front of head if trav < pivot
*/
PasswordType *runQuickSort(PasswordType *headPtr)
{
    // initialize variables
    // declare pivot and newHeadPtr 
    PasswordType *pivot, *newHeadPtr;
    PasswordType *tempPtr = headPtr;
    //PasswordType *newHead = NULL;
    
    // check for headPtr != NULL, and headPtrs next ptr is not null
    if (headPtr != NULL && headPtr->nextPtr != NULL)
    {
        // partition data passing in the current head and the new
        pivot = partition(headPtr, &newHeadPtr);
        
        // update headPtr
        headPtr = newHeadPtr; 

        // check to see if the first node in the list is not the pivot
        if (headPtr != pivot) 
        {   

            // loop up to find node before pivot
            while (headPtr->nextPtr != pivot)
            {            
                // split the list
                //headPtr->nextPtr = NULL;    
                // sort left side of the list runQuickSort()
                //runQuickSort(headPtr);
                // find the end of the list, and attach pivot node to it
                //while (headPtr->nextPtr == NULL)
                   // pivot = headPtr->nextPtr;
                // increment headPtr 
                headPtr = headPtr->nextPtr;
            }
            
            // split the list
            headPtr->nextPtr = NULL;
            // sort left side
            runQuickSort(headPtr);
            // find end of list
            while (headPtr->nextPtr != NULL)
                // attach pivot to it
                pivot = headPtr->nextPtr;

        }
        // check to see if there are nodes after pivot (right side needs to be sorted)
        if (pivot->nextPtr != NULL)
        {
            // sort right side with runQuickSort() calling with node after pivot
            runQuickSort(pivot->nextPtr);
            //pivot = headPtr->nextPtr;
        }
    }
    // return ptr to the updated headPtr of the list
    return newHeadPtr;

}
/* 
Name: partition
Process: partitions the data according to quicksort algorithm. Uses first node in list as
                                 partition value (if a particular node is smaller that the
                                                  partition, it is reassigned in front of it)
                                                  
                                                  hint: remember to update headPtr
Function input/parameters: wkgPtr: pointer to beginning of list before it is partitioned
Function output/parameters: newHead, the updated headPtr of partitioned list
Function output/returned: pointer to the partition node
Device input/file: none
Device output/monitor: none
Dependencies: compareData


if data is already sorted, choosing pivot at front or back
results in worst case time complexity
*/

PasswordType *partition(PasswordType *wkgPtr, PasswordType **newHead)
{
    /* 
     *  things to keep track of here:
     *  node before current ptr
     *  head of the list (could change)
     */
    // initialize variables
    // declare head pointer set it equal to input param
    PasswordType *head = wkgPtr;
    // set new hew input param to empty, will be updating later
    // *newHead = NULL;
    // declare pivot pointer which is our first node
    PasswordType *pivot = wkgPtr;
    // set prevPtr to first node in the list
    PasswordType *prevPtr = wkgPtr;
    // declare current ptr set equal to 2nd element; acts as loop ptr 
    //PasswordType *currentNode = wkgPtr->nextPtr;
    PasswordType *currentNode = wkgPtr;
    // declare temp ptr 
    PasswordType *tempPtr = NULL;
    // declaring index variable as a cheat 
    int sortIndex = 0;

    // check for working ptr not null
    if (wkgPtr != NULL)
    { 
        // loop cross the list while currentNode is not null 
        while (currentNode != NULL)
        {
            // check to see if rank at loop ptr is less than rank at pivot
            if (currentNode->rank < pivot->rank)
            {
                // point current node at the head of the list (make current node new head)
                // set tempPtr to currentPtr->nextPtr
                tempPtr = currentNode->nextPtr;
                // set the next node of current as the head
                currentNode->nextPtr = head;
                // set prev nodes next node as the current nodes next
                prevPtr->nextPtr = currentNode->nextPtr;    

                // update head ptr making current the head
                head = currentNode;        
                // set prevPtr's nextPtr to the tempPtr
                prevPtr->nextPtr = tempPtr;
                // update the current ptr to be prevPtr->nextPtr
                currentNode = prevPtr->nextPtr;
            } 
            // otherwise, rank at loop ptr is larger than rank at pivot
            else
            {
                // advance currentNode
                currentNode = currentNode->nextPtr;
                // advance prevPtr
                if (sortIndex > 0) 
                {
                    prevPtr = prevPtr->nextPtr;
                }
            }
            sortIndex++;
        }
    }
    // update headPtr (output param)
    *newHead = head;
    // return pivot
    return pivot;
}

PasswordType *mergeSort(PasswordType *headPtr)
{
    // initialize variables
    PasswordType *leftHeadPtr, *rightHeadPtr, *head = headPtr;
    
    if(head != NULL && head->nextPtr != NULL)
    {
        splitLinkedList(head, &leftHeadPtr, &rightHeadPtr);

        leftHeadPtr = mergeSort(leftHeadPtr);
        rightHeadPtr = mergeSort(rightHeadPtr);

        head = runMerge(leftHeadPtr, rightHeadPtr);
    }
    
    return head;
}

PasswordType *runMerge(PasswordType *listOne, PasswordType *listTwo)
{
        // initialize variables
    PasswordType *mergeNode = NULL;
    PasswordType *tempPtr = mergeNode, *onePtr = listOne, *twoPtr = listTwo;
    
    if(onePtr == NULL)
    {
        return twoPtr;
    }
    else if(twoPtr == NULL)
    {
        return onePtr;
    }
    
    // put compare and place first node
    if(compareData(onePtr->rank, twoPtr->rank) < 0)
    {
        mergeNode = onePtr;
        
        onePtr = onePtr->nextPtr;
        
        mergeNode->nextPtr = NULL;
    }
    else
    {
        mergeNode = twoPtr;
        
        twoPtr = twoPtr->nextPtr;
        
        mergeNode->nextPtr = NULL;

    }
    
    tempPtr = mergeNode;

    // loop across both lists
    while(onePtr != NULL && twoPtr != NULL)
    {
        

        // assign smaller node to list
        if(compareData(onePtr->rank, twoPtr->rank) < 0)
        {

            tempPtr->nextPtr = onePtr;
            
            onePtr = onePtr->nextPtr;
        }
        
        else
        {
           
           tempPtr->nextPtr = twoPtr;
            
            twoPtr = twoPtr->nextPtr;
            
           
        }
        
        tempPtr = tempPtr->nextPtr;
    }
        
    // loop across list one
    if(onePtr != NULL)
    {
        // assign node to list
        tempPtr->nextPtr = onePtr;
    }
    
    // loop across list two
   if (twoPtr != NULL)
    {
        // assign node to list
        tempPtr->nextPtr = twoPtr;
    }
    
        
    return mergeNode;
}

void splitLinkedList(PasswordType *headPtr, PasswordType **firstHeadPtr,
                                                  PasswordType **secondHeadPtr)
{
    // initialize variables
    PasswordType *middlePtr = headPtr, *endPtr = headPtr->nextPtr;
    
    if(headPtr != NULL)
    {
        while(endPtr != NULL)
        {
            endPtr = endPtr->nextPtr;
            
            if(endPtr != NULL)
            {
                middlePtr = middlePtr->nextPtr;
                endPtr = endPtr->nextPtr;
            }
        }

        // reassign ptrs for output parameter
        *firstHeadPtr = headPtr;
        *secondHeadPtr = middlePtr->nextPtr;

        // split list in half
        middlePtr->nextPtr = NULL;
        
    }
    // void, no return
}
