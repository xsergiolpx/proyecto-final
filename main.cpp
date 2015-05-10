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
#include "inicio.h"
#include "incrementoMomento.h"
#include "progreso.h"
#include "distancia.h"

using namespace std;

int main(int argc, char **argv)
{
	//Pasos de tiempo
	int t = 100;
	//Diferencial de tiempo
	double dt = 1e-11;
	//Tamaño del cubo, temperatura, masa.
	double l = 0.0000001, T = 273, m = 1.66e-27, momento = 0;
	//Radio helio
	double radioHe = 31e-12;
	//Diferencial de camino para mover la particula y comprobar si se choca con otra
	double dr = 0.000001;
	//Numero de choques
	int choque = 0;
	//Numero de particulas
	int n = 3000;
	//Variables de las coordenadas esfericas de los caminantes
	double teta, phi, minimo = 0, maximo = 2 * 3.14159265;
	// semilla
	srand(time(NULL));
	//Componentes de la velocidad y la posicion
	double x[n], y[n], z[n], vx[n], vy[n], vz[n], rr[n];
	int pasos = 0;

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
	inicio(n, l, T, m, x, y, z, vx, vy, vz);
	cout << "[Hecho]\n\n";

	cout << "Calculando los movimientos de los atomos y la presión sobre la pared para " << t*dt << " segundos\n\n";
	for(int j = 0; j < t; j++) {
		for(int i = 0; i < n; i++) {
			//Se calcula el modulo del radio del movimiento de cada particula como |v|*dt
			rr[i] = dt * sqrt(vx[i] * vx[i] + vy[i] * vy[i] + vz[i] * vz[i]);
			//Se sacan dos angulos aleatorios
			teta = minimo + abs((double)rand() / (RAND_MAX + 1.0)) * (maximo / 2 - minimo);
			phi = minimo + abs((double)rand() / (RAND_MAX + 1.0)) * (maximo - minimo);
			if(fuera(x[i], y[i], z[i], rr[i], teta, phi, l) == false) {
				//Si no se sale, se mueve la particula qq*dr
				double qq = 0.0;
				//Bucle que recorre las n particulas
				for(int k = 0; k < n; k++)
					do {
						qq += 1.0;
						if(k != i && distancia(x[i] + qq * dr * sin(teta) * cos(phi), y[i] + qq * dr * sin(teta) * sin(phi), z[i] + qq * dr * cos(teta), x[k], y[k], z[k]) <= 2.0 * radioHe) {
							//Se cumple que la distancia entre la particula i y la k es menor que dos veces el radio del hidrogeno
							choque += 1;
						}
					} while(dr * qq <= rr[i]);
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

//Sacar la posicion de las particulas, la primera columna es x, la segunda y
	ofstream salida ("posiciones.txt", ios::out);
	for (int i = 0; i < n; i++) {
		salida << x[i] << " " << y[i] << " " << z[i]  << endl;
		cout << rr[i] << endl;
	}
	salida.close();


//Salida final por pantalla
	cout << "\n\n              ####   RESULTADOS   ####\n";
	cout << "\nLado del cubo:                          " << l;
	cout << "\n\nRadio del atomo:                        " << radioHe;
	cout << "\n\nPasos de todos los atomos               " << pasos;
	cout << "\n\nNumero de atomos de gas:                " << n;
	cout << "\n\nTiempo total de interaccion:            " << t*dt << "  s";
	cout << "\n\nMomento total sobre las paredes:        " << momento  << "  kg m/s\n\n";
	cout << "\n\nNumero de choques:                      " << choque << endl;
//cout <<     "Trabajo del gas:                        " << momento / dt << "   J\n\n";
	return 0;
}
