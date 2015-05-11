/*
 * 	Barra de progreso de los cálculos, donde x es el paso por el que va, n es el paso total, y w es la resolución de la barra
 */
static inline void loadbar(unsigned int x, unsigned int n, unsigned int w = 50)
{
	if ( (x != n) && (x % (n / 100 + 1) != 0) ) return;

	float ratio  =  x / (float)n;
	int   c      =  ratio * w;

	std::cout << std::setw(3) << (int)(ratio * 100) << "% [";
	for (int x = 0; x < c; x++) std::cout << "=";
	for (int x = c; x < w; x++) std::cout << " ";
	std::cout << "]\r" << std::flush;
}
