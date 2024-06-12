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

int alturaArbol(nodoA *raiz) {
	if (raiz == NULL)
		return 0;

	int izqAltura = alturaArbol(raiz->izq);
	int derAltura = alturaArbol(raiz->der);
	
	int mayor;
	if (izqAltura > derAltura)
		mayor = izqAltura;
	else
		mayor = derAltura;

	return mayor + 1;
	
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

void equilibrar(nodoA* &raiz, nodoA *ultNodo, int rama, bool nuevo) {
	bool salir = 0;

	while (ultNodo && !salir) {
		if (nuevo) {
			if (rama == izquierdo)
				ultNodo->fe -= 1;
			else
				ultNodo->fe += 1;
		}
		else {
			if (rama == izquierdo)
				ultNodo->fe += 1;
			else
				ultNodo->fe -= 1;
		}

		if (ultNodo->fe == 0)
			salir = 1;
		else {
			if (ultNodo->fe == -2) {
				if (ultNodo->izq->fe == 1)
					rotaDD(raiz, ultNodo);
				else
					rotaSD(raiz, ultNodo);

				salir = 1;
			}

			else {
				if (ultNodo->fe == 2) {
					if (ultNodo->der->fe == -1)
						rotaDI(raiz, ultNodo);
					else
						rotaSI(raiz, ultNodo);
					salir = 1;
				}
			}
		}

		if (!salir) {
			nodoA *pad = ultNodo->padre;
			if (pad) {
				if (pad->izq == ultNodo)
					rama = izquierdo;
				else
					rama = derecho;
			}
			ultNodo = pad;
		}
	}
}

void insertarDato(nodoA *&raiz, int elemento){
	nodoA *nuevo;
	nodoA *actual = raiz;
	nodoA *anterior = NULL;

	if(buscarDato(raiz, elemento, actual, anterior))
		cout<<"Elemento duplicado\n";
	else{
		nuevo = new nodoA;
		nuevo->valor = elemento;
		nuevo->izq = NULL;
		nuevo->der = NULL;
		nuevo->padre = NULL;
		nuevo->fe = 0;

		if(anterior == NULL)
			raiz = nuevo;
		else{
			nuevo->padre = anterior;
			if(anterior->valor > elemento){
				anterior->izq = nuevo;
				equilibrar(raiz, anterior, izquierdo, 1);
			}
			else{
				anterior->der = nuevo;
				equilibrar(raiz, anterior, derecho, 1);
			}
		}
	}
}

bool esHoja(nodoA *nod) {
	bool hoja;
	if (nod->izq == NULL && nod->der == NULL)
		hoja = 1;
	else
		hoja = 0;

	return hoja;
}

int calcularFE(nodoA *nod) {
	int fe;
	if (nod == NULL)
		fe = 0;
	else
		fe = alturaArbol(nod->der) - alturaArbol(nod->izq);

	return fe;
}

void eliminar(nodoA *&raiz, int dato) {
    nodoA *actual = raiz;
    nodoA *padreAux = NULL;
    nodoA *descendiente = NULL;
    nodoA *ultimoNodo = NULL;

    bool termina = 0;

    while (!termina && actual != NULL) {
        if (dato == actual->valor) {
            ultimoNodo = actual->padre;

            if (esHoja(actual)) {
                if (padreAux != NULL) {
                    if (padreAux->der == actual)
                        padreAux->der = NULL;
                    else if (padreAux->izq == actual)
                        padreAux->izq = NULL;
                }

                delete actual;
                actual = NULL;
                termina = 1;
            }
            else {
                padreAux = actual;
                if (actual->der == NULL) {
                    descendiente = actual->izq;
                    while (descendiente->izq != NULL) {
                        padreAux = descendiente;
                        descendiente = descendiente->izq;
                    }
                }
                else {
                    descendiente = actual->der;
                    while (descendiente->der != NULL) {
                        padreAux = descendiente;
                        descendiente = descendiente->der;
                    }
                }

                int aux = actual->valor;
                actual->valor = descendiente->valor;
                descendiente->valor = aux;
                actual = descendiente;
            }
        }
        else {
            padreAux = actual;
            if (dato > actual->valor)
                actual = actual->der;
            else if (dato < actual->valor)
                actual = actual->izq;
        }
    }

    if (ultimoNodo) {
    	int derizq;
    	if (ultimoNodo->izq == actual)
    		derizq = izquierdo;
    	else
    		derizq = derecho;

    	equilibrar(raiz, ultimoNodo, derizq, 0);
    }
}

void imprimirArbol(nodoA *arbol, int aux) {
	if (arbol != NULL) {
		imprimirArbol(arbol->der, aux + 1);
		for (int i = 0; i < aux; i++)
			cout << "\t";
		cout << arbol->valor << "\n";
		imprimirArbol(arbol->izq, aux + 1);
	}
}

int main() {
	nodoA *raiz = NULL;

	cout << "Construcción de Árboles AVL \n";

	bool band = 1;
	while (band) {
		int datoL;
		cout << "Ingresar dato ";
		cin >> datoL;

		if (datoL > -1)
			insertarDato(raiz, datoL);
		else
			band = 0;
	}

	imprimirArbol(raiz, 0);

	int datoE;
	cout << "Ingresar el dato a eliminar ";
	cin >> datoE;
	eliminar(raiz, datoE);

	imprimirArbol(raiz, 0);

	return 0;
}
