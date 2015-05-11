double incrementoMomento(double x, double y, double z, double vx, double vy, double vz, double momento, double rr, double teta, double phi, double l, double m)
{
	if(x + rr * sin(teta)*cos(phi) > l || (x + rr * sin(teta)*cos(phi)) < 0) {
		return (momento += 2.0 * m * abs(vx));
	} else if( (y + rr * sin(teta)*sin(phi)) > l || (y + rr * sin(teta)*sin(phi)) < 0) {
		return (momento += 2.0 * m * abs(vy));
	} else if( (z + rr * cos(teta)) > l || (z + rr * cos(teta)) < 0) {
		return (momento += 2.0 * m * abs(vz));
	}
	return momento;
}
