/*ESERCIZIO 1 LABORATORIO 7*/
#include <stdio.h>
#include <stdlib.h>

#define NSTONES 4
#define FILE_NAME "very_very_easy_test_set.txt"

//DATA STRUCTURES
typedef enum {z,s,r,t} gem;
typedef struct { int nstones[NSTONES], ntot;} stn;
typedef struct {stn *stones; int N;} db;

//PROTOTYPES
void setStones(stn *s, stn stones);
char getStone(gem g);
int isOutOfGems(stn stones, int g);
void scanStones(FILE *fp, stn *stones);
void findNecklace(gem *val, gem *sol, int k, stn stones, int *_stop_p);
void dispRip(int pos, gem *val,gem  *sol,  int n, int k, stn *stones, int *_stop);
int isValidSol(gem *v, int N);
void printSol(gem *sol, int N);

//GLOBAL VARIABLES

/*******START MAIN*******/
int main()
{
     stn stones;
//     gem prova[8]={z,z,r,s,s,t,r,t};
     int i, N, _stop=1, count =1;
     gem val[NSTONES] = {z,s,r,t}, sol[NSTONES];
//     printf("%d\n", isValidSol(prova, 8));
     FILE *fp = fopen(FILE_NAME, "r");
     db data;
     fscanf(fp, "%d", &data.N);
     data.stones = (stn *) malloc(data.N * sizeof(stn));
     for (i = 0; i < data.N; i++) {

     }
     do
     {
	  fscanf(fp, "%d", &N);
	  scanStones(fp, &stones);
	  _stop=1;
	  printf("Test %d\n",count++);
	  for (i=stones.ntot; i > 0 && _stop; i--) {
	       findNecklace(val, sol, i, stones, &_stop);
	  }
     } while ((--N) > 0);
     fclose(fp);
     return 0;
}
/*******END MAIN*******/

void dispRip(int pos, gem *val, gem *sol, int n, int k, stn *stones, int *_stop){
     int i, *stns=stones->nstones;
     if (pos >= k) {
	  *_stop=0;
	  printf("Soluzione: lunghezza:%d\nCollana:\n", k);
	  printSol(sol, k);
	  return;
     }
     for (i = 0; i < n && _stop; i++) {
	  sol[pos]=val[i];
//	  printSol(sol, pos+1);
	  stns[val[i]]--;

	       if (!(isValidSol(&(sol[pos-1]), 2)) || isOutOfGems(*stones, val[i])) {
		    stns[val[i]]++;
	       } else dispRip(pos+1, val, sol, n, k, stones, _stop);

     }
     return;
}



int isValidSol(gem *v, int N) {
     int i;
     gem g;

     for (i = 0; i < N-1; ++i) {
	  g=v[i];
	  switch (g) {
	  case z: {
	       if (v[i+1]!=z && v[i+1]!=r)
		    return 0;
	       break;
	  }
	  case s:{
	       if (v[i+1]!=s && v[i+1]!=t)
		    return 0;
	       break;
	  }
	  case r:{
	       if (v[i+1]!=s && v[i+1]!=t)
		    return 0;
	       break;
	  }
	  case t:{
	       if (v[i+1]!=z && v[i+1]!=r)
		    return 0;
	       break;
	  }
	  default:
	       break;
	  }
     }
     return 1;
}

int isOutOfGems(stn stones, int g){
     if(stones.nstones[g]==-1)
	  return 1;
     return 0;
}

void printSol(gem *sol, int N){
     printf("*");
     for (int i=0 ; i < N; i++) {
	  printf("-%c", getStone(sol[i]));
     }
     printf("-*\n");
}

char getStone(gem g){
     switch (g) {
     case z: return 'z';
     case s: return 's';
     case r: return 'r';
     case t: return 't';
default:
	  break;
     }
     return 'E'; //ERROR
}

void scanStones(FILE *fp, stn *stones) {
     int *v = stones->nstones;
     stones->ntot=0;
     for (int i = 0; i < NSTONES; i++) {
	  fscanf(fp, "%d", &v[i]);
	  stones->ntot+=v[i];
     }
}

void findNecklace(gem *val, gem *sol, int k, stn stones, int *_stop_ptr){
     stn *sto = malloc(sizeof(stn));
     setStones(sto, stones);
     dispRip(0, val, sol, NSTONES, k, sto, _stop_ptr);
     free(sto);
     return;
}

void setStones(stn *s, stn stones){
     int *vs=stones.nstones;
     for (int i = 0; i < NSTONES; i++) {
	  (s->nstones)[i]=vs[i];
     }
     s->ntot=stones.ntot;
}
