#include <iostream>
#include <algorithm>
#include <vector>
#include "texto.h"

using namespace std;

class NodoAVL {
public:
    int key;
    NodoAVL* left;
    NodoAVL* right;
    int altura;

    NodoAVL(int val) : key(val), left(nullptr), right(nullptr), altura(1) {}
};

class ArbolAVL {
private:
    NodoAVL* root;

public:
    ArbolAVL() : root(nullptr) {}

    NodoAVL* obtenerRoot() {
        return root;
    }

    void clearAll() {
        root = nullptr;
    }

    void insertar(int key) {
        root = insertarAVL(root, key);
    }

    NodoAVL* insertarAVL(NodoAVL* nodoActual, int key) {
        if (nodoActual == nullptr) {
            return new NodoAVL(key);
        }
        if(nodoActual->key == key){
            cout<<RED<<GREEN_COLOR<<"El elemento ya existe"<<RESET_COLOR<<RESET_BACKGROUND<<endl;
            return nodoActual;
        }
        if (key < nodoActual->key) {
            nodoActual->left = insertarAVL(nodoActual->left, key);
        } else if (key > nodoActual->key) {
            nodoActual->right = insertarAVL(nodoActual->right, key);
        } else {
            return nodoActual;
        }

        nodoActual->altura = 1 + std::max(getAltura(nodoActual->left), getAltura(nodoActual->right));

        int fe = getFactorEquilibrio(nodoActual);

        if (fe > 1 && key < nodoActual->left->key) {
            cout<<"Rotacion "<<GREEN_COLOR<<"SIMPLE"<<RESET_COLOR<<" a la "<<RED<<"DERECHA"<<RESET_BACKGROUND<<"\n\n"<<endl;
            return rightRotate(nodoActual);
        }

        if (fe < -1 && key > nodoActual->right->key) {
            cout<<"Rotacion "<<GREEN_COLOR<<"SIMPLE"<<RESET_COLOR<<" a la "<<CYAN<<"IZQUIERDA"<<RESET_BACKGROUND<<"\n\n"<<endl;
            return leftRotate(nodoActual);
        }

        if (fe > 1 && key > nodoActual->left->key) {
            cout<<"Rotacion "<<MAGENTA_COLOR<<"DOBLE"<<RESET_COLOR<<" a la "<<RED<<"DERECHA"<<RESET_BACKGROUND<<"\n\n"<<endl;
            nodoActual->left = leftRotate(nodoActual->left);
            return rightRotate(nodoActual);
        }

        if (fe < -1 && key < nodoActual->right->key) {
            cout<<"Rotacion "<<MAGENTA_COLOR<<"DOBLE"<<RESET_COLOR<<" a la "<<CYAN<<"IZQUIERDA"<<RESET_BACKGROUND<<"\n\n"<<endl;
            nodoActual->right = rightRotate(nodoActual->right);
            return leftRotate(nodoActual);
        }

        return nodoActual;
    }

    void buscar(int elemento) {
        if (BuscaEnAVL(root, elemento)) {
            std::cout << "Existe" << std::endl;
        } else {
            std::cout << "No Existe" << std::endl;
        }
    }

    bool BuscaEnAVL(NodoAVL* nodoActual, int elemento) {
        if (nodoActual == nullptr) {
            return false;
        } else if (elemento == nodoActual->key) {
            return true;
        } else if (elemento < nodoActual->key) {
            return BuscaEnAVL(nodoActual->left, elemento);
        } else {
            return BuscaEnAVL(nodoActual->right, elemento);
        }
    }

    void eliminar(int key) {
        root = eliminarAVL(root, key);
    }

    NodoAVL* eliminarAVL(NodoAVL* nodoActual, int key) {
        if (nodoActual == nullptr)
            return nodoActual;

        if (key < nodoActual->key) {
            nodoActual->left = eliminarAVL(nodoActual->left, key);
        } else if (key > nodoActual->key) {
            nodoActual->right = eliminarAVL(nodoActual->right, key);
        } else {
            if ((nodoActual->left == nullptr) || (nodoActual->right == nullptr)) {
                NodoAVL* temp = nullptr;
                if (temp == nodoActual->left) {
                    temp = nodoActual->right;
                } else {
                    temp = nodoActual->left;
                }

                if (temp == nullptr) {
                    nodoActual = nullptr;
                } else {
                    nodoActual = temp;
                }
            } else {
                NodoAVL* temp = getNodoConValorMaximo(nodoActual->left);
                nodoActual->key = temp->key;
                nodoActual->left = eliminarAVL(nodoActual->left, temp->key);
            }
        }

        if (nodoActual == nullptr)
            return nodoActual;

        nodoActual->altura = std::max(getAltura(nodoActual->left), getAltura(nodoActual->right)) + 1;

        int fe = getFactorEquilibrio(nodoActual);

        if (fe > 1 && getFactorEquilibrio(nodoActual->left) >= 0) {
            return rightRotate(nodoActual);
        }

        if (fe < -1 && getFactorEquilibrio(nodoActual->right) <= 0) {
            return leftRotate(nodoActual);
        }

        if (fe > 1 && getFactorEquilibrio(nodoActual->left) < 0) {
            nodoActual->left = leftRotate(nodoActual->left);
            return rightRotate(nodoActual);
        }

        if (fe < -1 && getFactorEquilibrio(nodoActual->right) > 0) {
            nodoActual->right = rightRotate(nodoActual->right);
            return leftRotate(nodoActual);
        }

        return nodoActual;
    }

