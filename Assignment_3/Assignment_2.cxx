#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void sort(int *A, int n);
 
int main()
{  int i, offset, j;
   int B[10000000];
   time_t t;
   srand( (unsigned) time( &t ));
   offset = rand()%10000000;
   for( i = 0; i< 10000000; i++ )
   {  B[i] = ((91*i)%10000000) + offset;
   }
   printf("Prepared array of 10 million integers; calling sort\n");
   sort( B, 10000000 );
   printf("finished sort, now check result\n");
   for( i=0, j=0; i < 10000000; i++ )
     if( B[i] != i+ offset ) j++;
   if( j == 0 )
     printf("Passed Test\n");
   else
     printf("Failed Test. %d numbers wrong.\n", j );
}
 
void sort(int* A, int n) {
    int buckets[65536]; // 65535 is the range of 0xFFFF //
    for (int i = 0;i < 65536;i++) { buckets[i] = 0; } // sets values to 0 //
    int sorted[n]; // Original array is sorted and stored - sorted must be the same size as original array //
 
    // Lower 16 bits //
 
    // Makes a count per element value of the array //
    for (int i = 0; i < n; i++) { buckets[(A[i] & 0xFFFF)]++; }
 
    // Modifies the bucket array so that the array can be converted later as the positions of each element //
    for (int i = 0, position = buckets[0]; i < 65536; i++, position += buckets[i]) { buckets[i] = position - buckets[i]; }
 
    // Placing the original array's elements into the result array in the proper position //
    for (int i = 0; i < n; i++) { sorted[buckets[(A[i] & 0xFFFF)]++] = A[i]; }
 
    // Sets the original array as the sorted array //
    for (int i = 0; i < n; i++) { A[i] = sorted[i]; }
 
    // Upper 16 bits //
 
    // Clears all value of the bucket to 0 so that it can be resued for each loop //
    for (int i = 0;i < 65536;i++) { buckets[i] = 0; }
 
    // Makes a count per element value of the array //
    for (int i = 0; i < n; i++) { buckets[(A[i] >> 16) & 0xFFFF]++; }
 
    // Modifies the bucket array so that the modified array indicates the position of each element in the result array //
    for (int i = 0, position = buckets[0]; i < 65535; i++, position += buckets[i]) { buckets[i] = position - buckets[i]; }
 
    // Placing the original array's elements into the result array in the proper position //
    for (int i = 0; i < n; i++) { sorted[buckets[(A[i] >> 16) & 0xFFFF]++] = A[i]; }
 
    // Sets the original array as the result array so the original array is sorted //
    for (int i = 0; i < n; i++) { A[i] = sorted[i]; }
}