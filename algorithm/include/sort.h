#ifndef _SORT_H_
#define _SORT_H_

#undef DEBUG
#define QUICKSORT_THRESHOLD 10
#define BUCKETSORT_RATIO 0.1

int SelectionSort(int array[], unsigned int size);
int BubbleSort(int array[], unsigned int size);
int InsertionSort(int array[], unsigned int size);
int ShellSort(int array[], unsigned int size);
int HeapSort(int array[], unsigned int size);
int MergeSort(int array[], unsigned int size);
int QuickSort(int array[], unsigned int size);
int BucketSort(int array[], unsigned int size);
int RadixSort(int array[], unsigned int size);

#endif
