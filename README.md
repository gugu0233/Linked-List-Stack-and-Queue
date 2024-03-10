main.c

  Incep prin a declara si initializa, cu ajutorul functiilor de initializare, cate o variabila pentru fiecare 
structura necesara: banda, coada, stiva pentru UNDO si cea pentru REDO. Dupa ce verific ca alocarea s-a produs 
cu succes, declar variabila n, pentru numarul operatiilor citite din fisier, variabila i pentru parcurgerea 
operatiilor, variabila string in care voi retine fiecare operatie si variabila elem in care retin operatia extrasa 
din coada.
  Apoi, deschid fisierul de intrare, "tema1.in", pentru citire in modul text si cel de iesire, "tema1.out", pentru 
a scrie rezultatul si verific daca au fost deschise cu succes, afisand un mesaj corespunzator in caz contrar.
  Citesc din fisier numarul de operatii n, apoi operatiile, cu ajutorul functiei fgets, pentru a retine in 
variabila string cate o linie din fisier si adaug caracterul null dupa fiecare linie (operatie).
  Incep sa verific operatia retinuta in string. Daca aceasta este diferita de EXECUTE, SHOW, SHOW_CURRENT, UNDO si
REDO, o adaug in coada pentru a putea fi executata in momentul in care intlanesc operatia EXECUTE. Daca operatia 
este SHOW, apelez functia SHOW, iar daca este SHOW_CURRENT, apelez functia SHOW_CURRENT. Pentru operatia
EXECUTE, extrag din coada prima operatie, pe care o retin in variabila elem. Daca aceasta este MOVE_RIGHT, 
retin in stiva pentru UNDO pointerul la pozitia degetului, apoi execut operatia. Daca operatia din elem este 
MOVE_LEFT, retin in stiva pentru UNDO, la fel ca la MOVE_RIGHT, pointerul la pozitia degetului, apoi execut 
operatia. Insa, pentru a nu executa de mai multe ori operatia daca degetul este pe prima pozitie, iau o 
variabila auxiliara aux, care ma ajuta sa stiu daca degetul este pe prima pozitie in banda. Daca da, atunci 
extrag din stiva de UNDO pointerul la pozitia degetului, pentru a executa operatia o singura data.
Pentru restul operatiilor, MOVE_LEFT_CHAR, MOVE_RIGHT_CHAR, WRITE, INSERT_LEFT si INSERT_RIGHT, verific 
operatia din elem si apelez functia corespunzatoare.
  Pentru operatia UNDO, retin in stiva pentru REDO pointerul la pozitia curenta a degetului, dupa care extrag 
din stiva pentru UNDO pointerul la vechea pozitie, modificand astfel pozitia curenta a degetului cu cea veche, 
adica cea de dinaintea executarii operatiei. Similar pentru operatia REDO, retin in stiva pentru UNDO pozitia 
curenta a degetului si extrag din stiva pentru REDO vechea pozitie, astfel actualizand pozitia degetului cu cea 
veche.
  Dupa executarea fiecarei operatii, eliberez toata memoria alocata cu ajutorul functiilor de distrugere si 
inchid fisierele deschise.

functii.c

 'AlocCelulaB' este functia pentru alocarea unei celule intr-o lista dublu inlantuita, care primeste ca parametru 
un caracter. Intai aloca memorie pentru celula si verifica daca alocarea s-a produs cu succes, apoi adauga caracterul 
in celula si seteaza pointerii pentru legaturi (pre si urm) pe NULL, deoarece celula nu este legata de nicio alta 
celula. La final, returneaza celula creata.
 'InitLista' este functia pentru initializarea unei liste care permite retinerea continutlui benzii. Folosind 
functia anterioara de alocare a unei celule, 'AlocCelulaB', initializeaza banda, care contine initial caracterele 
'|#', verificand dacaf iecare alocare s-a produs cu succes.
 'AdaugListaB' primeste ca parametrii o lista si un caracter. Functia parcurge lista pana ajunge la finalul 
acesteia apoi aloca noua celula de inserat folosind functia 'AlocCelulaB' si actualizeaza legaturile astfel 
incat ultima celula din lista sa fie legata de noua celula si invers.
 'InitBanda' este functia pentru initializarea benzii. Intai aloca memorie pentru banda si verifica daca alocarea 
s-a produs cu succes. Apoi, functia initializeaza continutul benzii cu ajutorul functiei de initializare a unei 
liste dublu inlantuite, 'InitLista', iar degetul pointeaza la primul element de dupa santinela. La final 
returneaza banda.
 'SHOW' afiseaza banda in fisier. Functia primeste ca parametrii un pointer catre banda si unul la fisierul de iesire. 
Parcurge lista, pornind de la primul element de dupa santinela, si verifica cele doua cazuri: daca degetul nu 
se afla pe caracter, functia afiseaza doar caracterul, altfel, degetul este pe caracter, deci il afiseaza intre '|'.
 'SHOW_CURRENT' afiseaza elementul de pe pozitia curenta a degetului. Functia primeste ca parametrii un pointer 
