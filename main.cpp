#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <climits>

//Funciones
#include "fuera.h"
#include "inicioModificado.h"
#include "incrementoMomento.h"
#include "progreso.h"
#include "distancia.h"

using namespace std;

int main(int argc, char **argv)
{

	//Tener en cuenta las colisiones?
	bool colisiones = false;
	
	/*
	 * Parametros modificables
	 */

	//Pasos de tiempo
	int t = 1000;
	//Diferencial de tiempo
	double dt = 1e-13;
	//Tamaño del cubo, temperatura, masa.
	double lext = 1e-8, lin = lext / 2.0;;
	double  Text = 1, Tin = 30, m = 222.0 * 1.660538e-27, momento = 0;
	//Numero de particulas
	int n = 4000;
	//Radio del atomo
	double radioH = 120e-12;
	//Diferencial de camino para mover la particula y comprobar si se choca con otra
	double dr = radioH;

	/*
	 *Fin de parametros modificables
	 */

	lin = lin * 0.5; // esto es para centrarlo pero tendra la longitud de antes
	double l = lext;
	//Numero de choques
	int choque = 0;
	bool chocado = false;
	//Variables de las coordenadas esfericas de los caminantes
	double teta, phi, minimo = 0, maximo = 2 * 3.14159265;
	// semilla
	srand(time(NULL));
	//Componentes de la velocidad y la posicion
	double x[n], y[n], z[n], vx[n], vy[n], vz[n], v[n], rr[n];
	//Pasos totales de todas los atomos
	int pasos = 0;
	//Vector con la distancia entre colisiones
	vector<double> lCol (0);
	//Libre recorrido medio
	double lMed = 0;

//Se resetean las posiciones a cero
	for(int i = 0; i < n; i++) {
		x[i] = 0;
		y[i] = 0;
		z[i] = 0;
		vx[i] = 0;
		vy[i] = 0;
		vz[i] = 0;
		rr[i] = 0;

	}
//Disposicion inicial de las partículas, y distribucion de las velocidades
	cout << "Calculando las posiciones y distribuciones de la velocidad iniciales...    ";
	//inicio(n, l, T, m, x, y, z, vx, vy, vz);
	inicioModificado(n, lext, lin, Text, Tin, m, x, y, z, vx, vy, vz);
	cout << "[Hecho]\n\n";

	cout << "Calculando los movimientos de los atomos y la presión sobre la pared para " << t*dt << " segundos\n\n";
	for(int j = 0; j < t; j++) {
		for(int i = 0; i < n; i++) {
			//Se calcula el modulo del radio del movimiento de cada particula como |v|*dt
			rr[i] = dt * sqrt(vx[i] * vx[i] + vy[i] * vy[i] + vz[i] * vz[i]);
			//Se sacan dos angulos aleatorios
			teta = minimo + abs((double)rand() / (RAND_MAX + 1.0)) * (maximo * 0.5 - minimo);
			phi = minimo + abs((double)rand() / (RAND_MAX + 1.0)) * (maximo - minimo);
			//Para cada paso de cada particula se resetea su estado como que no ha chocado
			chocado = false;
			//Se comprueba si se sale del cubo
			if(fuera(x[i], y[i], z[i], rr[i], teta, phi, l) == false) {
				if (colisiones == true) {
					//Si no se sale, se mueve la particula qq*dr
					double qq = 0.0;
					//Bucle que recorre las n particulas
					for(int k = 0; k < n; k++)
						do {
							qq += 1.0;
							if(k != i && distancia(x[i] + qq * dr * sin(teta) * cos(phi), y[i] + qq * dr * sin(teta) * sin(phi), z[i] + qq * dr * cos(teta), x[k], y[k], z[k]) <= 2.0 * radioH) {

								//Si en esta iteracion de tiempo t no habia chocado, se saca su libre recorrido
								if(chocado == false) {
									lCol.push_back(qq * dr);
									//Se cumple que la distancia entre la particula i y la k es menor que dos veces el radio del hidrogeno
									choque += 1;
								}
								//Se marca como que ha chocado
								chocado = true;
							}
						} while(dr * qq <= rr[i]);
				}
				//Calculamos la posicion en cartesianas
				x[i] = x[i] + rr[i] * sin(teta) * cos(phi);
				y[i] = y[i] + rr[i] * sin(teta) * sin(phi);
				z[i] = z[i] + rr[i] * cos(teta);
				//Se aumenta el contador de pasos totales para verificar que las particulas se mueven
				pasos += 1;
			} else {
				//Si se sale, se calcula el momento que le transpasa a la pared
				momento = incrementoMomento(x[i], y[i], z[i], vx[i], vy[i], vz[i], momento, rr[i], teta, phi, l, m);
			}
		}
		//Barra de progreso
		loadbar(j + 1, t, 50);
	}
	if (colisiones == true) {
		//Calculo de la distancia media entre colisiones
		double suma = 0;
		for(int i = 0; i < lCol.size(); i++) {
			suma += lCol[i];
		}
		lMed = suma / lCol.size();
		//Sacar la distancia entre colisiones
		ofstream salida2 ("colisiones.txt", ios::out);
		for (int i = 0; i < lCol.size(); i++) {
			salida2 << lCol[i] << endl;
		}
		salida2.close();
	}

//Sacar la posicion de las particulas, la primera columna es x, la segunda y
	ofstream salida ("posiciones.txt", ios::out);
	for (int i = 0; i < n; i++) {
		salida << x[i] << " " << y[i] << " " << z[i]  << endl;
	}
	salida.close();

// Sacar velocidades por zonas
	ofstream F1("Datosexterior.txt");
	ofstream F2("Datosinterior.txt");
	for(int i = 0; i < n; i++) {
		v[i] = sqrt(vx[i] * vx[i] + vy[i] * vy[i] + vz[i] * vz[i]);
		if(x[i] > lext * 0.5 - lin) { // modificación para el cubo interior
			if(x[i] < lext * 0.5 + lin) {
				if(y[i] > lext * 0.5 - lin) {
					if(y[i] < lext * 0.5 + lin) {
						if(z[i] > lext * 0.5 - lin) {
							if(z[i] < lext * 0.5 + lin) {
								F2 << v[i] << endl;
							}
						}
					}
				}
			}
		}// fin sextuple if zona de modificación
		if(x[i] < lext * 0.5 - lin) { // modificación para el cubo interior
			F1 << v[i] << endl;
		} else if(x[i] > lext * 0.5 + lin) {
			F1 << v[i] << endl;
		} else if(y[i] < lext * 0.5 - lin) {
			F1 << v[i] << endl;
		} else if(y[i] > lext * 0.5 + lin) {
			F1 << v[i] << endl;
		} else if(z[i] < lext * 0.5 - lin) {
			F1 << v[i] << endl;
		} else if(z[i] > lext * 0.5 + lin) {
			F1 << v[i] << endl;
		}
// fin sextuple if zona de modificación
	}


//Salida final por pantalla
	cout << "\n\n              ####   RESULTADOS   ####\n";
	cout << "\nLado del cubo:                          " << l << "  m";
	cout << "\n\nRadio del atomo:                        " << radioH << "  m";
	cout << "\n\nPasos de todos los atomos               " << pasos;
	cout << "\n\nNumero de atomos de gas:                " << n;
	cout << "\n\nTiempo total de simulacion:            " << t*dt << "  s";
	cout << "\n\nMomento total sobre las paredes:        " << momento  << "  kg m/s";
	if (colisiones == true) {
		cout << "\n\nNumero de choques:                      " << choque << endl;
		cout << "\nLibre recorrido medio:                  " << lMed << "  m";
	}
	cout << "\n\nPresion numerica:                       " << (momento / (l * l * 6.0)) / (t * dt) << "  Pa";
	cout << "\n\n";
	
	return 0;
}
