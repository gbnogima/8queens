#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define N 8
#define NUM_SOLUTIONS 8
#define NUM_PARENTS 3  
#define NUM_OFFSPRING 8


int min_attacks = 9999; 

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
   int i, j;
   for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
         matrix[i][j] = 0;
      }
   }
   for (i = 0; i < N; i++) {
      matrix[i][arr[i]] = 1;
   }
}


int count_num_attacks(int board[N][N], int index, int *best_idx){
   int i, j; 
   int num_attacks = 0;
   int count, count1, count2, count3, count4;

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

   //percorrendo as diagonais
   count = 0;
   for (i = 0; i < N; i++){
      count1 += board[i][i];
      count2 += board[N-1-i][i];
   }
   if(count1 > 0)
      num_attacks += (count1-1);
   


   for(i = 1; i < N; i++){
      count1 = 0;
      count2 = 0;
      count3 = 0;
      count4 = 0;
      for(j = 0; j < N - i; j++){
         count1 += board[j+i][j];
         count2 += board[j][j+i];
         count3 += board[N-j-i][j];
         count4 += board[N-1-j][j+i];
      }
      if(count1 > 0)
         num_attacks += (count1-1);
      if(count2 > 0)
         num_attacks += (count2-1);
      if(count3 > 0)
         num_attacks += (count3-1);
      if(count4 > 0)
         num_attacks += (count4-1);
   }

   if(num_attacks < min_attacks){
      min_attacks = num_attacks;
      *best_idx = index;
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
   int board[NUM_SOLUTIONS][N][N]; // 
   srand (time(0));   
     
   int pop_1d[NUM_SOLUTIONS][N];
   double fitness[NUM_SOLUTIONS];
   int parents_idx[NUM_PARENTS];

   int mating_pool[NUM_PARENTS][N];
   int idx1, idx2;
   int best_idx;


   for (i = 0; i < NUM_SOLUTIONS; i++)
      bldarray(pop_1d[i]);

   printf("Population: \n");
   for (int i = 0; i < NUM_SOLUTIONS; i++)
       print_array(pop_1d[i], N);
    printf("\n");

   for (i = 0; i < NUM_SOLUTIONS; i++)
      initialize_population(board[i], pop_1d[i]);

   // printf("Board: \n");
   // for (int i = 0; i < NUM_SOLUTIONS; i++)
   //    print_matrix(board[i]); 


   while(min_attacks != 0){
      for (i = 0; i < NUM_SOLUTIONS; i++)
         initialize_population(board[i], pop_1d[i]);

      //printf("Fitness: \n");
      for (i = 0; i < NUM_SOLUTIONS; i++){
         fitness[i] = (double)1 / (double)(count_num_attacks(board[i], i, &best_idx));
         //printf("%f\n", fitness[i]);
      }

      if(min_attacks == 0)
         break;
      
      select_mating_pool(parents_idx, fitness, mating_pool, pop_1d);

      // printf("Mating pool:\n");
      // for (i = 0; i < NUM_PARENTS; i++)
      //    print_array(mating_pool[i], N);
      // printf("\n");
       
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

      // printf("Min attacks: %d\n", min_attacks);

      // getchar();
   }

   // printf("Population: \n");
   //    for (i = 0; i < NUM_SOLUTIONS; i++)
   //       print_array(pop_1d[i], N);
   //    printf("\n");

   // printf("Board: \n");
   // for (i = 0; i < NUM_SOLUTIONS; i++)
   //    print_matrix(board[i]); 

   printf("Best: \n");
   print_matrix(board[best_idx]);





   return 0;

}