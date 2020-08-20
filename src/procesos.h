#ifndef PROCESOS_H_
#define PROCESOS_H_


const int COLUMNA=10;
const int FILA=10;


//Completa la matriz de minas y espacios en blanco.
void inicializarTablero(char tablero[FILA][COLUMNA]);


/*Muestra por pantalla al usuario, una secuencia de numeros
 * para que le sea más facil ubicarse en el tablero
 */
void margenHorizontal();


//Muestra el tablero.
void mostrarTablero(char tablero[FILA][COLUMNA]);


/*
 * Interactua con el usuario y llama a las otras funciones
 * para colocar las banderas o minas.
 */
void menu();


/*
 * Coloca una bandera donde crea que haya una mina.
 */
void bandera(char tablero[FILA][COLUMNA]);


/*
 * Pide la posicion que quiera el usuario
 */
void pedirPosicion(int ubicacion[2]);


/*
 * Devuelve si hay una mina en la posicion ingresada o no.
 */
bool hayMina(char tablero[FILA][COLUMNA], int posicion[2]);


/*
 * Analiza las filas alrededor de la posicion seleccionada
 * y pone en dicha posicion un numero representando la cantidad
 * de minas alrededor.
 */
void  analizarPeriferia(char tablero[FILA][COLUMNA], int posicion[2]);

/*
 * En caso que la posicion seleccionado no tenga minas
 * alrededor, tambien analizara a las contiguas de la posicion
 * revelada.
 *
 */
void descubrirPeriferia(char tablero[FILA][COLUMNA]);


//Devuelve si ganó la partida.
bool ganar(char matriz[FILA][COLUMNA]);

/*
 * Revela dónde estaban las minas.
 *
 */
void mostrarTableroFinal(char matriz[FILA][COLUMNA]);

#endif /* PROCESOS_H_ */
