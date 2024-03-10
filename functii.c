/*LONDRALIU Alexandra-Nicoleta - 311 CB*/
#include "header.h"

TListaB AlocCelulaB(char x) {  // functie pentru alocarea unei celule
    TListaB aux = (TListaB)malloc(sizeof(TCelulaB));  // aloc memorie pentru celula
    if (!aux)  // verific daca alocarea a reusit
        return NULL;
    aux->info = x;  // atribui caracterul respectiv celulei
    aux->pre = aux->urm = NULL;
    return aux;
}

TListaB InitListaB() {  // functie pentru initializarea unei liste care permite retinerea \
continutului benzii
    TListaB aux = AlocCelulaB('|');
    if (!aux)
        return NULL;
    aux->urm = AlocCelulaB('#');
    if (!(aux->urm))
        return NULL;
    return aux;
}

void AdaugListaB(TListaB L, char data) {  // functie de adaugare in lista
    TListaB ultim = NULL;
    for (ultim = L; ultim->urm != NULL; ultim = ultim->urm)  // parcurg lista pana la final
        continue;
    TListaB aux = AlocCelulaB(data);  // aloc noua celula de inserat
    ultim->urm = aux;  // leg ultima celula din lista de noua celula de inserat
    aux->pre = ultim;
}

TBanda *InitBanda() {  // functie pentru initializarea benzii
    TBanda *b = (TBanda *)malloc(sizeof(TBanda));  // alocare
    if (!b)
        return NULL;  // verific daca alocarea a reusit
    b->content = InitListaB();  // initializez continutul benzii
    if (!(b->content)) {
        free(b);
        return NULL;  // verific daca alocarea a reusit
    }
    b->poz = b->content->urm;  // setez degetul pe prima pozitie din banda (dupa santinela)
    return b;
}

void SHOW(TBanda *b, FILE *out) {  // functia SHOW, care afiseaza in fisier banda
    TListaB L = b->content->urm;  // L este o lista dublu inlantuita care porneste de la primul \
    element de dupa santinela
    TListaB p = NULL;
    for (p = L; p != NULL; p = p->urm)  // parcurg lista
        if (p != b->poz) {  // cazul in care nu sunt pe pozitia curenta
            fprintf(out, "%c", p->info);
        } else {  // cazul in care sunt pe pozitia curenta, afisez conform cerintei
            fprintf(out, "|");
            fprintf(out, "%c", p->info);
            fprintf(out, "|");
        }
    fprintf(out, "\n");
}

void SHOW_CURRENT(TBanda *b, FILE *out) {  // functia SHOW_CURRENT, care afiseaza elementul de pe \
pozitia curenta
    fprintf(out, "%c", b->poz->info);
    fprintf(out, "\n");
}

void WRITE_C(TBanda *b, char data) {  // functia WRITE_C, care actualizeaza caracterul de pe pozitia curenta
    b->poz->info = data;
}

void MOVE_RIGHT(TBanda *b) {  // functia MOVE_RIGHT, care muta degetul cu o pozitie spre dreapta
    if (b->poz->urm == NULL)  // cazul in care ma aflu pe ultima pozitie
        AdaugListaB(b->content, '#');  // inserez caracterul # si mut degetul pe noul caracter
    b->poz = b->poz->urm;  // altfel doar mut degetul cu o pozitie mai la dreapta
}

void MOVE_LEFT(TBanda *b) {    // functia MOVE_LEFT, care muta degetul cu o pozitie spre stanga
    if (b->poz->pre == NULL)  // cazul in care ma aflu pe prima pozitie
        b->poz = b->poz;  // degetul ramane in acelasi loc
    else
        b->poz = b->poz->pre;  // altfel il mut cu o pozitie spre stanga
}

void MOVE_RIGHT_CHAR(TBanda *b, char data) {  // functia MOVE_RIGHT_CHAR, care muta degetul spre dreapta \
pana la un anumit simbol
    TListaB L = b->poz;  // pornesc de la pozitia curenta
    TListaB p = NULL;
    for (p = L; p->urm != NULL; p = p->urm)  // parcurg continutul benzii spre dreapta
        if (p->info == data) {  // daca am gasit simbolul, actualizez pozitia degetului
            b->poz = p;
            return;}
    if (p->urm == NULL && p->info != data) {  // cazul in care am ajuns la limita din dreapta fara sa \
gasesc simbolul
        AdaugListaB(b->content, '#');  // inserez caracterul # si mut degetul pe caracter
        b->poz = p->urm;
    } else {
    b->poz = p;
    }
}

void MOVE_LEFT_CHAR(TBanda *b, char data, FILE *out) {  // functia MOVE_LEFT_CHAR, care muta degetul \
spre stanga pana la un anumit simbol
    TListaB L = b->poz;  // pornesc de la pozitia curenta
    TListaB p = NULL;
    for (p = L; p->pre != NULL; p = p->pre)  // parcurg continutul benzii spre stanga
        if (p->info == data) {  // daca am gasit simbolul, actualizez pozitia degetului
            b->poz = p;
            return;}
    if (p->pre == NULL && p->info != data)  // cazul in care am ajuns la limita din stanga a benzii si nu \
am gasit simbolul
        fprintf(out, "ERROR\n");  // afisez mesajul ERROR si nu modific pozitia degetului
    else
        b->poz = p;
}

