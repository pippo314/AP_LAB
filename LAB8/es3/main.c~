/*LABORATORIO 8 ESERCIZIO 3*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_CODE 6
#define DIM_STR 50
#define MAX_O 50
#define MAX_I 8
#define MAXC 6
#define N_CMD 10
#define FILE_NAME "pg.txt"

//DATA STRUCTURES
typedef enum {load_champ, load_obj, add_champ, del_champ, equip, unequip, get_stats, print} cmd;

typedef struct {int hp,mp,atk,def,mag,spr;} stat_t;

typedef struct {char *name, *type; stat_t stats;} obj_t;

typedef struct {obj_t *objects; int nObj;} inv_t;

typedef struct {int isUsed; obj_t **equip;} tabEquip_t;

typedef struct {char *code, *name, *class; tabEquip_t *equip; stat_t stats;} champ_t, *pchamp_t;
typedef char* Key;

typedef struct node node_t, *link;
struct node {
     champ_t champ;
     link next;
};

typedef struct {link headPg, tailPg; int nPg;} tabPg_t;
//PROTOTYPES
cmd getCmd(char **commands);
void readFileC(char *file_name, tabPg_t *tab);


//FUNCTIONS FOR obj_t
obj_t scanObj(FILE *p);


//FUNCTIONS FOR stat_t
stat_t scanStats(FILE *fp);
void showStats(FILE *fp, stat_t s);

//FUNCTIONS FOR champ_t (supposed to be an ITEM)
pchamp_t CHAMPnew();
pchamp_t CHAMPscan(FILE *fp);
pchamp_t CHAMPsetVoid();
void CHAMPshow(FILE *fp, pchamp_t c);
int CHAMPcheckVoid(pchamp_t c);
Key KEYget(pchamp_t c);
int KEYcompare(Key k1, Key k2);

//FUNCTIONS FOR THE LIST
link newNode(champ_t c, link next);
void listInsHead(tabPg_t *tabPg, champ_t c);
void listDelKey(tabPg_t *tabPg, Key key);
pchamp_t listSearch(tabPg_t *tabPg, Key key);
void listPrint(tabPg_t *l);

tabPg_t *newTabPg();

/*******START MAIN*******/
int main(int argc, char *argv[])
{
     char *cmds[N_CMD] ={"load_champ", "load_obj", "add_champ", "del_champ", "equip", "unequip", "get_stats", "print"};
     cmd command;
     tabPg_t *tabPg = newTabPg(); //qual è il miglior modo per fare questo?
     while ((command = getCmd(cmds))!=-1) {
	  switch (command) {
	  case load_champ: {
	       readFileC(FILE_NAME, tabPg);
	       break;
	  }
	  case load_obj: {break;}
	  case add_champ: {break;}
	  case del_champ: {break;}
	  case equip: {break;}
	  case unequip: {break;}
	  case get_stats: {break;}
	  case print: {
	       listPrint(tabPg);
	       break;}
default:
	       break;
	  }
     }
     return 0;
}
/*******END MAIN*******/

link newNode(champ_t c, link next){
     link x = malloc(sizeof(champ_t));
     if (x == NULL)
	  return NULL;
     x->champ=c;
     x->next=next;
     return x;
}

void listInsHead(tabPg_t *tabPg, champ_t c){
     tabPg->headPg=newNode(c,tabPg->tailPg);
}

void listDelKey(tabPg_t *tabPg, Key key){
     link x, prev, h=tabPg->headPg;
     for(x=h, prev=NULL; x!=NULL; prev=x, x=x->next) {
	  if (KEYcompare(key, KEYget(&x->champ))==0){
	       if(x==h)
		    h=x->next;
	       else
		    prev->next=x->next;
	       free(x);
	       break;
	  }
     }
}

int KEYcompare(Key k1, Key k2){
     return strcmp(k1, k2);
}

Key KEYget(pchamp_t c){
     return c->code;
}

pchamp_t listSearch(tabPg_t *tabPg, Key key){

     for(link x=tabPg->headPg; x!=NULL; x=x->next)
	  if(KEYcompare(key, KEYget(&x->champ))==0)
	       return &x->champ;
     return CHAMPsetVoid();
}

pchamp_t CHAMPsetVoid(){
     pchamp_t c=CHAMPnew();
     c->code = NULL;
     c->class = NULL;
     c->equip = NULL;
     c->name = NULL;
     return c;
}

cmd getCmd(char **commands){
     int i;
     char *tmp = malloc(MAX_O * sizeof(char));
     printf("Comandi disponibili:\n");
     printf("load_champ, load_obj, add_champ, del_champ, equip, unequip, get_stats, print\n");
     printf("Inserire comando.\n>");
     fscanf(stdin, "%s", tmp);
     for (i = 0; i < N_CMD; ++i)
	  if (strcmp(commands[i], tmp)==0)
	       return (cmd) i;
     free(tmp);
     return -1;
}

void readFileC(char *file_name, tabPg_t *tab){
     FILE *fp = fopen(file_name, "r");
     pchamp_t c;
     fscanf(fp, "%d", &tab->nPg);
//     do
     for(int i=0; i<tab->nPg;i++)   {
	  c = CHAMPscan(fp);
	  listInsHead(tab, *c); }
//     } while (CHAMPcheckVoid(c)==0);
}

stat_t scanStats(FILE *fp){
     stat_t s;
     fscanf(fp, "%d %d %d %d %d %d", &s.hp, &s.mp, &s.atk, &s.def, &s.mag, &s.spr);
     return s;
}

pchamp_t CHAMPscan(FILE *fp){
     pchamp_t c = CHAMPnew();
     char *tmp1,*tmp2, *tmp3;
     tmp1=malloc(DIM_STR * sizeof(char));
     tmp2=malloc(DIM_STR * sizeof(char));
     tmp3=malloc(DIM_STR * sizeof(char));
     if (fscanf(fp, "%s %s %s", tmp1, tmp2, tmp3) != EOF ) {
	  strcpy(c->code,tmp1);
	  strcpy(c->name, tmp2);
	  strcpy(c->class,tmp3);
	  c->stats = scanStats(fp);
	  free(tmp1);
	  free(tmp2);
	  free(tmp3);
	  return c;
     } else return CHAMPsetVoid();
}

pchamp_t CHAMPnew(){
     pchamp_t pc = malloc(sizeof(champ_t));
     pc->code = (char *) malloc(DIM_CODE * sizeof(char));
     pc->name = malloc(DIM_STR * sizeof(char));
     pc->class = malloc(DIM_STR *sizeof(char));
     return pc;
}

tabPg_t *newTabPg(){
     tabPg_t *tab;
     tab = (tabPg_t *) malloc(sizeof(tabPg_t));
     tab->headPg=NULL;
     tab->tailPg=NULL;
     tab->nPg=0;
     return tab;
}

void listPrint(tabPg_t *l){
     link x;
     int i;
     for ( x=l->headPg, i=0; i < l->nPg; x=x->next, i++) {
	  CHAMPshow(stdout, &(l->headPg->champ));
     }
}

void CHAMPshow(FILE *fp, pchamp_t c){
     fprintf(fp, "%s %s %s", c->code, c->name, c->class);
     showStats(fp, c->stats);
}

void showStats(FILE *fp, stat_t s){
     fprintf(fp, "%d %d %d %d %d %d", s.atk, s.def, s.hp, s.mag, s.mp, s.spr);
}

int CHAMPcheckVoid(pchamp_t c){
     if(c->code == NULL)
	  return 1;
     return 0;
}
