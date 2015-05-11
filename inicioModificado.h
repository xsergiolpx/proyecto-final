
double MB(double vi, double m, double T)
{
	// función que calcula la probabilidad para un valor de una de las componentes de la velocidad segun la distribución marginal para una componente de Maxwell-Boltzmann

	double K = 1.3806504e-23; // cte de Boltzmann
	double Fmb;
	Fmb = sqrt(m / (2 * K * T)) * exp(-m * (vi) * (vi) / (2 * K * T));
	return Fmb;

}  // fin de la función de distribución de velocidades moleculares

void inicioModificado(int n, double lext, double lin, double Text, double Tin, double m, double* x, double* y, double* z, double* vx, double* vy, double* vz)
{

// inicio: función que genera el estado inicial del gas en una caja cúbica

// Entrada:

// n: número de partículas en la caja (u entero al cubo)
// l: lado de la caja
// T: temperatura
// m: masa molecular
// x,y,z: punteros donde se guardaran las coordenadas de las partículas
// vx,vy,vz: punteros para las componentes de las velocidades

// Salida:
// Es tipo void pero escribe sobre los punteros x,y,z

	srand (time(NULL));
	double Nm = INT_MAX;  // Máximo entero
	double rango = lext;    // el rango
	double liminf = 0;

// ahora colocamos las partículas homogenenamente distribuidads en el cubo
	for(int i = 0; i < n; i++) {
		x[i] = (double(rand()) * rango) / Nm + liminf;
		y[i] = (double(rand()) * rango) / Nm + liminf;
		z[i] = (double(rand()) * rango) / Nm + liminf;
	} // fin del  for de distribución

// ahora generamos la distribución inicial de velocidades con números aleatorios que se ajustan a la distribución de velocidades moleculares de Maxwell-Boltzmann

	double K = 1.3806504e-23; // cte Boltzmann
	double sigma = sqrt(K * Text / m); // desviación típica de la distribución
	double sigma2 = sqrt(K * Tin / m);
	rango = 5 * sigma;  // el rango
	double rango2 = 5 * sigma2;
	liminf = -2.5 * sigma;
	double liminf2 = -2.5 * sigma2;
// ahora se genenran los numeros aleatorios que se van aceptando o rechazando
	double Pteor;
	double Ptest;
	double vi; // probabilidades
	for(int i = 0; i < n; i++) {
		vx[i] = (double(rand()) * rango) / Nm + liminf;
		Ptest = double(rand()) / Nm; // entre 0 y 1
		vi = vx[i];
		Pteor = MB(vi, m, Text); // probabilidad según la distribución
		if(x[i] > lext * 0.5 - lin) { // modificación para el cubo interior
			if(x[i] < lext * 0.5 + lin) {
				if(y[i] > lext * 0.5 - lin) {
					if(y[i] < lext * 0.5 + lin) {
						if(z[i] > lext * 0.5 - lin) {
							if(z[i] < lext * 0.5 + lin) {
								vx[i] = (double(rand()) * rango2) / Nm + liminf2;
								Ptest = double(rand()) / Nm; // entre 0 y 1
								vi = vx[i];
								Pteor = MB(vi, m, Tin); // probabilidad según la distribución

							}
						}
					}
				}
			}
		}// fin sextuple if zona de modificación
		if(Ptest > Pteor) {
			i = i - 1; // se rechaza
		}
	}

// ahora la componente y de la velocidad

	for(int i = 0; i < n; i++) {
		vy[i] = (double(rand()) * rango) / Nm + liminf;
		Ptest = double(rand()) / Nm; // entre 0 y 1
		vi = vy[i];
		Pteor = MB(vi, m, Text); // probabilidad según la distribución
		if(x[i] > lext * 0.5 - lin) { // modificación para el cubo interior
			if(x[i] < lext * 0.5 + lin) {
				if(y[i] > lext * 0.5 - lin) {
					if(y[i] < lext * 0.5 + lin) {
						if(z[i] > lext * 0.5 - lin) {
							if(z[i] < lext * 0.5 + lin) {
								vx[i] = (double(rand()) * rango2) / Nm + liminf2;
								Ptest = double(rand()) / Nm; // entre 0 y 1
								vi = vx[i];
								Pteor = MB(vi, m, Tin); // probabilidad según la distribución

							}
						}
					}
				}
			}
		}// fin sextuple if zona de modificación
		if(Ptest > Pteor) {
			i = i - 1; // se rechaza
		}
	}


// ahora la componente z de la velocidad

	for(int i = 0; i < n; i++) {
		vz[i] = (double(rand()) * rango) / Nm + liminf;
		Ptest = double(rand()) / Nm; // entre 0 y 1
		vi = vz[i];
		Pteor = MB(vi, m, Text); // probabilidad según la distribución
		if(x[i] > lext * 0.5 - lin) { // modificación para el cubo interior
			if(x[i] < lext * 0.5 + lin) {
				if(y[i] > lext * 0.5 - lin) {
					if(y[i] < lext * 0.5 + lin) {
						if(z[i] > lext * 0.5 - lin) {
							if(z[i] < lext * 0.5 + lin) {
								vx[i] = (double(rand()) * rango2) / Nm + liminf2;
								Ptest = double(rand()) / Nm; // entre 0 y 1
								vi = vx[i];
								Pteor = MB(vi, m, Tin); // probabilidad según la distribución

							}
						}
					}
				}
			}
		}// fin sextuple if zona de modificación
		if(Ptest > Pteor) {
			i = i - 1; // se rechaza
		}
	}


}// fin de la función inicio
