#include <iostream>
#include "lista.h"


void dodaj_koniec(struct lista *glowa, int n) {

    if(!glowa->liczba) {
        glowa->liczba = n;
        glowa->next =NULL;
        return;
    }

	lista *newlista = new lista;
	newlista->liczba = n;
	newlista->next = NULL;

	lista *aktualny = glowa;
	while(aktualny) {
		if(aktualny->next == NULL) {
			aktualny->next = newlista;
			return;
		}
		aktualny = aktualny->next;
	}
}

void dodaj_poczatek(struct lista **glowa, int n) {

    if(!(*glowa)->liczba) {
        (*glowa)->liczba = n;
        (*glowa)->next =NULL;
        return;
    }

	lista *newlista = new lista;
	newlista->liczba = n;
	newlista->next = *glowa;
	*glowa = newlista;
}
int elem_at(struct lista *glowa, int n) {

    int licznik = 0;
    lista *aktualny = glowa;
	while(aktualny) {
        if(licznik == n) {
            return aktualny->liczba;
        }
		if(aktualny->next == NULL) {
			return -1;
		}
		aktualny = aktualny->next;
		licznik++;
	}
}

void usun(struct lista *glowa) {
    lista *aktualny = glowa->next;
    lista *tmp;

    while(aktualny) {
        tmp = aktualny->next;
        delete aktualny;
        aktualny = tmp;
    }

    glowa->liczba = NULL;
}

int rozmiar(lista *head) {
    lista *aktualny = head;
    int licznik = 0;

    while(aktualny) {
            licznik++;
        if(!aktualny->next) {
            return licznik;
        }

        aktualny = aktualny->next;
    }

    return -1;
}