la banda si unul la fisierul de iesire si afiseaza in fisier caracterul unde pointeaza degetul.
 'WRITE_C' actualizeaza caracterul curent. Functia primeste un pointer la banda si un caracter, actualizand astfel 
elementul unde pointeaza degetul cu caracterul.
 'MOVE_RIGHT' muta degetul cu o pozitie spre dreapta. Daca degetul se afla pe ultima pozitie, atunci adauga o noua 
celula care contine caracterul '#', folosind functia 'AdaugListaB'si muta degetul pe noul caracter inserat. Altfel,
functia doar muta degetul pe urmatorul caracter din banda.
 'MOVE_LEFT' muta degetul cu o pozitie spre stanga. Daca degetul se afla pe prima pozitie, atunci acesta ramane in 
aceeasi pozitie, altfel il muta pe urmatorul caracter din stanga.
 'MOVE_RIGHT_CHAR' primeste ca parametrii banda si un caracter si muta degetul spre dreapta pana gaseste acel 
caracter. Functia parcurge continutul benzii de la pozitia degetului pana la final, iar daca a fost gasit caracterul,
actualizeaza pozitia degetului, altfel, daca s-a ajuns la finalul benzii si caracterul nu a fost gasit, adauga 
caracterul '#' si muta degetul pe noul caracter.
 'MOVE_LEFT_CHAR' primeste ca parametrii banda, un caracter, si fisierul de iesire si muta degetul spre stanga pana
gaseste acel caracter. Functia parcurge continutul benzii de la pozitia degetului spre inceput, iar daca a gasit 
caracterul, actualizeaza pozitia degetului, altfel, daca am ajuns la limita din stanga a benzii si nu a fost 
gasit caracterul, functia afiseaza mesajul de eroare in fisier si nu modifica pozitia degetului.
 'INSERT_RIGHT_CHAR' primeste ca parametrii banda si un caracter, pe care il insereaza in dreapta pozitiei degetului.
Daca degetul este pe ultimul caracter, functia insereaza noul caracter, folosind functia 'AdaugListaB', si 
muta degetul pe noul element inserat. Altfel, aloca noua celula de inserat, verifica alocarea si reface legaturile 
intre celule.
 'INSERT_LEFT_CHAR' primeste ca parametrii banda, un caracter si fisierul de iesire si insereaza in stanga pozitiei 
degetului caracterul respectiv. Daca degetul este pe prima pozitie, functia afiseaza mesajul de eroare in fisier, 
altfel, aloca noua celula de inserat, verifica alocarea si reface legaturile intre celule.
 'InitSt' initializeaza o stiva vida.
 'push' primeste ca parametrii un pointer la stiva si un caracter pe care il insereaza la inceputul stivei(in varf). 
Dupa alocare si verificare, functia insereaza caracterul in celula noua si reface legaturile.
 'pop' primeste ca parametrii un pointer la stiva si adresa elementului extras din stiva. Functia retine intr-o 
variabila auxiliara varful stivei, reface legaturile mutand varful pe urmatorul element, apoi elibereaza memoria. 
 'InitQ' este functia pentru initializarea unei cozi vide.
 'IntrQ' adauga un element in coada. Dupa alocarea unei noi celule si verificare, adauga caracterul de inserat 
in celula. Daca coada nu este vida, functia leaga celula noua dupa ultima din coada, altfel, noua celula va fi
prima din coada. La final, actualizeaza sfarsitul cozii, care in ambele cazuri, este noua celula inserata.
 'ExtraQ' extrage primul element din coada. Daca coada este vida, functia returneaza 0, deoarece nu este niciun  
element de extras, altfel retine intr-o variabula auxiliara inceputul cozii, extrage primul element, dupa care 
reface legaturile in coada si elibereaza memoria ocupata de primul element care a fost extras.
 'DistrQ' distruge coada. Intai, dezaloca memoria pentru fiecare celula a cozii, apoi dezaloca structura de coada 
si seteaza pointerul, care pointa catre coada, pe NULL, pentru a indica ca aceasta nu mai exista.
 'DistrugeLista' distruge lista dublu inlantuita cu santinela. Intai, dezaloca toate celulele din lista, apoi 
dezaloca structura de lista si seteaza pointerul, care pointa catre lista, pe NULL, deoarece aceasta nu mai exista.
 'DistrB' distruge banda. Pentru continutul benzii, care este o lista dublu inlantuita cu santinela, foloseste 
functia anterioara de distrugere a unei liste , 'DistrugeLista', apoi seteaza pointerul pentru pozitia degetului pe
NULL, dezaloca structura de banda si seteaza si pointerul catre banda pe NULL.
 'DistrSt' distruge stiva. Foloseste functia de extragere a unui element din stiva, 'pop', pentru a extrage rand pe 
rand elementele, ramanand la final cu o stiva vida, pe care o seteaza pe NULL, intrucat nu mai exista.

 TOTAL punctaj obtinut: 100.0/100
 Valgrind: 20/20
  
