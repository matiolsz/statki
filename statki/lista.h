#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

struct lista {
	int liczba;
	lista* next;
};

void dodaj_koniec(struct lista *glowa, int n);
void dodaj_poczatek(struct lista **glowa, int n);
int elem_at(struct lista *glowa, int n) ;
void usun(struct lista *glowa);
int rozmiar(lista *head);

#endif // LISTA_H_INCLUDED


