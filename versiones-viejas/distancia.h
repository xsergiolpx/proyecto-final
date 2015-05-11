/*
*	Distancia entre dos puntos, se tienen que pasar los datos como
*	(x1,y1,z1,x2,y2,z2)
*/

double distancia(double x1, double y1, double z1, double x2, double y2, double z2)
{
	//std::cout << sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2)) << std::endl;
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2)));
}
