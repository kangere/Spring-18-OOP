#ifndef VECTOR_HPP	
#define VECTOR_HPP

class vector {

private:
	double x,y,z;

public:
	vector(double x, double y, double z): x(x),y(y),z(z)
	{}

	double get_x()const {return x;}
	double get_y()const {return y;}
	double get_z()const {return z;}
	void mult_vector(vector&);
	double vector_dot_product(vector&);
	vector unit_vector();
	void rotate_vec(double,double);

	void operator=(vector&);
};

typedef vector Matrix[3];


#endif