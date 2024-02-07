#ifndef KDTREE_H
#define KDTREE_H

#pragma once

#include <bits/stdc++.h>
#include "texto.h"
using namespace std;
int pizarraSIZE = 127;
vector<vector<texto>> pizarra;
void llenarpizarra(){
    for(int i = 0; i < pizarraSIZE+2; i++){
        vector<texto> temp;
        for(int j = 0; j < pizarraSIZE+2; j++){
            temp.push_back(texto(WHITE,BLUE_COLOR,' '));
        }
        pizarra.push_back(temp);
    }
    for(int i=0;i<pizarraSIZE+2;i++){
        pizarra[0][i].changeCaracter(CYAN_COLOR,'-');
        pizarra[pizarraSIZE+1][i].changeCaracter(CYAN_COLOR,'-');
        pizarra[i][0].changeCaracter(CYAN_COLOR,'|');
        pizarra[i][pizarraSIZE+1].changeCaracter(CYAN_COLOR,'|');
    }
    pizarra[0][0].changeCaracter(CYAN_COLOR,218);
    pizarra[0][pizarraSIZE+1].changeCaracter(CYAN_COLOR,191);
    pizarra[pizarraSIZE+1][0].changeCaracter(CYAN_COLOR,192);
    pizarra[pizarraSIZE+1][pizarraSIZE+1].changeCaracter(CYAN_COLOR,217);
}
void printpizarra(){
    for(int i = pizarraSIZE+1; i>= 0 ; i--){
        for(int j = 0; j < pizarraSIZE+2; j++){
            cout << pizarra[i][j];
        }
        cout << endl;
    }
}
template <class T>
bool operator ==(const vector<T> &a, const vector<T> &b){
    for(auto i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}
template <class T>
class KDNode{
public:
    vector<T> point;
    int dimension;
    KDNode<T> *left, *right;
    //bool depth;
    
    KDNode(vector<T> point, int dimension){
        this->point = point;
        this->dimension = dimension;
        this->left = NULL;
        this->right = NULL;
        //depth = 0;
    }

    bool operator==(const KDNode<T> &other) const{
        for(auto i = 0; i < point.size(); i++){
            if(point[i] != other.point[i]){
                return false;
            }
        }
    }
    void printArbol(ostream &os){
        os << "\"";
        for(int i = 0; i < dimension; i++){
            os << point[i];
            if(i != dimension - 1){
                os << ", ";
            }
        }
        os << "\"";
    }
};

template <class T>
class KDTree{
public:
    KDNode<T> *root=nullptr;
    int dimension;
    int maxsize = 0;
    KDTree(){
        //this->root = nullptr;
        this->dimension = 0;
    }
    KDTree(int d){
        //this->root = nullptr;
        this->dimension = d;
    }
    void insert(int maxX, int minX, int maxY, int minY, vector<T> point, KDNode<T>*& node, int da){
    if (!node){
        node = new KDNode<T>(point, dimension);
        if (point[0] > maxsize){
            maxsize = point[0];
        }
        if (!da){
            if(minY>maxY){
                for (int i = maxY; i < minY; i++){
                    if (pizarra[i][point[0]].caracter != 'X')
                        pizarra[i][point[0]].changeCaracter('|');
                }
            }else {
                for (int i = minY; i < maxY; i++){
                    if (pizarra[i][point[0]].caracter != 'X')
                        pizarra[i][point[0]].changeCaracter('|');
                }
            }
        } else {
            if(minX>maxX){
                for (int i = maxX; i < minX; i++){
                    if (pizarra[point[1]][i].caracter != 'X')
                        pizarra[point[1]][i].changeCaracter('-');
                }    
            }else {
                for (int i = minX; i < maxX; i++){
                    if (pizarra[point[1]][i].caracter != 'X')
                        pizarra[point[1]][i].changeCaracter('-');
                }
            }
        }
        pizarra[point[1]][point[0]].changeCaracter( 'X');

        return;
    } else if (node->point == point){
        return;
    } else {
        if (!da){
            if (point[0] < node->point[0]){
                insert(node->point[0], minX, maxY, minY, point, node->left, (da +1)  % this->dimension);
            } else {
                insert(maxX, node->point[0] + 2, maxY, maxY, point, node->right, (da + 1) % this->dimension);
            }
        } else {
            if (point[1] < node->point[1]){
                insert(maxX, minX, node->point[1], minY, point, node->left, (da + 1) % this->dimension);
            } else {
                insert(maxX, minX, maxY, node->point[1] + 1,point, node->right, (da + 1) % this->dimension);
            }
        }
    }
}

    KDNode<T>* find(vector<T> point, KDNode<T> *node, int da){
        if(!node){
            return nullptr;
        }else if(node->point == point){
            return node;
        }else if(point[da] < node->point[da]){
            return find(point, node->left, (da + 1) % this->dimension);
        }else return find(point, node->right, (da + 1) % this->dimension);
    }
    void printArbol(ostream &os, KDNode<T> *node){
        if(!node){
            return;
        }
        if(node->left){
            node->printArbol(os);
            os<<" -> ";
            node->left->printArbol(os);
            os<<endl;
        }
        if(node->right){
            node->printArbol(os);
            os<<" -> ";
            node->right->printArbol(os);
            os<<endl;
        }
        printArbol(os, node->left);
        printArbol(os, node->right);
    }
public:
    void insert(vector<T> point){
        insert(pizarraSIZE+1,1,pizarraSIZE+1,1,point, root, 0);
        cout<<endl;
        printpizarra();
        system("pause");

    }
    KDNode<T>* find(vector<T> point){
        return find(point, root, 0);
    }
    void printArbol(ostream &os){
        os<<"digraph G {"<<endl;
        printArbol(os, root);
        os<<"}\n";
    }
};
void insertarRandoms(int num, KDTree<int> &a){
    srand(time(NULL));
    for(int i = 0; i < num; i++){
        int x = rand() % pizarraSIZE + 1;
        int y = rand() % pizarraSIZE + 1;
        std::cout<<CYAN_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t..[  "<<GREEN<<ITALIC<<"INSERTANDO PUNTO "<<CYAN<<x<<", "<<y<<RESET_BACKGROUND<<RESET_COLOR<<"  ]..  \n";
		std::cout<<"\n"<<CYAN_COLOR"==============================================================================="<<"\n\n"<<RESET_COLOR;
        a.insert({x, y});
        printpizarra();
    }

}
void menuKD(KDTree<int> &arbol) {
    llenarpizarra();
    int opcion = 0;
    int elementoX = 0;
    int elementoY = 0;
    char basurero=' ';

    do {
		system("cls");
		std::cout<<CYAN_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t..[  "<<GREEN_COLOR<<ITALIC<<"KDTREE 2D"<<RESET_COLOR<<"  ]..  \n";
        cout<<CYAN_COLOR<<"\n"<<"==============================================================================="<<"\n"<<RESET_COLOR;
        cout << CYAN_COLOR<<ITALIC<<"\t [1]"<<RESET_COLOR<<"  Insertar elemento      KD-Tree   \n";
		cout << CYAN_COLOR<<ITALIC<<"\t [2]"<<RESET_COLOR<<"  Mostrar arbol          KD-Tree   \n";
		cout << CYAN_COLOR<<ITALIC<<"\t [3]"<<RESET_COLOR<<"  Limpiar arbol          KD-Tree   \n";
		cout << CYAN_COLOR<<ITALIC<<"\t [4]"<<RESET_COLOR<<"  Insertar random        KD-Tree   \n";    
		cout << CYAN_COLOR<<ITALIC<<"\t [5]"<<RESET_COLOR<<"  Salir                  KD-Tree   \n";    
  
        std::cout << "\n\t Ingrese opcion : ";
        std::cin >> opcion;
        system("cls"); 

        switch (opcion) {
            case 1:
                std::cout << CYAN_COLOR<<ITALIC<<" -> Ingrese"<<RESET_COLOR<< " el elemento a insertar: ";
                std::cin >> elementoX>>basurero>>elementoY;
                arbol.insert({elementoX, elementoY});
                std::cout<<CYAN_COLOR<<"\n"<<"==============================================================================="<<"\n";
		        cout <<RESET_COLOR<<"\n\t\t..[  "<<GREEN<<ITALIC<<"INSERTADO PUNTO "<<CYAN<<elementoX<<", "<<elementoY<<RESET_BACKGROUND<<RESET_COLOR<<"  ]..  \n";
		        std::cout<<"\n"<<CYAN_COLOR"==============================================================================="<<"\n\n"<<RESET_COLOR;
                system("pause");
                break;
            case 2:
                std::cout<<"\n"<<CYAN_COLOR<<"==============================================================================="<<"\n";
                std::cout<<"\n"<<GREEN_COLOR<<ITALIC<<"                                   KDTREE                                   "<<"\n";
                std::cout<<"\n"<<CYAN_COLOR<<"==============================================================================="<<"\n\n\n";
                system("color 05"); 
                if (arbol.root == nullptr) {
                    std::cout <<GREEN<<RESET_COLOR<< "EL ARBOL ESTA VACIO" <<RESET_BACKGROUND<<RESET_COLOR<< std::endl;
                } else {
                    printpizarra();
                }
                system("pause");
                break;
            case 3:
                std::cout<<"\n"<<CYAN_COLOR<<"==============================================================================="<<"\n";
                std::cout<<"\n"<<GREEN_COLOR<<ITALIC<<"                                   ARBOL LIMPIO                                "<<"\n";
                std::cout<<"\n"<<CYAN_COLOR<<"==============================================================================="<<"\n";
                llenarpizarra();
                system("pause");
                break;
            case 4:
                int cantidadNumeros;
                std::cout << CYAN_COLOR<<ITALIC<<"-> Ingrese"<<RESET_COLOR<< " la "<<CYAN<<GREEN_COLOR<<"cantidad de numeros aleatorios"<<RESET_BACKGROUND<<RESET_COLOR<<" a insertar: "<<GREEN_COLOR;
                std::cin >> cantidadNumeros;
                cout<<RESET_COLOR;
                insertarRandoms(cantidadNumeros,arbol);
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

#endif