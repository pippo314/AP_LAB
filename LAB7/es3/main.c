/*LABORATORIO 7 ESERCIZIO 3*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJ 8
#define MAX_STR 50
#define PG_FILE "pg.txt"
#define INV_FILE "inventory.txt"
#define N_CMD 9
#define CODE 7
#define N_STAT 6

int MAXN=1;
//DATA STRUCTURES
typedef enum {load_champ, load_obj, add_champ, del_champ, equip, unequip, get_stats, print, stop=-1} cmd;

typedef struct {int hp,mp,atk,def,mag,spr;} stat_t;

typedef struct {char name[MAX_STR], type[MAX_STR]; stat_t stats;} inv_t;

typedef struct {inv_t *vettInv; int nInv, maxInv; } tabInv_t; //nel .h sarà dichiarato un puntatore a questa struct

typedef struct {int inUso, vettEq[MAX_OBJ];/*sarà necessaria la realloc*/} tabEquip_t;

typedef struct {char code[CODE], name[MAX_STR], class[MAX_STR]; stat_t stat; tabEquip_t *equip;} pg_t; //nei prossimi lab equip non avrà asterischi
typedef char* Key;

typedef struct node node_t, *link;
struct node {
     pg_t pg;
     link next;
};

typedef struct {link headPg, tailPg; int nPg;} tabPg_t;
//PROTOTYPES

//FUNCTIONS FOR inv_t "QUASI ADT"
inv_t OBJscan(FILE *fp);
void OBJshow(inv_t obj);
int OBJcompare(inv_t o1, inv_t o2);

//FUNCTIONS FOR tabInv_t
tabInv_t *newTabInv();
void INVaddObj(tabInv_t *tab, inv_t obj);
void printTab(tabInv_t *tab);
void setTabDim(tabInv_t *tab, int max_dim);
int getIndexOf(tabInv_t *tab, inv_t obj);

//FUNCTIONS FOR stat_t
stat_t scanStats(FILE *fp);
void showStats(FILE *fp, stat_t s);
void upgradeStats(stat_t *pg_stat, stat_t obj_stat);

//FUNCTIONS FOR pg_t "QUASI ADT"
void PGequip(pg_t *pg, int obj);
tabEquip_t *PGgetEquip(pg_t *pg);
Key KEYget(pg_t *pg);
int KEYcompare(Key k1, Key k2);
pg_t PGscan(FILE *fp);
void PGshow(pg_t pg);

//FUNCTIONS FOR THE LIST
tabPg_t *newList();
link newNode(pg_t pg, link next);
void listInsHead(tabPg_t *tabPg, pg_t pg);
void listDelKey(tabPg_t *tabPg, Key key);
pg_t listSearch(tabPg_t *tabPg, Key key);
void listPrint(tabPg_t *l);

//FUNCTIONS FOR tabEquip_t
tabEquip_t *newEquip();
void addEquip(tabEquip_t *equip, int obj); //chiamata nel main
void delEquip(tabEquip_t *equip, int obj);

//UTILITY
void readFilePG(char *file_name, tabPg_t *list);
void readFileINV(char *file_name, tabInv_t *tabInv);
cmd getCmd(char *commands[]);

