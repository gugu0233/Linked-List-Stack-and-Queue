/*LONDRALIU Alexandra-Nicoleta - 311 CB*/
#include "header.h"

int main() {
  TBanda *b = InitBanda();  // initializare banda
  TCoada *c = InitQ();  // initializare coada
  TStiva s_undo = InitSt();  // initializare stiva pentru operatia UNDO
  TStiva s_redo = InitSt();  // initializare stiva pentru operatia REDO
  if (!b)  // verificare alocare
    return 1;
  if (!c)
    return 1;
  int n = 0, i = 0;
  char string[MAX], elem[MAX];
  char input_filename[] = "tema1.in";
  FILE *in = fopen(input_filename, "rt");  // deschidere fisier de intrare pentru citire in modul text
  if (in == NULL) {  // verific daca fisierul a fost deschis cu succes
    fprintf(stderr, "ERROR: Fisierul nu a putut fi deschis %s", input_filename);
    return -1;
  }
  char output_filename[] = "tema1.out";
  FILE *out = fopen(output_filename, "wt");  // deschidere fisier de iesire pentru a scrie rezultatul in modul text
  if (out == NULL) {  // verific daca fisierul a fost deschis cu succes
    fprintf(stderr, "ERROR: Fisierul nu a putut fi deschis %s", output_filename);
    return -1;
  }
  fscanf(in, "%d", &n);  // citesc numarul de operatii din fisier
  fgets(string, MAX, in);  // incep citirea operatiilor
  for (i = 0; i < n; i++) {
    fgets(string, MAX, in);
    string[strlen(string)-1] = '\0';  // adaug null la sfarsitul fiecarei operatii
    if (strcmp(string, "EXECUTE") != 0 && strcmp(string, "SHOW") != 0 && strcmp(string, "SHOW_CURRENT") != 0 && \
        strcmp(string, "UNDO") !=0 && strcmp(string, "REDO") != 0)
      IntrQ(c, string);  // adaug in coada toate operatiile, inafara de EXECUTE, SHOW, SHOW_CURRENT, UNDO si REDO
    // verific operatia citita si apelez functia corespunzatoare
    if (strcmp(string, "SHOW") == 0)
      SHOW(b, out);
    if (strcmp(string, "SHOW_CURRENT") == 0)
      SHOW_CURRENT(b, out);
    if (strcmp(string, "EXECUTE") == 0) {  // daca operatia citita este EXECUTE
        ExtrQ(c, elem);  // extrag din coada prima operatie retinuta
        if (strcmp(elem, "MOVE_RIGHT") == 0) {  // daca operatia extrasa din coada este MOVE_RIGHT
            push(&s_undo, b->poz);  // intai retin in stiva pentru UNDO pozitia degetului, dupa care execut operatia
            MOVE_RIGHT(b);
          }
        if (strcmp(elem, "MOVE_LEFT") == 0) {  // daca operatia extrasa din coada este MOVE_LEFT
            push(&s_undo, b->poz);  // intai retin in stiva pentru UNDO pozitia degetului
            TListaB aux = b->poz;
          MOVE_LEFT(b);
          if (aux == b->poz)  // daca degetul este pe prima pozitie, execut o singura data operatia
            pop(&s_undo, &b->poz);
          }
        // verific operatia citita si apelez functia corespunzatoare
        if (strstr(elem, "MOVE_RIGHT_CHAR") != 0)
          MOVE_RIGHT_CHAR(b, elem[strlen(elem)-1]);
        if (strstr(elem, "MOVE_LEFT_CHAR") != 0)
          MOVE_LEFT_CHAR(b, elem[strlen(elem)-1], out);
        if (strstr(elem, "WRITE") != 0)
          WRITE_C(b, elem[strlen(elem)-1]);
        if (strstr(elem, "INSERT_RIGHT") != 0)
          INSERT_RIGHT_CHAR(b, elem[strlen(elem)-1]);
        if (strstr(elem, "INSERT_LEFT") != 0)
          INSERT_LEFT_CHAR(b, elem[strlen(elem)-1], out);
      }
      if (strcmp(string, "UNDO") == 0) {  // pentru operatia UNDO
        push(&s_redo, b->poz);  // retin in stiva pentru REDO pointerul la pozitia degetului
        pop(&s_undo, &b->poz);  // extrag din stiva pentru UNDO pointerul la vechea pozitie
      }
    if (strcmp(string, "REDO") == 0) {  // pentru operatia REDO
        push(&s_undo, b->poz);  // retin in stiva pentru UNDO pozitia degetului
        pop(&s_redo, &b->poz);  // extrag din stiva pentru REDO vechea pozitie
      }
  }
// distrug toate structurile si inchid fisierele
  DistrSt(&s_undo);
  DistrSt(&s_redo);
  DistrQ(&c);
  DistrB(&b);
  fclose(in);
  fclose(out);
  return 0;
}
