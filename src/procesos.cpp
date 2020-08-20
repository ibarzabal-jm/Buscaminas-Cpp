#include <iostream>
#include <stdlib.h>
#include "procesos.h"

using namespace std;



void inicializarTablero(char tablero[FILA][COLUMNA]){
	for (int i=0; i<FILA; i++){
		for (int j=0; j<COLUMNA; j++){
			tablero[i][j]='-';
		}
	}

	for(int i=0; i<16; i++){
		bool colocado=false;
		do{
			int a=rand()%10;
			int b=rand()%10;
			if(tablero[a][b]=='-'){
				colocado=true;
				tablero[a][b]='*';
			}
		}while(colocado==false);
	}
}



void margenHorizontal(){
	for(int j=0; j<COLUMNA;j++){
				cout<<' '<<j<<' ';
			}
			cout<<endl;
}



void mostrarTablero(char tablero[FILA][COLUMNA]){

	margenHorizontal();
	for (int i=0; i<FILA; i++){
				for (int j=0; j<COLUMNA; j++){

					switch(tablero[i][j]){

					case '-': cout<<"["<<"-"<< "]";
							break;

					case 'F': cout<<"["<<"F"<< "]";
							break;

					case 'E': cout<<"["<<"F"<< "]";
							break;

					case '*': cout<<"["<<"-"<< "]";
							break;

					default: cout<<"["<<tablero[i][j]<< "]";
					}

				}
				cout<<' '<<i<<endl;
			}
	margenHorizontal();
}



void menu(){
	char tablero[FILA][COLUMNA];
	inicializarTablero(tablero);
	mostrarTablero(tablero);
	unsigned int jugar;
	bool perder;
	perder=false;
	do{
		int opcion;
		bool validar;
		validar=true;
		do{
			cout<<endl;
			cout<<"¿Que accion quiere realizar?"<<endl;
			cout<<" '1' para Arriesgar"<<endl;
			cout<<" '2' para colocar Bandera"<<endl;
			cout<<" '3' para Salir"<<endl;
			cin>>opcion;
			cout<<endl;
			switch(opcion){

				case 1: {
						int ubicacion[2];
						pedirPosicion(ubicacion);
						if(hayMina(tablero, ubicacion)==true){
							perder=true;
						}else{
							analizarPeriferia(tablero, ubicacion);
							descubrirPeriferia(tablero);
						}
				}
						break;

				case 2: bandera(tablero);
						break;

				case 3: perder=true;
						break;

				default: {
						cout<<"Opcion invalida"<<endl;
						validar=false;
				}

			}
		}while(!validar);
		mostrarTablero(tablero);
		cout<<endl;
	}while(!perder && !ganar(tablero));
	if(perder==true){
		cout<<endl;
		mostrarTableroFinal(tablero);
		cout<<endl;
		cout<<"---->>>>!!!!!!!!!! PERDISTEEEEE !!!!!!<<<-----"<<endl;
		cout<<endl;
	}else{
		cout<<endl;
		mostrarTableroFinal(tablero);
		cout<<endl;
		cout<<"GANASTE"<<endl;
		cout<<endl;
	}

	cout<<"---------¿Desea jugar devuelta?----------------"<<endl;
	cout<<"Presione 1 para Seguir jugando, 0 para NO seguir jugando";
	cin>>jugar;
	if(jugar==1){
		menu();
	}
}



void pedirPosicion(int ubicacion[2]){

	cout<<"Ingrese la posicion"<<endl;
	cout<<"Ingrese la fila"<<endl;
	cin>>ubicacion[0];
	cout<<endl;
	cout<<"Ingrese la columna"<<endl;
	cin>>ubicacion[1];
	cout<<endl;

}

bool hayMina(char tablero[FILA][COLUMNA], int posicion[2]){
	int filaelegida=posicion[0];
	int columnaelegida=posicion[1];

	if( tablero[filaelegida][columnaelegida]=='*' || tablero[filaelegida][columnaelegida]=='F' )
			return true;


	return false;
}