    NodoAVL* rightRotate(NodoAVL* nodoActual) {
        NodoAVL* nuevaRaiz = nodoActual->left;
        NodoAVL* temp = nuevaRaiz->right;

        nuevaRaiz->right = nodoActual;
        nodoActual->left = temp;

        nodoActual->altura = std::max(getAltura(nodoActual->left), getAltura(nodoActual->right)) + 1;
        nuevaRaiz->altura = std::max(getAltura(nuevaRaiz->left), getAltura(nuevaRaiz->right)) + 1;

        return nuevaRaiz;
    }

    NodoAVL* leftRotate(NodoAVL* nodoActual) {
        NodoAVL* nuevaRaiz = nodoActual->right;
        NodoAVL* temp = nuevaRaiz->left;

        nuevaRaiz->left = nodoActual;
        nodoActual->right = temp;

        nodoActual->altura = std::max(getAltura(nodoActual->left), getAltura(nodoActual->right)) + 1;
        nuevaRaiz->altura = std::max(getAltura(nuevaRaiz->left), getAltura(nuevaRaiz->right)) + 1;

        return nuevaRaiz;
    }

    std::vector<std::vector<texto>> crearMatriz(int n, int m) {
        std::vector<std::vector<texto>> matriz(n, std::vector<texto>(m, texto(BLUE_COLOR,' ')));
        return matriz;
    }

    // Esta función imprime una matriz de nxm en la consola
    void imprimirMatriz(const std::vector<std::vector<texto>>& matriz) {
        for (int i = 0; i < matriz.size(); i++) {
            for (int j = 0; j < matriz[i].size(); j++) {
                std::cout << matriz[i][j];
            }
            std::cout << "\n\n";
        }
    }

    void rellenarMatriz(NodoAVL* nodo, std::vector<std::vector<texto>>& matriz, int fila, int col, int offset) {
        if (nodo == nullptr)
            return;
        std::string s = std::to_string(nodo->key);
        for (std::string::size_type i = 0; i < s.size(); i++) {
            matriz[fila][col + i] = s[i];
        }
        if (nodo->left != NULL) {
            // Colocamos el carácter "/" para unir el nodo con su hijo izquierdo
            matriz[fila + 1][col - offset / 2].changeCaracter(BLACK_COLOR,'/') ;
            // Llamamos recursivamente a la función para el subárbol izquierdo
            rellenarMatriz(nodo->left, matriz, fila + 2, col - offset, offset / 2);
        }
        if (nodo->right != NULL) {
            // Colocamos el carácter "\" para unir el nodo con su hijo derecho
            matriz[fila + 1][col + offset / 2].changeCaracter(BLACK_COLOR, '\\');
            // Llamamos recursivamente a la función para el subárbol derecho
            rellenarMatriz(nodo->right, matriz, fila + 2, col + offset, offset / 2);
        }
    }

    int altura(NodoAVL* nodo) {
        if (nodo == nullptr)
            return 0;
        int hizq = altura(nodo->left);
        int hder = altura(nodo->right);
        return std::max(hizq, hder) + 1;
    }

    void mostrarArbolAVL() {
        int h = altura(root);
        std::vector<std::vector<texto>> matriz = crearMatriz(h*2, 100);
        rellenarMatriz(root, matriz, 0, 50, 25);
        imprimirMatriz(matriz);
    }


