#include <iostream>
#include <stdlib.h>
#include <vector>
#include "texto.h"

using namespace std;

typedef struct ABBnodo {
	int nro;
	struct ABBnodo *izq, *der;
}*ABB;

int numNodosABB = 0; 
int numK = 0, k;     

struct nodoCola {
	ABB ptr;
	struct nodoCola *sgte;
};
struct cola {
	struct nodoCola *delante;
	struct nodoCola *atras;
};

void inicializaCola(struct cola &q)
{
	q.delante = NULL;
	q.atras = NULL;
}

void encola(struct cola &q, ABB n)
{
	struct nodoCola *p;
	p = new(struct nodoCola);
	p->ptr = n;
	p->sgte = NULL;
	if (q.delante == NULL)
		q.delante = p;
	else
		(q.atras)->sgte = p;
	q.atras = p;
}

ABB desencola(struct cola &q)
{
	struct nodoCola *p;
	p = q.delante;
	ABB n = p->ptr;
	q.delante = (q.delante)->sgte;
	delete(p);
	return n;
}


ABB crearNodo(int x)
{
	ABB nuevoNodo = new(struct ABBnodo);
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}


void insertar(ABB &arbol, int x)
{
	if (arbol == NULL)
	{
		arbol = crearNodo(x);
	}
	else if (arbol->nro==x)
	{	
		cout<<MAGENTA<<BLUE_COLOR<<"La clave ya existe..!"<<RESET_BACKGROUND<<RESET_COLOR<<"\n";
		return;
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x > arbol->nro)
		insertar(arbol->der, x);
}


void limpiarArbol(ABB &arbol)
{
    if (arbol != NULL)
    {
        limpiarArbol(arbol->izq);
        limpiarArbol(arbol->der);
        delete arbol;
        arbol = NULL;
    }
}

int altura(ABB arbol) {
    if (arbol == NULL)
        return 0;
    int hizq = altura(arbol->izq);
    int hder = altura(arbol->der);
    return std::max(hizq, hder) + 1;
}

std::vector<std::vector<texto>> crearMatriz(int n, int m) {
    std::vector<std::vector<texto>> matriz(n, std::vector<texto>(m, texto(' ')));
    return matriz;
}

void imprimirMatriz(const std::vector<std::vector<texto>>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 100; j < matriz[i].size(); j++) {
            std::cout << matriz[i][j];
        }
        std::cout << "\n\n";
    }
}

void rellenarMatriz(ABB arbol, std::vector<std::vector<texto>>& matriz, int fila, int col, int offset) {
    if (arbol == NULL)
        return;
    std::string s = std::to_string(arbol->nro);
    for (int i = 0; i < s.size(); i++) {
        matriz[fila][col + i].changeCaracter(MAGENTA_COLOR, s[i]);
    }
    if (arbol->izq != NULL) {
        matriz[fila + 1][col - offset / 2].changeCaracter(BLUE_COLOR, '/');
        rellenarMatriz(arbol->izq, matriz, fila + 2, col - offset, offset / 2);
    }
    if (arbol->der != NULL) {
        matriz[fila + 1][col + offset / 2].changeCaracter(BLUE_COLOR,'\\') ;
        rellenarMatriz(arbol->der, matriz, fila + 2, col + offset, offset / 2);
    }
}

void verArbol(ABB arbol) {
    int h = altura(arbol);
    std::vector<std::vector<texto>> matriz = crearMatriz(h*2, 300);
    rellenarMatriz(arbol, matriz, 0, 150, 20);
    imprimirMatriz(matriz);
}

void insertarNumerosRandom(ABB &arbol, int n)
{
    system("cls");
    for (int i = 0; i < n; ++i)
    {
        int num = rand() % 100;

		std::cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t     ..[  "<<MAGENTA_COLOR<<ITALIC<<"INSERTANDO "<<num<<RESET_COLOR<<"  ]..  \n";
		std::cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n\n";
        insertar(arbol, num);
		verArbol(arbol);
		std::cout<<"\n\n";
    }
    cout << MAGENTA<<RESET_COLOR<<"\n\t  Números aleatorios insertados..!" << RESET_BACKGROUND<<endl << endl;
}


void menuABB(ABB& arbol){
	int op , x;
	do{
		system("cls");

		cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t     ..[  "<<MAGENTA_COLOR<<ITALIC<<"ARBOL BINARIO DE BUSQUEDA"<<RESET_COLOR<<"  ]..  \n";
		cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout << RED_COLOR<<"\t [1] "<<RESET_COLOR<<CYAN_COLOR<<" Insertar elemento      arbol ABB   \n";
		cout << RED_COLOR<<"\t [2] "<<RESET_COLOR<<CYAN_COLOR<<" Mostrar arbol          arbol ABB   \n";
		cout << RED_COLOR<<"\t [3] "<<RESET_COLOR<<CYAN_COLOR<<" Limpiar arbol          arbol ABB   \n";
		cout << RED_COLOR<<"\t [4] "<<RESET_COLOR<<CYAN_COLOR<<" Insertar random        arbol ABB   \n";
		cout << RED_COLOR<<"\t [5] "<<RESET_COLOR<<CYAN_COLOR<<" Salir                  arbol ABB   \n";

		cout<<"\n\n"<<RESET_COLOR;
		cout << "\n\t Ingrese opcion : ";

		cin >> op;
		cout << endl;
		system("cls"); 

		switch (op)
		{
			case 1:
				cout << " Ingrese valor : ";  cin >> x;
				insertar(arbol, x);
				break;

			case 2: 

				std::cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
				std::cout <<RESET_COLOR<<"\n\t\t      ..[   "<<MAGENTA_COLOR<<ITALIC<<"ABB"<<RESET_COLOR<<"   ]..  \n";
				std::cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n\n\n";
				verArbol(arbol);
				system("pause");
				break;

			case 3:
				limpiarArbol(arbol);
				std::cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
				std::cout <<RESET_COLOR<<"\n\t\t      ..[   "<<MAGENTA_COLOR<<ITALIC<<"ARBOL LIMPIO"<<RESET_COLOR<<"   ]..  \n";
				std::cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n\n\n";
				system("pause");
				break;

			case 4:
				int cantidadNumeros;
				std::cout << MAGENTA_COLOR<<ITALIC<<"-> Ingrese"<<RESET_COLOR<< " la "<<MAGENTA<<BLUE_COLOR<<"cantidad de numeros aleatorios "<<RESET_BACKGROUND<<RESET_COLOR<<"a insertar: "<<MAGENTA_COLOR;
				cin >> cantidadNumeros;
				insertarNumerosRandom(arbol, cantidadNumeros);
				system("pause");
				break;
			
			case 5:
				break;

			default:
				std::cout <<CYAN<<MAGENTA_COLOR<< "OPCION DE INVALIDA" <<RESET_BACKGROUND<<RESET_COLOR<< std::endl;
				break;

		} 

	} while (op != 5);
}

