/*LONDRALIU Alexandra-Nicoleta - 311 CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct celulaB {  // definire lista dublu inlantuita cu santinela
  char info;
  struct celulaB *pre, *urm;
} TCelulaB, *TListaB;
/* TCelulaB este o variabila care retine 'info', 'pre' si 'urm'('pre' si 'urm' sunt pointeri care pointeaza \
catre celula anterioara, respectiv celula urmatoare).
TListaB este un pointer catre tipul TCelulaB.*/

typedef struct banda {  // definire banda
  TListaB content;
  TListaB poz;
} TBanda;  // TBanda este o variabila care retine continutul benzii si pozitia (degetul)

typedef struct celula {  // definire lista simplu inlantuita
  char info[MAX];
  struct celula *urm;
} TCelula, *TLista;  // TCelula este o variabila care retine 'info' si 'urm'('urm' este un pointer care pointeaza \
catre celula urmatoare). TLista este un pointer catre tipul TCelula.

typedef struct coada {  // definire coada folosind o lista simplu inlantuita
  TLista inc, sf;
} TCoada;  // TBanda este o variabila care retine inceputul si sfarsitul cozii

typedef struct celula_stiva {  // definire stiva folosind o lista simplu inlantuita
    TListaB info;
    struct celula_stiva *urm;
} TcelulaStiva, *TStiva;  // TCelulaStiva este o variabila care retine 'info' si 'urm'('urm' este un pointer care \
pointeaza catre celula urmatoare). TStiva este un pointer catre tipul TcelulaStiva.


TListaB AlocCelulaB(char x);
TListaB InitListaB();
void AdaugListaB(TListaB L, char data);
TBanda *InitBanda();
void SHOW(TBanda *b, FILE *out);
void SHOW_CURRENT(TBanda *b, FILE *out);
void WRITE_C(TBanda *b, char data);
void MOVE_RIGHT(TBanda *b);
void MOVE_LEFT(TBanda *b);
void MOVE_RIGHT_CHAR(TBanda *b, char data);
void MOVE_LEFT_CHAR(TBanda *b, char data, FILE *out);
int INSERT_RIGHT_CHAR(TBanda *b, char data);
int INSERT_LEFT_CHAR(TBanda *b, char data, FILE *out);
TStiva InitSt(void);
int push(TStiva *vf, TListaB x);
int pop(TStiva *vf, TListaB *x);
TCoada *InitQ();
int IntrQ(TCoada *c, char *x);
int ExtrQ(TCoada *c, char *x);
void DistrQ(TCoada **c);
void DistrSt(TStiva *vf);
void DistrugeListaB(TListaB *aL);
void DistrB(TBanda **b);
