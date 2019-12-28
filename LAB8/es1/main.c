/*LABORATORIO 8 ESERCIZIO 1*/

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "activities.txt"

//DATA STRUCTURES
typedef struct {
     int s, f, d;
} att;

typedef struct {
     att *v;
     int N;
}array;

//PROTOTYPES
int isCompatible(att a1, att a2);
int isValid(att *v, int N);

att scanAtt(FILE *fp);
void printAtt(att a);
void readFile(char *file_name, att **v, int *N);
void printSol(att *v, int N);
int checkMax(att *v, int N);
void attSel(int N, att *v);
void powerset(int pos, att *val, att *sol, int n, int k, int start, array* best_sol);
void arraycpy(att *v1, att *v2, int N); //copy v2 in v1

//GLOBAL VARIABLES
int MAX=0;
/*******START MAIN*******/
int main(int argc, char *argv[])
{
     att *v;
     int N;
     readFile(FILE_NAME, &v, &N);
     attSel(N, v);
     return 0;
}
/*******END MAIN*******/

void attSel(int N, att *v){
     int i;
     att *sol= malloc(N * sizeof(att));
     array *best_sol = malloc(sizeof(array));
     best_sol->v = malloc(N * sizeof(att));
     for (i = N; i > 0; i--) {
	  powerset(0, v, sol, N, i, 0, best_sol);
     }
     printSol(best_sol->v, best_sol->N);
     printf("La durata massima è:%d\n", MAX);
}

int isValid(att *v, int N){//check
     int i;
     att tmp = v[N-1];
//     printSol(v, N+1);
     for (i = N-2; i >= 0; i--) {
	  if (!(isCompatible(tmp, v[i])))
	       return 0;
     }
     return 1;
}

void powerset(int pos, att *val, att *sol, int n, int k, int start, array *best_sol){
     int i, m=0;
     if (pos >= k) {
//	  if (isValid(sol, pos+1)) {
//	  printSol(sol, k);
	       if ((m=checkMax(sol, k))){
		    MAX=m;
		    arraycpy(best_sol->v, sol, k);
		    best_sol->N=k;
	       }
	       return;
//	  }
    }

     for (i = start; i < n; i++) {
	  sol[pos] = val[i];
	  if (!(isValid(sol, pos+1)))
	       continue; //pruning
	  powerset(pos+1, val, sol, n, k, i+1, best_sol);
     }
}

int checkMax(att *v, int N){
     int i, m=0;
     for (i = 0; i < N; i++) {
	  m+= v[i].d;
     }
     if(m<MAX)
	  return 0;
     MAX=m;
     return m;
}

void printSol(att *v, int N){
     int i;
     printf("Le attività che compongono la soluzione sono:\n");
     for (i = 0; i < N; i++) {
	  printAtt(v[i]);
     }
     printf("\n");
}

void printAtt(att a){
     printf("(%d,%d) ", a.s, a.f);
}

void readFile(char *file_name, att **v, int *N) {
     int i;
     FILE *fp = fopen(file_name, "r");
     fscanf(fp, "%d", N);
     *v = malloc(*N * sizeof(att));
     for (i = 0; i < *N; i++) {
	  (*v)[i]=scanAtt(fp);
     }
     fclose(fp);
}

att scanAtt(FILE *fp){
     att a;
     fscanf(fp, "%d %d", &a.s, &a.f);
     a.d = a.f - a.s;
     return a;
}
int isCompatible(att a1, att a2){  // !(tmp.s >= v[i].f) && !(tmp.f <= v[i].s)
     if ( a2.s >= a1.f || a2.f <= a1.s)
	  return 1;
     return 0;
}

void arraycpy(att *v1, att *v2, int N){
     int i;
     for (i = 0; i < N; i++) {
	  v1[i]=v2[i];
     }
}
