/*LABORATORIO 7 ESERCIZIO 3*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgList.h"
#include "Pg.h"
#include "invArray.h"

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

//PROTOTYPES

//UTILITY
cmd getCmd(char *commands[]);

/*******START MAIN*******/
int main(int argc, char *argv[])
{
     char *cmds[N_CMD] ={"load_champ", "load_obj", "add_champ", "del_champ", "equip", "unequip", "get_stats", "print", "stop"};
     cmd command;
     FILE *fp;
     pg_t *tmp_pg;
     inv_t *tmp_obj;
     char tmp_code[CODE], tmp_name[MAX_STR];
     pgList_t listPg = newList();
     invArray_t tabInv = newInvArray();

     while ((command = getCmd(cmds)) != -1) {
	  switch (command) {
	  case load_champ: {
	       fp = fopen(PG_FILE, "r");
	       pgList_readFile(fp, listPg);
	       fclose(fp);
	       break;
	  }
	  case load_obj: {
	       fp = fopen(INV_FILE, "r");
	       invArray_readFile(fp, tabInv);
	       fclose(fp);
	       break;
	  }
	  case add_champ: {
	       printf("Inserire dati personaggio:\n");
	       pgList_insert(listPg, PGscan(stdin));
	       break;
	  }
	  case del_champ: {
	       printf("Inserire codice personaggio da eliminare:\n");
	       scanf("%s", tmp_code);
	       pgList_remove(listPg, tmp_code);
	       break;
	  }
	  case equip: {
	       printf("Inserire codice personaggio:\n");
	       scanf("%s", tmp_code);
	       printf("Inserire nome oggetto:\n");
	       scanf("%s", tmp_name);
	       tmp_pg = pgList_searchByCode(listPg, tmp_code);
	       tmp_obj = invArray_searchByName(tabInv, tmp_name);
	       PGequip(tmp_pg, invArray_IndexOf(tabInv, *tmp_obj));
	       break;
	  }
	  case unequip: {
	       printf("Inserire codice personaggio:\n");
	       scanf("%s", tmp_code);
	       printf("Inserire nome oggetto:\n");
	       scanf("%s", tmp_name);
	       tmp_pg = pgList_searchByCode(listPg, tmp_code);
	       tmp_obj = invArray_searchByName(tabInv, tmp_name);
	       PGunequip(tmp_pg, invArray_IndexOf(tabInv, *tmp_obj));
	       break;
	  }
	  case get_stats: {
	       printf("Inserire codice personaggio:\n");
	       scanf("%s", tmp_code);
	       tmp_pg = pgList_searchByCode(listPg, tmp_code);
	       PGstatsEval(tmp_pg, tabInv);
	       PGshow(*tmp_pg, tabInv);
	       break;
	  }
	  case print: {
	       listPrint(listPg, tabInv);
	       printf("\n");
	       printTab(tabInv);
	       printf("\n");
	       break;
	  }
	  case stop: {
	       return 0;
	  }
	  default:
	       return 0;
	  }
     }
     return 0;
}
/*******END MAIN*******/
/* void readFilePG(char *file_name, pgList_t tab){ */
/*      int not_end=1; */
/*      pg_t pg_tmp; */
/*      FILE *fp = fopen(file_name, "r"); */

/*      while (not_end) { */
/* 	  pg_tmp = PGscan(fp); */
/* 	  if(!feof(fp)){ //se non è la fine del file aggiungi alla lista */
/* 	       listInsHead(tab, pg_tmp); */
/* 	  } else not_end = 0; */
/*      } */
/*      fclose(fp); */
/* } */

/* void readFileINV(char *file_name, invArray_t tabInv){ */
/*      int dim, i; */
/*      FILE *fp = fopen(file_name, "r"); */
/*      fscanf(fp, "%d", &dim); */
/*      setTabDim(tabInv, dim); */
/*      for (i = 0; i < dim; i++) { */
/* 	  INVaddObj(tabInv, OBJscan(fp)); */
/*      } */
/* //     fclose(fp); */
/* } */

cmd getCmd(char *commands[]){
     int i;
     char *tmp = malloc(MAX_STR * sizeof(char));
     printf("Comandi disponibili:\nload_champ\nload_obj\nadd_champ\ndel_champ\nequip\nunequip\nget_stats\nprint\nstop\n>");
     scanf("%s", tmp);
     printf("\n");
     for (i = 0; i < N_CMD; i++) {
	  if (strcmp(tmp, commands[i])==0)
	       return (cmd) i;
     }
     return -1;
}