/*******START MAIN*******/
int main(int argc, char *argv[])
{
     char *cmds[N_CMD] ={"load_champ", "load_obj", "add_champ", "del_champ", "equip", "unequip", "get_stats", "print", "stop"};
     cmd command;
     tabPg_t *listPg = newList();
     tabInv_t *tabInv = newTabInv();
     while ((command = getCmd(cmds)) != -1) {
	  switch (command) {
	  case load_champ: {
	       readFilePG(PG_FILE, listPg);
	       break;
	  }
	  case load_obj: {
	       readFileINV(INV_FILE, tabInv);
	       break;
	  }
	  case add_champ: {
	       printf("Inserire dati personaggio:\n");
	       listInsHead(listPg, PGscan(stdin));
	       break;
	  }
	  case del_champ: {
	       printf("Inserire codice personaggio da eliminare:\n");
	       char tmp_code[CODE];
	       scanf("%s", code);
	       listDelKey(listPg, code);
	       break;
	  }
	  case equip: {
	       printf("Inserire codice personaggio:\n");
	       scanf("%s", tmp_code);
	       printf("Inserire nome oggetto:\n");


	       break;
	  }
	  case unequip: {
	       break;
	  }
	  case get_stats: {
	       break;
	  }
	  case print: {
	       break;
	  }


default:
	       break;
	  }
     }
/*      tabPg_t *tab= newList(); */
/*      readFilePG(PG_FILE, tab); */
/*      tabInv_t *inv = newTabInv(); */
/*      readFileINV(INV_FILE, inv); */
/*      printTab(inv); */
/*      stat_t s1,s2; */
/*      s1.atk = 10; s1.def = 10; s1.hp = 10; s1.mag = 10; s1.mp = 10; s1.spr = 10; */
/*      s2.atk = -1; s2.def = 10; s2.hp = -10; s2.mag = -5; s2.mp = 5; s2.spr =-5; */
/*      upgradeStats(&s1, s2); */
/* //     listPrint(tab); */
     return 0;
}
/*******END MAIN*******/

link newNode(pg_t pg, link next){
     link x = malloc(sizeof(node_t));
     if (x == NULL)
	  return NULL;
     x->pg = pg;
     x->next=next;
     return x;
}

void listInsHead(tabPg_t *tabPg, pg_t pg){
     tabPg->headPg=newNode(pg,tabPg->headPg);
}

void listDelKey(tabPg_t *tabPg, Key key){
     link x, prev, h=tabPg->headPg;
     for(x=h, prev=NULL; x!=NULL; prev=x, x=x->next) {
	  if (KEYcompare(key, KEYget(&x->pg))==0){
	       if(x==h)
		    h=x->next;
	       else
		    prev->next=x->next;
	       free(x);
	       break;
	  }
     }
}


Key KEYget(pg_t *pg) {
     return pg->code;
}

int KEYcompare(Key k1, Key k2){
     return strcmp(k1, k2);
}

pg_t PGscan(FILE *fp){
     pg_t pg;
     fscanf(fp, "%s %s %s", pg.code, pg.name, pg.class);
     pg.stat = scanStats(fp);
     pg.equip=NULL;
     return pg;
}


stat_t scanStats(FILE *fp){
     stat_t s;
     fscanf(fp, "%d %d %d %d %d %d", &s.hp, &s.mp, &s.atk, &s.def, &s.mag, &s.spr);
     return s;
}

void PGshow(pg_t pg){
     printf("%s %s %s ", pg.code, pg.name, pg.class);
     showStats(stdout, pg.stat);
     printf("\n");
}

void showStats(FILE *fp, stat_t s){
     fprintf(fp, "%d %d %d %d %d %d", s.atk, s.def, s.hp, s.mag, s.mp, s.spr);
}

void readFilePG(char *file_name, tabPg_t *tab){
     int not_end=1;
     pg_t pg_tmp;
     FILE *fp = fopen(file_name, "r");

     while (not_end) {
	  pg_tmp = PGscan(fp);
	  if(!feof(fp)){ //se non è la fine del file aggiungi alla lista
	       listInsHead(tab, pg_tmp);
	       tab->nPg++;
	  } else not_end = 0;
     }
     fclose(fp);
}

tabPg_t *newList(){
     tabPg_t *tab = malloc(sizeof(tabPg_t));
     tab->headPg=NULL;
     tab->nPg=0;
     tab->tailPg=NULL;
     return tab;
}

void listPrint(tabPg_t *l){
     link x;
     int i;
     for ( x=l->headPg, i=0; i < l->nPg; x=x->next, i++) {
	  PGshow((x->pg));
     }
}

inv_t OBJscan(FILE *fp){
     inv_t obj;
     fscanf(fp, "%s %s", obj.name, obj.type);
     obj.stats = scanStats(fp);
     return obj;
}