int INSERT_RIGHT_CHAR(TBanda *b, char data) {  // functia INSERT_RIGHT_CHAR, care insereaza un caracter \
in dreapta pozitiei degetului
    if (b->poz->urm == NULL) {  // cazul in care degetul este pe ultimul caracter
        AdaugListaB(b->content, data);  // inserez noul caracter
        b->poz = b->poz->urm;  // mut pozitia degetului pe noul caracter inserat
        return 1;
    }
    TListaB aux = AlocCelulaB(data);  // daca nu ma aflu la finalul benzii, aloc noua celula de inserat
    if (!aux)  // verific daca alocarea a reusit
        return 0;
    aux->urm = b->poz->urm;  // refac legaturile intre celule
    aux->pre = b->poz;
    b->poz->urm = aux;
    aux->urm->pre = aux;
    b->poz = aux;
    return 1;
}

int INSERT_LEFT_CHAR(TBanda *b, char data, FILE *out) {  // functia INSERT_LEFT_CHAR, care insereaza un \
caracter in stanga pozitiei degetului
    if (b->poz->pre == NULL) {  // cazul in care degetul se afla pe prima pozitie
        fprintf(out, "ERROR\n");  // afisez mesajul ERROR
        return 1;
    }
    TListaB aux = AlocCelulaB(data);  // daca nu ma aflu la inceputul benzii, aloc noua celula de inserat
    if (!aux)  // verific daca alocarea a reusit
        return 0;
    aux->urm = b->poz;  // refac legaturile intre celule
    aux->pre = b->poz->pre;
    b->poz->pre->urm = aux;
    b->poz->pre = aux;
    b->poz = aux;
    return 1;
}

TStiva InitSt(void) {  // functie pentru initializarea unei stive vide
    return NULL;
}

int push(TStiva *vf, TListaB x) {  // functie de inserare la inceput in stiva
    TStiva aux = (TStiva)malloc(sizeof(TcelulaStiva));  // alocarea
    if (!aux)  // verific daca alocarea a reusit
        return 0;
    aux->info = x;  // inserez caracterul in celula
    aux->urm = *vf;  // refac legaturile
    *vf = aux;
    return 1;
}

int pop(TStiva *vf, TListaB *x) {  // functie pentru extragerea primului element din stiva
    TStiva aux = NULL;
    aux = *vf;  // retin varful stivei
    if (aux == NULL)
        return 0;
    *x = aux->info;  // refac legaturile
    *vf = aux->urm;
    free(aux);  // eliberez memoria
    return 1;
}

TCoada *InitQ() {  // functie pentru initializarea unei cozi
    TCoada *c = (TCoada *)malloc(sizeof(TCoada));  // alocarea
    if (!c)  // verific daca alocarea a reusit
        return NULL;
    c->inc = c->sf = NULL;
    return c;
}

int IntrQ(TCoada *c, char *x) {  // functie pentru adaugarea unui element la sfarsitul cozii
    TLista aux = NULL;
    aux = (TLista)malloc(sizeof(TCelula));  // alocarea unei noi celule
    if (!aux)  // verific daca alocarea a reusit
        return 0;
    snprintf(aux->info, strlen(x)+1, "%s", x);  // adaug caracterul in celula
    aux->urm = NULL;
    if (c->sf != NULL)  // cazul in care coada nu este vida
        c->sf->urm = aux;  // leg celula dupa ultima din coada
    else
        c->inc = aux;  // noua celula se afla inceputul cozii
    c->sf = aux;  // actualizez sfarsitul cozii
    return 1;
}

int ExtrQ(TCoada *c, char *x) {  // functie pentru extragerea primului element din coada
    TLista aux = NULL;
    if (c->inc == NULL)  // caz in care coada e vida
        return 0;
    aux = c->inc;  // retin primul element din coada
    snprintf(x, strlen(aux->info)+1, "%s", aux->info);  // extrag primul caracter
    c->inc = aux->urm;  // refac legaturile
    if (c->inc == NULL)
        c->sf = NULL;
    free(aux);  // eliberez memoria
    return 1;
}

void DistrQ(TCoada **c) {  // functie pentru distrugerea cozii
    TLista p = NULL, aux = NULL;
    p = (*c)->inc;
    while (p) {  // dezaloc toate celulele
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*c);  // dezaloc structura de coada
    *c = NULL;  // setez pointerul pe NULL, intrucat coada nu mai exista
}

void DistrugeListaB(TListaB *aL) {  // functie pentru distrugerea unei liste dublu inlantuite cu santinela
    TListaB p = (*aL)->urm, aux = NULL;
    while (p != NULL) {  // dezaloc toate celulele
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*aL);  // dezaloc structura de lista
    *aL = NULL;  // setez pointerul pe NULL, intrucat lista nu mai exista
}

void DistrB(TBanda **b) {  // functie pentru distrugerea benzii
    DistrugeListaB(&((*b)->content));  // pentru continutul benzii folosesc functia pentru distrugerea unei liste
    (*b)->poz = NULL;  //
    free(*b);  // dezaloc structura de banda
    *b = NULL;  // setez pointerul pe NULL, intrucat banda nu mai exista
}

void DistrSt(TStiva *vf) {  // functie pentu distrugerea stivei
    TListaB aux = NULL;
    while (*vf)  // extrag element cu element din stiva
        pop(vf, &aux);
    *vf = NULL;  // setez pointerul pe NULL, intrucat stiva nu mai exista
}
