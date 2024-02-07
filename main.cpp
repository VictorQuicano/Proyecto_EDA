#include <bits/stdc++.h>    
#include "ArbolBinario.h"
#include "ArbolAVL.h"
#include "ArbolRB.h"
#include "KDTree.h"
#include "QuadTree.h"

#include "ColorsHead.h"

int main() {
    initBoard();
    int opcion;
    ArbolAVL arbolAVL;
    ABB arbolABB = NULL;
    RedBlackTree<int> arbolRB;
    KDTree<int> arbolKD(2);
    QTree *treeQ = new QTree();

    do {
		system("cls");

		cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t                 ..[  "<<MAGENTA_COLOR<<ITALIC<<"MENU"<<RESET_COLOR<<"  ]..  \n";
		cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout << RED_COLOR<<"\t [1]"<<RESET_COLOR<<CYAN_COLOR<<"  Arbol ABB  \n";
		cout << RED_COLOR<<"\t [2]"<<RESET_COLOR<<CYAN_COLOR<<"  Arbol AVL  \n";
		cout << RED_COLOR<<"\t [3]"<<RESET_COLOR<<CYAN_COLOR<<"  Arbol RB  \n";
		cout << RED_COLOR<<"\t [4]"<<RESET_COLOR<<CYAN_COLOR<<"  KD-TREE 2D  \n";
		cout << RED_COLOR<<"\t [5]"<<RESET_COLOR<<CYAN_COLOR<<"  Quad-Tree  \n";
        cout << RED_COLOR<<"\t [6]"<<RESET_COLOR<<CYAN_COLOR<<"  Salir  \n";

        cout<<"\n\n"<<RESET_COLOR;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                menuABB(arbolABB);
                break;
            case 2:
                menuAVL(arbolAVL);
                break;
            case 3:
                menuRedBlack(arbolRB);
                break;
            case 4:
                menuKD(arbolKD);
            case 5:
                menuQuad(*treeQ);

            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
        
        std::cout << std::endl;
    } while (opcion != 6);
    
    return 0;
}
