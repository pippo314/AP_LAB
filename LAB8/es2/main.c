/*LABORATORIO 8 ESERCIZIO 2*/

#include <stdio.h>
#include <stdlib.h>

#define DBG 0
#define TILES_FILE "tiles.txt"
#define BOARD_FILE "board.txt"

//DATA STRUCTURES
typedef struct {
     char cT1, cT2;
     int vT1, vT2;
} tile;

typedef struct {
     int tile_index;
     int is_turned;
} cell;

typedef struct matrix *board;
struct matrix{
     cell **m;
     int nc, nr;
};

//PROTOTYPES
void tilesReadFile(char *file_name, tile **tiles, int *N);
void boardReadFile(char *file_name, board b);
tile TILEscan(FILE *fp);
void TILEshow(FILE *fp, tile t);
tile TILErotate(tile t);
cell CELLscan(FILE *fp);
void CELLshow(FILE *fp, cell c);
board newBoard();
void matrixAlloc(board b);
int CELLcheckVoid(cell c);
int countVoid(board b);
int findBestSol(board b, tile *tiles, int N);
void dispSempl(int pos, int *sol, int *val, int *mark, int n, int k, board b, tile *tiles);
void tileToCell(int index, int is_turned);
int scoreEval(board b, tiles *t);

/*******START MAIN*******/
int main(int argc, char *argv[])
{
     tile *tiles; //val
     int N,i;
     board b = malloc(sizeof(struct matrix));
     tilesReadFile(TILES_FILE, &tiles, &N);
     /* for (i = 0; i < N; ++i) { */
     /* 	  TILEshow(stdout, tiles[i]); */
     /* } */
     boardReadFile(BOARD_FILE, b);

     return 0;
}
/*******END MAIN*******/

void tilesReadFile(char *file_name, tile **tiles, int *N){
     int i;
     FILE *fp = fopen(file_name, "r");
     fscanf(fp, "%d\n", N);
     *tiles = malloc(*N * sizeof(tile));
     for (i = 0; i < *N; ++i) {
	  (*tiles)[i] = TILEscan(fp);
     }
     fclose(fp);
}

tile TILEscan(FILE *fp){
     tile t;
     fscanf(fp, "%c %d %c %d\n", &t.cT1, &t.vT1, &t.cT2, &t.vT2);
     return t;
}

void TILEshow(FILE *fp, tile t){
     printf("%c %d %c %d\n", t.cT1, t.vT1, t.cT2, t.vT2);
}

void boardReadFile(char *file_name, board b){
     int i,j;
     FILE *fp = fopen(file_name, "r");
     fscanf(fp, "%d %d\n", &b->nr, &b->nc);
     matrixAlloc(b);
     for (i = 0; i < b->nr; i++) {
	  for (j = 0; j < b->nc; j++) {
	       b->m[i][j] = CELLscan(fp);
	       CELLshow(stdout, b->m[i][j]);
	  }
	  printf("\n");
     }
     fclose(fp);
}

void matrixAlloc(board b){
     int i;
     b->m = (cell **) malloc(b->nr * sizeof(cell *));
     for (i = 0; i < b->nr; i++) {
	  (b->m)[i] = (cell *) malloc(b->nc * sizeof(cell));
     }
}

cell CELLscan(FILE *fp){
     cell c;
     fscanf(fp, "%d/%d ", &c.tile_index, &c.is_turned);
     return c;
}

void CELLshow(FILE *fp, cell c){
     fprintf(fp, "%d/%d ", c.tile_index, c.is_turned);
}

int findBestSol(board b, tile *tiles, int N){
     board sol; *sol = *b;
     int k = countVoid(b);
}

int countVoid(board b){
     int count = 0;
     for (i = 0; i < b->nr; i++) {
	  for (j = 0; j < b->nc; j++) {
	       if(CELLcheckVoid(b->m[i][j]))
		    count++;
	  }
     }
     return count;
}

int CELLcheckVoid(cell c){
     return c.tile_index == -1;
}

void dispSempl(int pos, board sol, int *mark, int n, int k, tile *tiles, int *max){
     int i;
     int r = pos % (sol->nc);
     int c = pos / (sol->nc);
     int score;
     if (pos >= k){
	  score = scoreEval(sol, tiles);
	  if (score > *max){
	       max = score;
	  }
	  return;
     }

     for (i = 0; i < n; i++) {
	  if (mark[i]==0) {
	       mark[i]=1;
	       sol->m[r][c] = tileToCell(i, 0);
	       dispSempl(pos+1,sol, mark, n, k, tiles, max);
	       sol->m[r][c] = tileToCell(i, 1);
	       dispSempl(pos+1,sol, mark, n, k, tiles, max);
	       mark[i] = 0;
	  }
     }
     return;
}

tile TILErotate(tile t){
     char tmp_c;
     int tmp_n;
     tmp_c = t.cT1;
     t.cT1 = t.cT2;
     t.cT2 = tmp_c;

     tmp_n = t.vT1;
     t.vT1 = t.vT2;
     t.vT2 = tmp_n;
     return t;
}

void tileToCell(int index, int is_turned){
     cell c;
     c.tile_index = index;
     c.is_turned = is_turned;
     return c;
}

int scoreEval(board b, tiles *t){

}
