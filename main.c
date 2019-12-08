#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define N 8
#define NUM_SOLUTIONS 8
#define NUM_PARENTS 2
#define NUM_OFFSPRING 8


int min_attacks = 99999999; 

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

void print_array(int arr[], int n)
{
   int j;
   for (j = 0; j < n; j++) 
      printf("%d ", arr[j]); 
   printf("\n");
}

void bldarray (int randN[])
{
   int i;
   for(i = 0; i < N; i++){
      randN[i] = rand() % N;
   }
   return;
}

//Coloca as damas no tabuleiro, com base no vetor aleatório gerado anteriormente
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

   // for(i = 0; i < N ; ++i){
   //    count = 0;

   //    for(j = 0; j < N - i; ++j){
   //       count += board[j][i];
   //    }
   //    if(count > 0)
   //       num_attacks += (count-1);

   //    if(i!=0){
   //       for(j = 0; j < N - i; ++j){
   //          count += board[j][i];
   //       }
   //       if(count > 0)
   //          num_attacks += (count-1);
   //    }
   // }
   if(num_attacks < min_attacks){
      min_attacks = num_attacks;
   }
   return num_attacks;
}

//Seleciona NUM_PARENTS com melhor fitness e armazena os índices em um vetor parents_idx
void select_mating_pool(int parents_idx[NUM_PARENTS], double fitness[NUM_SOLUTIONS], int mating_pool[NUM_PARENTS][N], int pop[NUM_SOLUTIONS][N]){
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
      //printf("%d ", max_idx);  
      for (int k = 0; k < N; k++){
         mating_pool[i][k] = pop[max_idx][k];
      }
      
   }
}

void crossover(int parent1[], int parent2[], int child[]){
   int mid = rand() % N;
   int i;
   for (int i = 0; i < N; i++){
      if(i > mid){
         child[i] = parent1[i];
      }
      else{
         child[i] = parent2[i];
      }
   }
}

void mutation(int genes[N]){
   if((rand()%100) < 10){
      bldarray(genes);
   }
}
  
int main() 
{ 
   int i;
   int board[NUM_SOLUTIONS][N][N] = {0}; // 
   srand (time(0));   
     
   int pop_1d[NUM_SOLUTIONS][N];
   double fitness[NUM_SOLUTIONS];
   int parents_idx[NUM_PARENTS];


   for (i = 0; i < NUM_SOLUTIONS; i++)
      bldarray(pop_1d[i]);

   printf("Population: \n");
   for (int i = 0; i < NUM_SOLUTIONS; i++)
       print_array(pop_1d[i], N);
    printf("\n");

   // for (i = 0; i < NUM_SOLUTIONS; i++)
   //    initialize_population(board[i], pop_1d[i]);

   // for (int i = 0; i < NUM_SOLUTIONS; i++)
   //    print_matrix(board[i]); 


   while(min_attacks != 0){
      for (i = 0; i < NUM_SOLUTIONS; i++)
         initialize_population(board[i], pop_1d[i]);

      for (i = 0; i < NUM_SOLUTIONS; i++){
         fitness[i] = (double)1 / (double)(count_num_attacks(board[i]));
         //printf("%f\n", fitness[i]);
      }
      
      int mating_pool[NUM_PARENTS][N];

      //printf("Idxs: \n");
      select_mating_pool(parents_idx, fitness, mating_pool, pop_1d);
      //printf("\n\n");

      // printf("Mating pool:\n");
      // for (i = 0; i < NUM_PARENTS; i++)
      //    print_array(mating_pool[i], N);
      // printf("\n");

      
      int idx1, idx2;
      for (i = 0; i < NUM_OFFSPRING; i++){
         idx1 = rand()%NUM_PARENTS;
         idx2 = rand()%NUM_PARENTS;
         while(idx1 == idx2){
            idx2 = rand()%NUM_PARENTS;
         }
         crossover(mating_pool[idx1], mating_pool[idx2], pop_1d[i]);
         mutation(pop_1d[i]);

      }

      // printf("Population: \n");
      // for (int i = 0; i < NUM_SOLUTIONS; i++)
      //    print_array(pop_1d[i], N);
      // printf("\n");

      //printf("%d\n", min_attacks);

      //getchar();
   }
   printf("%d\n", min_attacks);




   return 0;

}