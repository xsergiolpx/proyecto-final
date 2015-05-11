/*
 * Esta funcion comprueba si la particula i se sale del cubo de lado l en el siguiente paso 
 */
 
bool fuera(double x, double y,double z,double rr,double teta, double phi, double l)
{
	if((x + rr*sin(teta)*cos(phi)) > l || (y + rr*sin(teta)*sin(phi)) > l || (z + rr*cos(teta)) > l || (x + rr*sin(teta)*cos(phi)) < 0 || (y + rr*sin(teta)*sin(phi)) < 0 || (z + rr*cos(teta)) < 0)
	
	{
		return true;
	}
	return false;
}
