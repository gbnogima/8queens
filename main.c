#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define N 8
#define NUM_SOLUTIONS 8
#define NUM_PARENTS 2

 
void print_matrix(int arr[N][N]) 
{ 
   int i, j; 
   for (i = 0; i < N; i++){
      for (j = 0; j < N; j++) 
         printf("%d ", arr[i][j]); 
      printf("\n");
   }
   printf("\n");
} 

void print_array(int arr[N])
{
   int j;
   for (j = 0; j < N; j++) 
      printf("%d ", arr[j]); 
   printf("\n");
   printf("\n");
}

void bldarray (int randN[])
{
   int i;
   for(i = 0; i < N; i++){
      randN[i] = rand() % 8;
   }
   return;
}

void initialize_population(int matrix[N][N], int arr[]){
   int i;
   for (int i = 0; i < N; i++) {
      matrix[i][arr[i]] = 1;
   }
}

int count_num_attacks(int board[N][N]){
   int i, j; 
   int num_attacks = 0;
   int count;

   //percorrendo as colunas
   for (i = 0; i < N; i++){
      count = 0;
      for (j = 0; j < N; j++){
         count += board[j][i];
      }
      if(count > 0){
         num_attacks += (count-1);
      }
   }

   for(i = 0; i < N ; ++i){
      count = 0;

      for(j = 0; j < N - i; ++j){
         count += board[j][i];
      }
      if(count > 0)
         num_attacks += (count-1);

      if(i!=0){
         for(j = 0; j < N - i; ++j){
            count += board[j][i];
         }
         if(count > 0)
            num_attacks += (count-1);
      }
   }

   printf("\n");
   return num_attacks;
}

void select_mating_pool(int parents_idx[NUM_PARENTS], double fitness[NUM_SOLUTIONS]){
   int i, j;
   double max;
   int max_idx;
   for (i = 0; i < NUM_PARENTS; i++) {
      max = 0;
      for(j = 0; j < NUM_SOLUTIONS; j++){
         if(fitness[j] > max){
            max = fitness[j];
            max_idx = j;
         }
      }
      fitness[max_idx] = -1;
      parents_idx[i] = max_idx;   
   }

}
  
int main() 
{ 
   int i;
   int board[NUM_SOLUTIONS][N][N] = {0}; // 
   srand (time(0));   
   for (int i = 0; i < NUM_SOLUTIONS; i++)
      print_matrix(board[i]);
   
   int pop_1d[NUM_SOLUTIONS][N];
   double fitness[NUM_SOLUTIONS];

   for (int i = 0; i < NUM_SOLUTIONS; i++)
      bldarray(pop_1d[i]);

   for (int i = 0; i < NUM_SOLUTIONS; i++)
      print_array(pop_1d[i]);

   for (int i = 0; i < NUM_SOLUTIONS; i++)
      initialize_population(board[i], pop_1d[i]);

   for (int i = 0; i < NUM_SOLUTIONS; i++)
      print_matrix(board[i]); 

   for (int i = 0; i < NUM_SOLUTIONS; i++){
      fitness[i] = (double)1 / (double)(count_num_attacks(board[i]));
      printf("%f\n", fitness[i]);
   }

   int parents_idx[NUM_PARENTS];
   select_mating_pool(parents_idx, fitness);
   printf("%d\n", parents_idx[0]);
   printf("%d\n", parents_idx[1]);
   return 0;

}