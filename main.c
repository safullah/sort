#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_arr(int arr[], int size);
void swap(int *current, int *next);
void bubble_sort(int arr[], int size);
void fill_arr(int arr[], int size, int rand_limit);

int main()
{

   //valgrind --tool=memcheck --leak-ckeck=full --show-reachable=yes --track-origin=yes --track-fds=yes
   int num_of_arrs = 3;
   clock_t start_t, end_t, total_t;
   int rand_limit = 32768;
   int small = 1000;
   int medium = 5000;
   int large = 25000;

   int size_of_arrs[num_of_arrs];
   memset(size_of_arrs, 0, num_of_arrs*sizeof(int));
   size_of_arrs[0] = small;
   size_of_arrs[1] = medium;
   size_of_arrs[2] = large;
   
   int small_arr[small];
   memset(small_arr, 0, small * sizeof(int));
   int medium_arr[medium];
   memset(medium_arr, 0, medium * sizeof(int));
   int large_arr[large];
   memset(large_arr, 0, large * sizeof(int));
   int *arrys[] = {small_arr, medium_arr, large_arr}; 
   
   /**
    * Bubblesort
    * 
    */

   printf("bubble_sort\n");
   printf("-----------");
  
   for (int i = 0; i < num_of_arrs; i++)
   {  
      fill_arr(arrys[i], size_of_arrs[i], rand_limit);
      //print_arr(all_arrs[i], size_of_arrs[i]);
      start_t = clock();
      bubble_sort(arrys[i], size_of_arrs[i]);
      end_t = clock();
      total_t = end_t - start_t;
      //print_arr(all_arrs[i], size_of_arrs[i]);

      printf("\nbubble_sort: %d integers\n", size_of_arrs[i]);
      printf("start: %ld\n", start_t);
      printf("end: %ld\n", end_t);
      printf("total: %ld\n", total_t);
   }

   /**
    * Quicksort
    * 
    */
   //TODO display the sort and unsorted array
   //TODO display the runtime of each func with different size of array

   /**
    * Mergesort
    * 
    */
   //TODO display the sort and unsorted array
   //TODO display the runtime of each func with different size of array

   return (0);
}

void print_arr(int arr[], int size)
{
   for (int i = 0; i < size; i++)
   {
      if (i % 15 == 0)
      {
         printf("\n");
      }

      printf(" %d ", arr[i]);
   }
   printf("\n");
}

void swap(int *current, int *next)
{
   int temp = *current;
   *current = *next;
   *next = temp;
}

void bubble_sort(int arr[], int size)
{
   int i, j;
   for (i = 0; i < size - 1; i++)
   {
      for (j = 0; j < size - i - 1; j++)
      {
         if (arr[j] > arr[j + 1])
         {
            swap(&arr[j], &arr[j + 1]);
         }
      }
   }
}

void fill_arr(int arr[], int size, int rand_limit)
{
   srand((unsigned int)time(NULL));
   for (int i = 0; i < size; i++)
   {
      arr[i] = rand() % rand_limit;
   }
}