void bandera(char tablero[FILA][COLUMNA]){

	int posicion[2];
	pedirPosicion(posicion);
	int filaelegida=posicion[0];
	int columnaelegida=posicion[1];

	switch(tablero[filaelegida][columnaelegida]){

	case '*': tablero[filaelegida][columnaelegida]='F';
		break;

	case 'F': tablero[filaelegida][columnaelegida]='*';
		break;
	case 'E': tablero[filaelegida][columnaelegida]='-';
		break;

	default: tablero[filaelegida][columnaelegida]='E';
	}

}



void analizarPeriferia(char tablero[FILA][COLUMNA], int posicion[2]){
	int filaelegida= posicion[0];
	int columnaelegida= posicion[1];
	int cantidadminas=0;

	//Analisis Vertical Derecho (columna +1)
	for(int i=-1;i<2; i++){
		if(columnaelegida+1<COLUMNA && filaelegida+i<FILA && filaelegida+i>=0){
			if(tablero[filaelegida+i][columnaelegida+1]=='*' || tablero[filaelegida+i][columnaelegida+1]=='F'){
			cantidadminas++;
			}
		}
	}

	//Analisis vertical izquierdo (columna -1)

	for(int i=-1;i<2; i++){
		if(columnaelegida-1>=0 && filaelegida+i<FILA && filaelegida+i>=0){
			if(tablero[filaelegida+i][columnaelegida-1]=='*' || tablero[filaelegida+i][columnaelegida-1]=='F'){
			cantidadminas++;
			}
		}
	}

	//Analisis Abajo//

	if((filaelegida+1<FILA) &&(tablero[filaelegida+1][columnaelegida]=='*' || tablero[filaelegida+1][columnaelegida]=='F')){
		cantidadminas++;
	}

	//Analisis Arriba//

	if( (filaelegida-1>=0) && (tablero[filaelegida-1][columnaelegida]=='*' || tablero[filaelegida-1][columnaelegida]=='F') ){
		cantidadminas++;
	}

	tablero[filaelegida][columnaelegida]=(48 +cantidadminas);
	//El 0 en Ascii se escribe como 48
}

void descubrirPeriferia(char tablero[FILA][COLUMNA]){

	for(int filaelegida=0; filaelegida<FILA; filaelegida++){
		for(int columnaelegida=0; columnaelegida<COLUMNA; columnaelegida++){
			if(tablero[filaelegida][columnaelegida]==48){
				int nuevaposicion[2];
				//Arriba
				nuevaposicion[0]=(filaelegida-1);
				nuevaposicion[1]=columnaelegida;
				if(nuevaposicion[0]>=0){
					analizarPeriferia(tablero, nuevaposicion);
				}

				//Abajo
				nuevaposicion[0]=(filaelegida+1);
				nuevaposicion[1]=columnaelegida;
				if(nuevaposicion[0]<FILA){
					analizarPeriferia(tablero, nuevaposicion);
				}

				//Columna derecha
				nuevaposicion[1]=columnaelegida+1;
				for(int i=-1; i<2; i++){
					nuevaposicion[0]=(filaelegida+i);
					if(nuevaposicion[0]>=0 && nuevaposicion[0]<FILA && nuevaposicion[1]<COLUMNA){
						analizarPeriferia(tablero, nuevaposicion);
					}
				}

				//Columna Izquierda
				nuevaposicion[1]=columnaelegida-1;
				for(int i=-1; i<2; i++){
					nuevaposicion[0]=(filaelegida+i);
					if(nuevaposicion[0]>=0 && nuevaposicion[0]<FILA && nuevaposicion[1]>=0){
						analizarPeriferia(tablero, nuevaposicion);
					}
				}



			}
		}
	}
}

bool ganar(char tablero[FILA][COLUMNA] ){

	int cantidadBanderasCorrectas=0;

	for (int i=0; i<FILA; i++){
			for (int j=0; j<COLUMNA; j++){
				if(tablero[i][j]=='F'){
					cantidadBanderasCorrectas++;
				}
				if(tablero[i][j]=='E' || tablero[i][j]=='-'){
					return false;
				}

			}
	}

	if(cantidadBanderasCorrectas==15){
		return true;
	}

	return true;
}




void mostrarTableroFinal(char tablero[FILA][COLUMNA]){

	margenHorizontal();
	for (int i=0; i<FILA; i++){
			for (int j=0; j<COLUMNA; j++){
						cout<<'['<<tablero[i][j]<< ']';
					}
					cout<<' '<<i<<endl;
			}
	margenHorizontal();

}
