#ifndef TEXTO_H
#define TEXTO_H
//******************************************//
//**************TEXTO CLASS*****************//
//******************************************//

//Esta clase se encarga de imprimir un caracter con un color y un fondo
//El problema es que se asigna por caracter
#include <bits/stdc++.h> 
#include "ColorsHead.h"
using namespace std;
class texto{
    public:
    string color=RESET_COLOR;
    string background=RESET_BACKGROUND;
    char caracter= ' ';
        texto(){
            this->color = RESET_COLOR;
            this->background = RESET_BACKGROUND;
            this->caracter = ' ';
        }        
        texto(char caracter){
            this->caracter = caracter;
        }
        texto(string color, char caracter){
            this->color = color;
            this->caracter = caracter;
        }
        texto(string bag, string color, char caracter){
            this->background = bag;
            this->color = color;
            this->caracter = caracter;
        }
        
        void changeColor(string bg,string color){
            this->background = bg;
            this->color = color;
        }
        void changeColor(string color){
            this->color = color;
        }
        void changeBackground(string bg){
            this->background = bg;
        }

        void changeCaracter(char caracter){
            this->caracter = caracter;
        }
        void changeCaracter(string color, char caracter){
            this->color = color;
            this->caracter = caracter;
        }
        void changeCaracter(string bag, string color, char caracter){
            this->background = bag;
            this->color = color;
            this->caracter = caracter;
        }
        
        friend ostream& operator<<(ostream& os, const texto& impre);
        friend istream& operator>>(istream& is, texto& impre);
};
ostream& operator<<(ostream& os, const texto& impre){
    os << impre.background<< impre.color << impre.caracter << RESET_COLOR;
    return os;
};
istream& operator>>(istream& is, texto& impre){
    impre.color = RESET_COLOR;
    is >>impre.caracter;
    return is;
};


#endif