#include <iostream>

using namespace std;

struct nodoA {
	int valor;
	int fe;
	nodoA *izq;
	nodoA *der;
	nodoA *padre;
};

enum {izquierdo, derecho};

void rotaSD(nodoA* &raiz, nodoA *nodo) {
    nodoA *padreAux = nodo->padre;
    nodoA *p = nodo;
    nodoA *q = nodo->izq;
    nodoA *b = q->der;

    if (padreAux != NULL) {
        if (padreAux->der == p)
            padreAux->der = q;
        else
            padreAux->izq = q;
    }
    else
        raiz = q;

    p->izq = b;
    q->der = p;

    p->padre = q;

    if (b)
        b->padre = p;

    q->padre = padreAux;

    p->fe = 0;
    q->fe = 0;
}   

void rotaSI(nodoA* &raiz, nodoA *nodo) {
	nodoA *padreAux = nodo->padre;
	nodoA *p = nodo;
	nodoA *q = nodo->der;
    nodoA *b = q->izq;

    if (padreAux) {
        if (padreAux->izq== p)
            padreAux->izq = q;
        else
            padreAux->der = q;
    }
    else
        raiz = q;

    p->der = b;
    q->izq = p;

    p->padre = q;

    if (b != NULL)
        b->padre = p;

    q->padre = padreAux;

    p->fe = 0;
    q->fe = 0;
}   

void rotaDD(nodoA* &raiz, nodoA *nodo) {
	nodoA *padreAux = nodo->padre;
	nodoA *p = nodo;
	nodoA *q = nodo->izq;
	nodoA *r = q->der;
	nodoA *b = r->izq;
	nodoA *c = r->der;

	if (padreAux) {
		if (padreAux->izq == p)
			padreAux->izq = r;
		else
			padreAux->der = r;
	}
	else
		raiz = r;

	q->der = b;
	p->izq = c;
	r->izq = q;
	r->der = p;

	q->padre = p->padre = r;

	r->padre = padreAux;

	if(b != NULL)
		b->padre = q;

	if(c != NULL)
		c->padre = p;

	switch (r->fe) {
		case -1:
			q->fe = 0;
			p->fe = 1;
			break;

		case 0:
			q->fe = 0;
			p->fe = 0;
			break;

		case 1:
			q->fe = -1;
			p->fe = 0;
			break;
	}

	r->fe = 0;
}

void rotaDI(nodoA* &raiz, nodoA *nodo) {
	nodoA *padreAux = nodo->padre;
	nodoA *p = nodo;
	nodoA *q = nodo->der;
	nodoA *r = q->izq;
	nodoA *b = r->izq;
	nodoA *c = r->der;

	if (padreAux) {
		if (padreAux->der == nodo)
			padreAux->der = r;
		else
			padreAux->izq = r;
	}
	else
		raiz = r;

	q->izq = c;
	p->der = b;
	r->der = q;
	r->izq = p;

	q->padre = p->padre = r;

	r->padre = padreAux;

	if(c)
		c->padre = q;

	if(b)
		b->padre = p;

	switch (r->fe) {
		case -1:
			p->fe = 0;
			q->fe = 1;
			break;

		case 0:
			p->fe = 0;
			q->fe = 0;
			break;

		case 1:
			p->fe = -1;
			q->fe = 0;
			break;
	}

	r->fe = 0;
}

void profundidadNodo(nodoA *nodo, int &h) {
	int profN = 0;
	nodoA *aux = nodo;

	while (aux) {
		profN++;
		aux = aux->padre;
	}

	if (profN > h)
		h = profN;
}

void alturaArbol(nodoA *raiz, int &h) {
	if (raiz != NULL) {
		alturaArbol(raiz->izq, h);
		profundidadNodo(raiz, h);
		alturaArbol(raiz->der, h);
	}
}

int buscarDato(nodoA *raiz, int dato, nodoA* &actual, nodoA* &anterior) {
	int encontrado = 0;
	anterior = NULL;
	actual = raiz;
	while (!encontrado && actual != NULL) {
		if (actual->valor == dato)
			encontrado = 1;
		else {
			anterior = actual;
			if (actual->valor > dato)
				actual = actual->izq;
			else
				actual = actual->der;
		}
	}

	return encontrado;
}

nodoA *nodoNuevo(nodoA* &padre, int datoN) {
	nodoA *nuevo = new nodoA;
	nuevo->valor = datoN;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	nuevo->fe = 0;
	nuevo->padre = padre;

	return nuevo;
}

void equilibrar(nodoA *nodo, int rama, bool nuevo) {

}

void insertarDato(nodoA* &raiz, int dato) {
	nodoA *padreAux = NULL;
	nodoA *actual = raiz;
	int valAct = actual->valor;

	while (actual != NULL && actual->valor != dato) {
		padreAux = actual;
		valAct = actual->valor;

		if (dato > valAct)
			actual = actual->der;
		else
			actual = actual->izq;
	}

	if (actual != NULL)
		cout << "No se agregó, se repite el dato \n";
	else {
		if (padreAux == NULL) {
			nodoA *nuevo = new nodoA;
			nuevo->valor = dato;
			raiz = nuevo;
		}
		else {
			if (dato > padreAux->valor) {
				padreAux->der = nodoNuevo(padreAux, dato);
				equilibrar(padreAux, derecho, 1);
			}
			else {
				padreAux->der = nodoNuevo(padreAux, dato);
				equilibrar(padreAux, izquierdo, 1);
			}
		}
	}
}

void eliminar(nodoA* &raiz, int dato) {

}

int main() {
	cout << "Construcción de Árboles AVL \n";

	return 0;
}
