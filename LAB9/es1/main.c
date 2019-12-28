/*LABORATORIO 9 ESERCIZIO 1
alg: considero l'istante j-esimo e tra le scelte possibili (attività finite in quel momento) scelgo quella che massimizza la somma delle durate di tutte le precedenti*/

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "activities.txt"

//DATA STRUCTURES
typedef struct {
     int s, f;
} att;

typedef struct vett{
     att *v;
     int N;
}*array;

//PROTOTYPES
void bubbleSort(array vett);
int isCompatible(att a1, att a2);
void readFile(char *file_name, array vett);

void solveDP(array vett);
void printArr(array vett);
void printSol(att *sol, int *index, int last);
void stampaSol(att *v, int N);

int attCompare(att a1, att a2);
void showAtt(att a);
att scanAtt(FILE *fp);
int attD(att a1);

/*******START MAIN*******/
int main(int argc, char *argv[])
{
     array vett = malloc(sizeof(array));
     readFile(FILE_NAME, vett);
     bubbleSort(vett);
//     printArr(vett);
     solveDP(vett);
     return 0;
}
/*******END MAIN*******/

void readFile(char *file_name, array vett) {
     int i;
     FILE *fp = fopen(file_name, "r");
     fscanf(fp, "%d", &vett->N);
     vett->v = malloc(vett->N * sizeof(att));
     for (i = 0; i < vett->N; i++) {
	  (vett->v)[i]=scanAtt(fp);
     }
     fclose(fp);
}

att scanAtt(FILE *fp){
     att a;
     fscanf(fp, "%d %d", &a.s, &a.f);
     return a;
}

void showAtt(att a){
     printf("%d %d\n",a.s, a.f);
}

void printArr(array vett){
     int i;
     for (i = 0; i < vett->N; ++i) {
	  showAtt((vett->v)[i]);
     }
}


void solveDP(array vett){
     att *val=vett->v;
     att *sol= malloc(sizeof(att) * vett->N);
     int *index = calloc(sizeof(att), vett->N);
     int *lenght = calloc(sizeof(int), vett->N);
     int i, last, max_sum, j;
     sol[0]=val[0];
     for (i = 1; i < vett->N; i++) { //definisce la dimensione del prefisso
	  lenght[i]=attD(val[i]);
	  index[i]=-1;
	  for (j=0; j<i; j++)
	       if(!isCompatible(val[i], val[j])){
		    if ( max_sum <= max_sum - attD(val[j]) + attD(val[i])){
		    max_sum = max_sum  - attD(val[j]) + attD(val[i]);
		    sol[j] = val[i];
		    }
	       } else if(attCompare(val[i-1], val[i])!=0)
		    sol[i-1]=val[i]; /* TODO: boh */
	  /* if (max_sum < lenght[i]) { */
	  /*      max_sum = lenght[i]; */
	  /*      last = i; */
	  /* } */
     }
     stampaSol(sol, vett->N);
//     printSol(val, index, last);

}

int isCompatible(att a1, att a2){  // !(tmp.s >= v[i].f) && !(tmp.f <= v[i].s)
     if ( a2.s >= a1.f || a2.f <= a1.s)
	  return 1;
     return 0;
}

int attD(att a){
     return a.f - a.s;
}

void bubbleSort(array vett){
     int i, j, l=0, r=vett->N-1;
     att tmp;
     for (i = l; i < r; i++) {
	  for (j=l; j < r - i + l; j++) {
	       if (attCompare((vett->v)[j], (vett->v)[j+1])>0){
		    tmp = (vett->v)[j];
		    (vett->v)[j]= (vett->v)[j+1];
		    (vett->v)[j+1] = tmp;
	       }
	  }
     }
     return;
}

int attCompare(att a1, att a2){
     return a1.f - a2.f;
}

void printSol(att *sol, int *index, int last){

     if (index[last] == -1){
	  showAtt(sol[last]);
	  return;
     }
     printSol(sol, index, index[last]);
     showAtt(sol[last]);
}

void stampaSol(att *v, int N){
     int i;
     for (i = 0; i < N; ++i) {
	  showAtt(v[i]);
     }

}
