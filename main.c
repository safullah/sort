#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_arr(int arr[], int size);
void swap(int *current, int *next);
void bubble_sort(int arr[], int size);
void fill_arr(int arr[], int size, int rand_limit);
int qsort_cmp_int(const void *p, const void *q);
int qsort_cmp_struct(const void *p, const void *q);
void merge(int arr[], int left, int middle, int right);
void merge_sort(int arr[], int left_index, int right_index);
int b_comparator(const void *p, const void *q);

typedef struct
{
   int num;
   char str[10];
} element;

char *rand_str();
void populate(element *target, int size, int rand_limit);

int main()
{

   //valgrind --tool=memcheck --leak-ckeck=full --show-reachable=yes --track-origin=yes --track-fds=yes

   //generate 500 elements with random int and char
   int num_of_arrs = 3;
   clock_t start_t, end_t, total_t;
   int rand_limit = 32768;
   int small = 5;   //1000;
   int medium = 10; //5000;
   int large = 15;  //25000;
   element elements[500];
   memset(elements, 0, 500 * sizeof(element));
   srand((unsigned int)time(NULL));
   populate(elements, 500, rand_limit);

   int size_of_arrs[num_of_arrs];
   memset(size_of_arrs, 0, num_of_arrs * sizeof(int));
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
    * bubble_sort
    * 
    */

   printf("bubble_sort\n");
   printf("-----------");

   for (int i = 0; i < num_of_arrs; i++)
   {
      fill_arr(arrys[i], size_of_arrs[i], rand_limit);
      //print_arr(arrys[i], size_of_arrs[i]);
      start_t = clock();
      bubble_sort(arrys[i], size_of_arrs[i]);
      end_t = clock();
      total_t = end_t - start_t;
      //print_arr(arrys[i], size_of_arrs[i]);

      printf("\nbubble_sort: %d integers\n", size_of_arrs[i]);
      printf("start: %ld\n", start_t);
      printf("end: %ld\n", end_t);
      printf("total: %ld\n", total_t);
   }

   /**
    * quick_sort
    * 
    */
   printf("\nquick_sort\n");
   printf("----------");

   for (int i = 0; i < num_of_arrs; i++)
   {
      fill_arr(arrys[i], size_of_arrs[i], rand_limit);
      //print_arr(arrys[i], size_of_arrs[i]);
      start_t = clock();
      qsort((void *)arrys[i], size_of_arrs[i], sizeof(int), qsort_cmp_int);
      end_t = clock();
      total_t = end_t - start_t;
      //print_arr(arrys[i], size_of_arrs[i]);

      printf("\nquick_sort: %d integers\n", size_of_arrs[i]);
      printf("start: %ld\n", start_t);
      printf("end: %ld\n", end_t);
      printf("total: %ld\n", total_t);
   }

   /**
    * merge_sort
    * 
    */
   printf("\nmerge_sort\n");
   printf("----------");

   for (int i = 0; i < num_of_arrs; i++)
   {
      fill_arr(arrys[i], size_of_arrs[i], rand_limit);
      //print_arr(arrys[i], size_of_arrs[i]);
      start_t = clock();
      merge_sort(arrys[i], 0, size_of_arrs[i] - 1);
      end_t = clock();
      total_t = end_t - start_t;
      //print_arr(arrys[i], size_of_arrs[i]);

      printf("\nmerge_sort: %d integers\n", size_of_arrs[i]);
      printf("start: %ld\n", start_t);
      printf("end: %ld\n", end_t);
      printf("total: %ld\n", total_t);
   }
   qsort((void *)elements, 500, sizeof(element), qsort_cmp_int);
   qsort(elements, 0, 500)
   element *target;
   int key = 10;
   target = (element *)bsearch(&key, elements, 500, sizeof(element), b_comparator);
   if (target != NULL)
   {
      printf("\nelement found: num = %d, str = %s\n", target->num, target->str);
   }
   else
   {
      printf("\nelement not found.\n");
   }

   return EXIT_SUCCESS;
}

void print_arr(int arr[], int size)
{
   for (int i = 0; i < size; i++)
   {
      if (i % 15 == 0)
      {
         printf("\n");
      }
      printf(" %6d ", arr[i]);
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

   for (int i = 0; i < size; i++)
   {
      arr[i] = rand() % rand_limit;
   }
}
char *rand_str()
{
   int len = rand() % 10;
   char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
   static char str[10];
   memset(str, '\0', sizeof(char) * 10);
   for (int i = 0; i < len; i++)
   {
      str[i] = alphabet[rand() % 26];
   }
   return str;
}

void populate(element *target, int size, int rand_limit)
{
   for (int i = 0; i < size; i++)
   {
      (target + i)->num = rand() % rand_limit;
      for (int j = 0; j < 10; j++)
      {
         (target + i)->str[j] = (char)(rand() % 26 + 'a');
      }
   }
}

int qsort_cmp_int(const void *p, const void *q)
{
   int first = *(const int *)p;
   int second = *(const int *)q;

   if (first > second)
   {
      return 1;
   }
   else if (first < second)
   {
      return -1;
   }
   else
   {
      return 0;
   }
}

int qsort_cmp_struct(const void *p, const void *q)
{
   int a = ((const element *)p)->num;
   int b = ((const element *)q)->num;

   if (a > b)
   {
      return 1;
   }
   else if (a < b)
   {
      return -1;
   }
   else
   {
      return 0;
   }
}

int b_comparator(const void *p, const void *q)
{
   int target = *(const int *)p;
   return target - ((const element *)q)->num;
}

void merge(int arr[], int left, int middle, int right)
{

   //step one create arr in left_arr and right_arr
   int left_size = middle - left + 1;
   int right_size = right - middle;
   int left_arr[left_size];
   int right_arr[right_size];
   for (int i = 0; i < left_size; i++)
   {
      left_arr[i] = arr[left + i];
   }

   for (int i = 0; i < right_size; i++)
   {
      right_arr[i] = arr[middle + 1 + i];
   }

   //put left_arr and right_arr back together
   int left_index = 0;
   int right_index = 0;
   int merged_index = left;
   while (left_index < left_size && right_index < right_size)
   {
      if (left_arr[left_index] <= right_arr[right_index])
      {
         arr[merged_index] = left_arr[left_index];
         left_index++;
      }
      else
      {
         arr[merged_index] = right_arr[right_index];
         right_index++;
      }
      merged_index++;
   }

   //rest of left_arr if any
   while (left_index < left_size)
   {
      arr[merged_index] = left_arr[left_index];
      left_index++;
      merged_index++;
   }

   // rest of right_arr if any
   while (right_index < right_size)
   {
      arr[merged_index] = right_arr[right_index];
      right_index++;
      merged_index++;
   }
}

void merge_sort(int arr[], int left_index, int right_index)
{

   if (left_index < right_index)
   {
      int middle = left_index + (right_index - left_index) / 2;
      merge_sort(arr, left_index, middle);
      merge_sort(arr, middle + 1, right_index);
      merge(arr, left_index, middle, right_index);
   }
}