    void limpiarArbol(NodoAVL* nodoActual) {
        if (nodoActual != nullptr) {
            limpiarArbol(nodoActual->left);
            limpiarArbol(nodoActual->right);
            delete nodoActual;
            nodoActual = nullptr;
        }
    }

private:
    int getAltura(NodoAVL* nodoActual) {
        if (nodoActual == nullptr) {
            return 0;
        }

        return nodoActual->altura;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getFactorEquilibrio(NodoAVL* nodoActual) {
        if (nodoActual == nullptr) {
            return 0;
        }

        return getAltura(nodoActual->left) - getAltura(nodoActual->right);
    }

    NodoAVL* getNodoConValorMaximo(NodoAVL* node) {
        NodoAVL* current = node;

        while (current->right != nullptr) {
            current = current->right;
        }

        return current;
    }
};

void insertarNumerosRandom(ArbolAVL &arbol, int n) {
    srand(time(NULL));
    int numero ;
    for (int i = 0; i < n; i++) {
        numero = 1 + rand() % (100);
    	std::cout<<GREEN_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t..[  "<<YELLOW_COLOR<<ITALIC<<"INSERTANDO "<<GREEN<<numero<<RESET_BACKGROUND<<RESET_COLOR<<"  ]..  \n";
		std::cout<<"\n"<<GREEN_COLOR"==============================================================================="<<"\n\n"<<RESET_COLOR;
        arbol.insertar(numero);
        arbol.mostrarArbolAVL();
        std::cout<<"\n\n";
    }

    std::cout << GREEN_COLOR<<"\n\t  Numeros aleatorios insertados..!" << RESET_COLOR<< endl << std::endl;

}

void menuAVL(ArbolAVL &arbol) {
    int opcion = 0;
    int elemento = 0;

    do {
		system("cls");
		std::cout<<GREEN_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t..[  "<<YELLOW_COLOR<<ITALIC<<"ARBOL ADELSON VELSKII Y LANDIS"<<RESET_COLOR<<"  ]..  \n";
        cout<<GREEN_COLOR<<"\n"<<"==============================================================================="<<"\n"<<RESET_COLOR;
        cout << GREEN_COLOR<<ITALIC<<"\t [1]"<<RESET_COLOR<<"  Insertar elemento      arbol AVL   \n";
		cout << GREEN_COLOR<<ITALIC<<"\t [2]"<<RESET_COLOR<<"  Mostrar arbol          arbol AVL   \n";
		cout << GREEN_COLOR<<ITALIC<<"\t [3]"<<RESET_COLOR<<"  Limpiar arbol          arbol AVL   \n";
		cout << GREEN_COLOR<<ITALIC<<"\t [4]"<<RESET_COLOR<<"  Insertar random        arbol AVL   \n";    
		cout << GREEN_COLOR<<ITALIC<<"\t [5]"<<RESET_COLOR<<"  Salir                  arbol AVL   \n";    
  
        std::cout << "\n\t Ingrese opcion : ";
        std::cin >> opcion;
        system("cls"); 

        switch (opcion) {
            case 1:
                std::cout << GREEN_COLOR<<ITALIC<<" -> Ingrese"<<RESET_COLOR<< " el elemento a insertar: ";
                std::cin >> elemento;
                arbol.insertar(elemento);
                break;
            case 2:
                std::cout<<"\n"<<GREEN_COLOR<<"==============================================================================="<<"\n";
                std::cout<<"\n"<<YELLOW_COLOR<<ITALIC<<"                                   ARBOL AVL                                   "<<"\n";
                std::cout<<"\n"<<GREEN_COLOR<<"==============================================================================="<<"\n\n\n";
                system("color 05"); 
                if (arbol.obtenerRoot() == nullptr) {
                    std::cout <<ORANGE<<RESET_COLOR<< "EL ARBOL ESTA VACIO" <<RESET_BACKGROUND<<RESET_COLOR<< std::endl;
                } else {
                    arbol.mostrarArbolAVL();
                }
                system("pause");
                break;
            case 3:
                arbol.clearAll();
                std::cout<<"\n"<<GREEN_COLOR<<"==============================================================================="<<"\n";
                std::cout<<"\n"<<YELLOW_COLOR<<ITALIC<<"                                   ARBOL LIMPIO                                "<<"\n";
                std::cout<<"\n"<<GREEN_COLOR<<"==============================================================================="<<"\n";
                system("pause");
                break;
            case 4:
                int cantidadNumeros;
                std::cout << GREEN_COLOR<<ITALIC<<"-> Ingrese"<<RESET_COLOR<< " la "<<GREEN<<YELLOW_COLOR<<"cantidad de numeros aleatorios "<<RESET_BACKGROUND<<RESET_COLOR<<"a insertar: "<<GREEN_COLOR;
                std::cin >> cantidadNumeros;
                cout<<RESET_COLOR;
                insertarNumerosRandom(arbol, cantidadNumeros);
                system("pause");
                break;

            case 5:
                break;
            
            default:
                std::cout <<ORANGE<<RESET_COLOR<< "OPCION DE INVALIDA" <<RESET_BACKGROUND<<RESET_COLOR<< std::endl;
                break;
        }
        
    } while (opcion != 5);
}

/* 
int main() {
    ArbolAVL arbol;

    menuAVL(arbol);
    return 0;
}
*/