void OBJshow(inv_t obj){
     printf("%s %s ", obj.name, obj.type);
     showStats(stdout, obj.stats);
     printf("\n");
}

void readFileINV(char *file_name, tabInv_t *tabInv){
     int dim, i;
     FILE *fp = fopen(file_name, "r");
     fscanf(fp, "%d", &dim);
//     tabInv = newTabInv(dim);
     setTabDim(tabInv, dim);
     for (i = 0; i < dim; i++) {
	  INVaddObj(tabInv, OBJscan(fp));
     }
//     fclose(fp);
}

tabInv_t *newTabInv(){
     tabInv_t *tab=malloc(sizeof(tabInv_t));
//     tab->maxInv=maxInv;
     tab->vettInv=malloc(MAXN * sizeof(inv_t));
     tab->nInv=0;
     return tab;
}

void INVaddObj(tabInv_t *tab, inv_t obj){
     if (tab->nInv == MAXN) {
	  MAXN = 2 * MAXN;
	  tab->vettInv = realloc(tab->vettInv, MAXN * sizeof(inv_t));
     }
     (tab->vettInv)[tab->nInv++] = obj;
}

void printTab(tabInv_t *tab){
     int i;
     for (i = 0; i < tab->nInv; i++) {
	  OBJshow((tab->vettInv)[i]);
     }
}


void setTabDim(tabInv_t *tab, int max_dim){
     tab->maxInv = max_dim;
}

tabEquip_t *newEquip(){
     tabEquip_t *equip = malloc(sizeof(tabEquip_t));
     equip->inUso=0;
     for (int i = 0; i < MAX_OBJ; i++) {
	  equip->vettEq[i]=-1;
     }
     return  equip;
}

void addEquip(tabEquip_t *equip, int obj){
     if (equip->inUso > MAX_OBJ) {
	  return; /* TODO: controllo rozzo */
     }
     equip->vettEq[equip->inUso++] = obj;
}

int getIndexOf(tabInv_t *tab, inv_t obj){
     int i;
     for (i = 0; i < tab->nInv; i++) {
	  if(OBJcompare(tab->vettInv[i], obj)==0)
	       return i;
     }
     return -1;
}

int OBJcompare(inv_t o1, inv_t o2){
     return strcmp(o1.name, o2.name);
}

tabEquip_t *PGgetEquip(pg_t *pg){
     return pg->equip;
}

void delEquip(tabEquip_t *equip, int obj){
     int i,j;
     for (i = 0; i < equip->inUso; i++) {
	  if (equip->vettEq[i] == obj){
	       for (j = i+1; j < equip->inUso; j++) {
		    equip->vettEq[j-1] = equip->vettEq[j];
	       }
	       equip->inUso--;
	  }
	  return; //escludo il caso in cui sia ammissibile avere più oggetti uguali
     }
}

void upgradeStats(stat_t *pg_stat, stat_t obj_stat){
     int i, nstat=6, tmp;
     int *pg = &pg_stat->atk, *obj = &obj_stat.atk;
     for (i = 0; i < nstat ; i++) {
	  tmp = (*(pg+i)+ *(obj+i));
	  if ( tmp < 1)
	       *(pg+i) = 1;
	  else
	       *pg = tmp;
     }
} /*itera la struct con un puntatore a intero, non funziona*/

cmd getCmd(char *commands[]){
     int i;
     char *tmp = malloc(MAX_STR * sizeof(char));
     printf("Comandi disponibili:\nload_champ\nload_obj\nadd_champ\ndel_champ\nequip\nunequip\nget_stats\nprint\nstop\n>");
     scanf("%s", tmp);
     for (i = 0; i < N_CMD; i++) {
	  if (strcmp(tmp, commands[i])==0)
	       return (cmd) i;
     }
     return -1;
}

void PGequip(pg_t *pg, int obj){
     if (pg->equip == NULL)
	  pg->equip = newEquip();
     addEquip(pg->equip,obj);
}
