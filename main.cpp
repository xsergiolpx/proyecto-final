#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include "fuera.h"

using namespace std;

int main(int argc, char **argv)
{
	//Pasos de tiempo
	int t=10000;
	double dt=0.00001;
	//Tamaño del cubo, temperatura, masa.
	double l=1, T=1, m=1.66e-27;
	//Numero de particulas
	int n=20;
	//Variables de las coordenadas esfericas de los caminantes
	double teta, phi, minimo=0, maximo=2*3.14159265;
	srand(time(NULL)); // semilla
	double x[n], y[n], z[n], vx[n], vy[n], vz[n], rr[n];

	//Se resetean las posiciones a cero
	for(int i=0; i<n; i++) {
		x[i]=0.5;
		y[i]=0.5;
		z[i]=0.5;
		vx[i]=1000;
		vy[i]=1000;
		vz[i]=1000;
		rr[i]=0;
	}
	
	//Variable radial de cada caminante
	for(int i=0; i<n; i++) {
		rr[i]=dt*sqrt(vx[i]*vx[i]+vy[i]*vy[i]+vz[i]*vz[i]);
	}

	for(int i=0; i<t; i++) {
		for(int i=0; i<n; i++) {
			//Se sacan dos angulos aleatorios
			teta=minimo+abs((double)rand()/(RAND_MAX+1.0))*(maximo-minimo);
			phi=minimo+abs((double)rand()/(RAND_MAX+1.0))*(maximo-minimo);
			//Calculamos la posicion en cartesianas
			if(fuera(x[i],y[i],z[i],rr[i],teta,phi,l)==false) {
				//Si no se sale, se mueve la particula
				x[i]=x[i]+rr[i]*sin(teta)*cos(phi);
				y[i]=y[i]+rr[i]*sin(teta)*sin(phi);
				z[i]=z[i]+rr[i]*cos(teta);
			}
		}
	}


//Sacar la posicion de las particulas, la primera columna es x, la segunda y
	ofstream salida ("posiciones.txt", ios::out);
	for (int i = 0; i < n; i++) {
		salida << x[i] << " " << y[i] << endl;
		cout << x[i]<< " " << y[i] << endl;
	}
	salida.close();
	return 0;
}
