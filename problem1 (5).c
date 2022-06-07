#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SEED 1000000

void selection_sort (void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int));
int index_of_min (void *a, int low, int high, int (*compare) (void *,int,int));
void swap (void *a, int i, int j);
int compare (void *a, int i, int j);
void quick_sort(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int));
int partition(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int));
int compare_qs(void *a, int i, int j);
void swap_qs(void *a, int i, int j);
int linear_search(void *key, void *arr, int size_arr, int(*cmp)(void *,void *, int));
int intcmp_ls(void *k, void *a, int index);
int binary_search(void *arr, void *key, int l , int r, int(*cmp)(void *,void *, int));
int intcmp_bs(void *k, void *a, int index);

/*
 AUTHOR: Suchith Pinreddy, Yash Nikumb
 FILENAME: problem1.c
 SPECIFICATION: to implement a generic selection sort, generic quick sort, a generic linear search, and a generic binary search using the algorithms
 FOR: CS 2413 Data Structures Section 002
*/
int main(void) {
  int *b = (int *)calloc(SIZE,sizeof(int));
  int *temp = (int *)calloc(SIZE,sizeof(int));
  int *temp1 = (int *)calloc(SIZE,sizeof(int));
  int *temp2 = (int *)calloc(SIZE,sizeof(int));
  int *temp3 = (int *)calloc(SIZE,sizeof(int));
  printf("\nArray of Random Numbers of size %d...\n",SIZE);
  int i;
  srand(time(0));  
  for (i = 0; i < SIZE; i++) {  
    b[i] = rand()%SEED;
  }
  for (i = 0; i < SIZE; i++){
    temp[i] = b[i];
    temp1[i] = b[i];
  }
  clock_t start_time, end_time;
  //TEST CASE 1
  printf("\nSelection Sort....\n");
  start_time = clock();
  selection_sort((void *) temp,SIZE,swap,compare);     
  end_time = clock();
  printf ("\n\tmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  //printf("\nSorted array:\n");
  printf("\nQuick Sort....\n");
  start_time = clock();
  quick_sort(temp1, 0, SIZE-1, swap_qs, compare_qs);     
  end_time = clock();
  printf ("\n\tmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  for(i = 0; i < SIZE; i++){
    temp2[i] = temp[SIZE - 1 - i];
    temp3[i] = temp1[SIZE - 1 - i];
  }
  //TEST CASE 2
  printf("\nSelection Sort....\n");
  start_time = clock();
  selection_sort((void *) temp2,SIZE,swap,compare);     
  end_time = clock();
  printf ("\n\tmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  //printf("\nSorted array:\n");
  printf("\nQuick Sort....\n");
  start_time = clock();
  quick_sort(temp3, 0, SIZE-1, swap_qs, compare_qs);     
  end_time = clock();
  printf ("\n\tmain - sort took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
//TEST CASE 3
  //front
  printf("\nLinear Search Sorted Array: b[%d] = %d\n", 0, temp[0]);
  start_time = clock();
  int index = linear_search(&temp[0], temp, SIZE ,intcmp_ls);
  end_time = clock();
  printf ("\n\tmain - search took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d, sorted array temp[%d] = %d\n",index, index, temp[index]);
  //mid
  printf("\nLinear Search Sorted Array: b[%d] = %d\n", SIZE/2, temp[SIZE/2]);
  start_time = clock();
  index = linear_search(&temp[SIZE/2], temp, SIZE ,intcmp_ls);
  end_time = clock();
  printf ("\n\tmain - search took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d, sorted array temp[%d] = %d\n",index, index, temp[index]);
  //end
    printf("\nLinear Search Sorted Array: b[%d] = %d\n", SIZE-1, temp[SIZE-1]);
  start_time = clock();
  index = linear_search(&temp[SIZE-1], temp, SIZE ,intcmp_ls);
  end_time = clock();
  printf ("\n\tmain - search took %f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d, sorted array temp[%d] = %d\n",index, index, temp[index]);
  //Binary
    //front
  printf("\nBinary Search Sorted Array: b[%d] = %d\n", 0, temp1[0]);
  start_time = clock();
  index = binary_search(temp1, &temp1[0], 0, SIZE ,intcmp_bs);
  end_time = clock();
  printf ("\n\tmain - search took %.8f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d, sorted array temp1[%d] = %d\n",index, index, temp1[index]);
  //mid
  printf("\nBinary Search Sorted Array: b[%d] = %d\n", SIZE/2, temp1[SIZE/2]);
  start_time = clock();
  index = binary_search(temp1,&temp1[SIZE/2], 0, SIZE ,intcmp_bs);
  end_time = clock();
  printf ("\n\tmain - search took %.8f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d, sorted array temp1[%d] = %d\n",index, index, temp1[index]);
  //end
    printf("\nBinary Search Sorted Array: b[%d] = %d\n", SIZE-1, temp1[SIZE-1]);
  start_time = clock();
  index = binary_search(temp1,&temp1[SIZE-1], 0, SIZE ,intcmp_bs);
  end_time = clock();
  printf ("\n\tmain - search took %.8f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d, sorted array temp1[%d] = %d\n",index, index, temp1[index]);
  //TEST CASE 4
  printf("\nLinear Search Sorted Array: b[%d] + 1 = %d\n", SIZE-1, temp[SIZE-1]);
  start_time = clock();
  index = linear_search(&temp[SIZE-1] + 1, temp, SIZE ,intcmp_ls);
  end_time = clock();
  printf ("\n\tmain - search took %.8f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d\n",index);
  //binary
  printf("\nBinary Search Sorted Array: b[%d] + 1 = %d\n", SIZE-1, temp[SIZE-1]);
  start_time = clock();
  index = binary_search(temp1,&temp1[SIZE-1] + 1, 0, SIZE ,intcmp_bs);
  end_time = clock();
  printf ("\n\tmain - search took %.8f seconds\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
  printf("Index %d\n",index);
  return 0;
}

/* NAME: selection_sort
 PARAMETERS: void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int) 
 PURPOSE: It sorts the program by using selection sort
 PRECONDITION: The variables passed should be a void ptr an int value, 3 void ptrs
 POSTCONDITION: It should sort the array correctly according to the size of the array 
*/

 void selection_sort (void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int)) {
  int lowind, i, j;
  for (i = 0; i < size-1; i++) {   /* number of passes through a */
    lowind = index_of_min (a,i,size-1,compare);
    if (i != lowind)               /* swap if lowind not the same as position i */
      swap(a,i,lowind);
  }
}

/* NAME: index_of_min
 PARAMETERS: void *a, int low, int high, int (*compare) (void *,int,int)
 PURPOSE: This function computes the min index of the array for selection sort. 
 PRECONDITION:  the actual parameters passed into the main functions should be void ptrs and int value according to the functions
 POSTCONDITION: It should return the index of the minimum value in an array correctly 
*/
 int index_of_min (void *a, int low, int high, int (*compare) (void *,int,int)) {
  int lowind = low, i;
  for (i = low+1; i <= high; i++) {   /* check for smaller elements from low+1 to high */
    if (compare (a,i,lowind) < 0)
      lowind = i;
   }
   return lowind;
}

/*
 * purpose:         swap 
 * parameters:      void *a
 *                  int i   - input parameter for index of lower element in array
 *                  int j   - input parameter for index of higher element in array
 * preconditions:   i and j must be valid array indices for array a
 * postconditions:  the values in a[i] and a[j] are exchanged
 */
void swap (void *a, int i, int j) {
  int *b = (int *) a;
  int temp = b[i];
  b[i] = b[j];
  b[j] = temp;
}

/* NAME: compare
 PARAMETERS: void *a, int i, int j
 PURPOSE: The purpose of the compare the values of the array to sort 
 PRECONDITION: the values passed should be a void pointer and two int values
 POSTCONDITION: It should compare the values and sort the arrays correctly
*/
int compare (void *a, int i, int j) {
  int *b = (int *) a;
  int res = 0;
  if (b[i] < b[j])
    res = -1;
  else if (b[i] > b[j])
    res = 1;
  return (res);
}
/* NAME: partition
 PARAMETERS: void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)
 PURPOSE: it is used to partition the array to sort the array using quick sort(divide and conquer)
 PRECONDITION: It should pass void values and in according to the formal parameters in the function
 POSTCONDITION: The function should partition the array correctly according to the right and the left element
*/
int partition(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)){

  int left = start;
  int right  = end;
  int loc = start;
  int Flag = 0;
  while(Flag == 0){
      while(compare(arr, loc, right) == 1 && loc != right){
          right = right -1;
        }
      if(loc == right){
            Flag = 1;
        }
      else{
            swap(arr, loc, right);
            loc = right;
        }
      if(Flag == 0){
          while(compare(arr, loc, left) == -1 && loc != left){
              left = left + 1;
          }
          if(loc  == left){
              Flag = 1;
          }
          else{
              swap(arr, loc, left);
              loc = left;
          }
        }    
      }
      return loc;
  }
/* NAME: quick_sort
 PARAMETERS: void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)) 
 PURPOSE: It sorts the program by using quick sort using reccursion and other functions
 PRECONDITION: the variables passed should be according to the parameters in this function
 POSTCONDITION: It should sort the array correctly according to the size of the array 
*/
void quick_sort(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)){
    if(start < end){
        int loc = partition(arr, start, end, swap,compare);
        quick_sort(arr, start, loc - 1, swap, compare);
        quick_sort(arr, loc + 1, end, swap, compare);
    }
}
/* NAME: compare_qs
 PARAMETERS: void *a, int i, int j
 PURPOSE: The purpose of the compare the values of the array to sort 
 PRECONDITION: the values passed should be a void pointer and two int values
 POSTCONDITION: It should compare the values and sort the arrays correctly
*/
int compare_qs(void *a, int i, int j){
  int *b = (int *) a;
  int res = 0;
  if (b[i] <= b[j])
    res = 1;
  else if (b[i] > b[j])
    res = -1;
  return (res);
}
/*
 * NAME:         swap_qs
 * parameters:      void *a
 *                  int i   - input parameter for index of lower element in array
 *                  int j   - input parameter for index of higher element in array
 * preconditions:   i and j must be valid array indices for array a
 * postconditions:  the values in a[i] and a[j] are exchanged
 */
void swap_qs(void *a, int i, int j) {
  int *b = (int *) a;
  int temp = b[i];
  b[i] = b[j];
  b[j] = temp;
} 
/* NAME: linear_search
 PARAMETERS: void *key, void *arr, int size_arr, int(*cmp)(void *,void *, int) 
 PURPOSE: The linear search is implemeted using the functions below
 PRECONDITION: The variables passed should be a void ptrs and values according to the function parameters 
 POSTCONDITION:It should search and return the index position of the search correctly 
*/
int linear_search(void *key, void *arr, int size_arr, int(*cmp)(void *,void *, int)){
  for(int j = 0; j< size_arr; j++){
    if(cmp(key, arr, j)==0){
      return j;
    }
  }
  return -1;
}
/* NAME: intcmp_ls
 PARAMETERS: void *k, void *a, int index
 PURPOSE: This function is used for comparison in linear search 
 PRECONDITION: the actual parameters passed should be two void ptrs and an index value
 POSTCONDITION: the elements should be compared correctly in the linear search 
*/
int intcmp_ls(void *k, void *a, int index){
  int *arr = (int *)a;
  int *key = (int *)k;
  return arr[index] - *key;
}

/* NAME: binary_search
 PARAMETERS: void *arr, void *key, int l , int r, int(*cmp)(void *,void *, int) 
 PURPOSE: The binary search is implemeted using the functions below
 PRECONDITION: The variables passed should be a void ptrs and values according to the function parameters 
 POSTCONDITION:It should search and return the index position of the search correctly 
*/
int binary_search(void *arr, void *key, int l , int r, int(*cmp)(void *,void *, int)){
  while(l <= r){
    int m = l + (r-l)/2;

    if((cmp(key, arr, m)==0)){
      return m;
    }

    if((cmp(key, arr, m)) < 0){
      l = m + 1;
    }
    if((cmp(key, arr, m)) > 0){
      r = m - 1;
    }
  }
  return -1;
}
/* NAME: intcmp_bs
 PARAMETERS: void *k, void *a, int index
 PURPOSE: This function is used for comparison in binary search 
 PRECONDITION: the actual parameters passed should be two void ptrs and an index value
 POSTCONDITION: the elements should be compared correctly in the binary search 
*/
int intcmp_bs(void *k, void *a, int index){
  int *arr = (int *)a;
  int *key = (int *)k;
  return arr[index] - *key; 
} 
/*  
Test cases : 
1) Output when size= 1000: 
Array of Random Numbers of size 1000...

Selection Sort....

    main - sort took 0.000347 seconds

Quick Sort....

    main - sort took 0.000218 seconds

Selection Sort....

    main - sort took 0.000362 seconds

Quick Sort....

    main - sort took 0.004586 seconds

Linear Search Sorted Array: b[0] = 527

    main - search took 0.000000 seconds
Index 0, sorted array temp[0] = 527

Linear Search Sorted Array: b[500] = 534728

    main - search took 0.000001 seconds
Index 500, sorted array temp[500] = 534728

Linear Search Sorted Array: b[999] = 999081

    main - search took 0.000001 seconds
Index 999, sorted array temp[999] = 999081

Binary Search Sorted Array: b[0] = 527

    main - search took 0.00000100 seconds
Index 0, sorted array temp1[0] = 527

Binary Search Sorted Array: b[500] = 534728

    main - search took 0.00000000 seconds
Index 500, sorted array temp1[500] = 534728

Binary Search Sorted Array: b[999] = 999081

    main - search took 0.00000200 seconds
Index 999, sorted array temp1[999] = 999081

Linear Search Sorted Array: b[999] + 1 = 999081

    main - search took 0.00000100 seconds
Index -1

Binary Search Sorted Array: b[999] + 1 = 999081

    main - search took 0.00000100 seconds
Index -1
2) Output when size= 10000: 
Array of Random Numbers of size 10000...

Selection Sort....

    main - sort took 0.024632 seconds

Quick Sort....

    main - sort took 0.002782 seconds

Selection Sort....

    main - sort took 0.032502 seconds

Quick Sort....

    main - sort took 0.479403 seconds

Linear Search Sorted Array: b[0] = 6

    main - search took 0.000000 seconds
Index 0, sorted array temp[0] = 6

Linear Search Sorted Array: b[5000] = 503664

    main - search took 0.000004 seconds
Index 5000, sorted array temp[5000] = 503664

Linear Search Sorted Array: b[9999] = 999934

    main - search took 0.000013 seconds
Index 9999, sorted array temp[9999] = 999934

Binary Search Sorted Array: b[0] = 6

    main - search took 0.00000200 seconds
Index 0, sorted array temp1[0] = 6

Binary Search Sorted Array: b[5000] = 503664

    main - search took 0.00000100 seconds
Index 5000, sorted array temp1[5000] = 503664

Binary Search Sorted Array: b[9999] = 999934

    main - search took 0.00000200 seconds
Index 9999, sorted array temp1[9999] = 999934

Linear Search Sorted Array: b[9999] + 1 = 999934

    main - search took 0.00000700 seconds
Index -1

Binary Search Sorted Array: b[9999] + 1 = 999934

    main - search took 0.00000100 seconds
Index -1
3) Output when size= 1000000: 

Array of Random Numbers of size 10000...

Selection Sort....

    main - sort took 0.024632 seconds

Quick Sort....

    main - sort took 0.002782 seconds

Selection Sort....

    main - sort took 0.032502 seconds

Quick Sort....

    main - sort took 0.479403 seconds

Linear Search Sorted Array: b[0] = 6
 make -s
 ./main

Array of Random Numbers of size 100000...

Selection Sort....

    main - sort took 2.466118 seconds

Quick Sort....

    main - sort took 0.040773 seconds

Selection Sort....

    main - sort took 3.872689 seconds

Quick Sort....

    main - sort took 46.447462 seconds

Linear Search Sorted Array: b[0] = 1

    main - search took 0.000000 seconds
Index 0, sorted array temp[0] = 1

Linear Search Sorted Array: b[50000] = 503386

    main - search took 0.000052 seconds
Index 50000, sorted array temp[50000] = 503386

Linear Search Sorted Array: b[99999] = 999985

    main - search took 0.000147 seconds
Index 99999, sorted array temp[99999] = 999985

Binary Search Sorted Array: b[0] = 1

    main - search took 0.00000300 seconds
Index 0, sorted array temp1[0] = 1

Binary Search Sorted Array: b[50000] = 503386

    main - search took 0.00000000 seconds
Index 50000, sorted array temp1[50000] = 503386

Binary Search Sorted Array: b[99999] = 999985

    main - search took 0.00000200 seconds
Index 99999, sorted array temp1[99999] = 999985

Linear Search Sorted Array: b[99999] + 1 = 999985

    main - search took 0.00005600 seconds
Index -1

Binary Search Sorted Array: b[99999] + 1 = 999985

    main - search took 0.00000100 seconds
Index -1


1. sorting arrays with random values – passed
2. sorting arrays in increasing or decreasing order – passed
3. searching for values at the front, middle, and end of the sorted arrays – passed
4. searching for values that are not in the arrays – passed 

*******Searching and Sorting Analysis
1. Is there an array where the selection sort would take more steps or less steps? 
Ans. Yes the selection sort would take more steps if the array size is more in this case and less steps whrn the array size is less
2. Is there an array where the quick sort would take more steps or less steps?
Ans. Yes the quick sort would take more steps if the array size is more in this case and less steps whrn the array size is less
3. What improvement could the linear search have from the algorithm in the chapter 14 slides for a sorted array? 
Ans. it will require kless time if the array is sorted and will require more time if it us insorted
4. What is the big O of the overall storage requirements for each sort and search for n items? 
Ans. Big O for selection sort: O(n)
Big O for quick sort: O(n)
Big O for linear search: O(n)
Big O for binary search: O(n)
Team members: 
              
1) Suchith Pinreddy: 
 a) void selection_sort (void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int)); = Checked 
b) int index_of_min (void *a, int low, int high, int (*compare) (void *,int,int)); = Checked
c) void swap (void *a, int i, int j); = Checked
d) int compare (void *a, int i, int j); =  Implemeted
e) void quick_sort(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)); = Implemeted
f) int partition(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)); =  Checked
g) int compare_qs(void *a, int i, int j); = Implemeted 
h) void swap_qs(void *a, int i, int j);= Implemeted
i) int linear_search(void *key, void *arr, int size_arr, int(*cmp)(void *,void *, int));= Checked and edited
j) int intcmp_ls(void *k, void *a, int index); =  Checked
int binary_search(void *arr, void *key, int l , int r, int(*cmp)(void *,void *, int)); = Checked
k) int intcmp_bs(void *k, void *a, int index);  = Checked
2) Yash Nikumb: 
 a) void selection_sort (void *a, int size, void (*swap) (void *,int,int), int (*compare) (void *,int,int)); = edited 
b) int index_of_min (void *a, int low, int high, int (*compare) (void *,int,int)); = Checked
c) void swap (void *a, int i, int j); = Checked
d) int compare (void *a, int i, int j); = Checked
e) void quick_sort(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)); = Chekced
f) int partition(void *arr, int start, int end, void (*swap) (void *,int,int), int (*compare) (void *,int,int)); + Checked
g) int compare_qs(void *a, int i, int j); = Checked 
h) void swap_qs(void *a, int i, int j);= Checked
i) int linear_search(void *key, void *arr, int size_arr, int(*cmp)(void *,void *, int));= Checked and edited
j) int intcmp_ls(void *k, void *a, int index); = Implemeted
int binary_search(void *arr, void *key, int l , int r, int(*cmp)(void *,void *, int)); = Implemeted
k) int intcmp_bs(void *k, void *a, int index);  = implemeted
*/