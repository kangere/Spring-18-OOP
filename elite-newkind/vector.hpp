#ifndef VECTOR_HPP	
#define VECTOR_HPP

class vector {

private:
	double x,y,z;
	void rotate_var(int,int,int);

public:
	vector(double x, double y, double z): x(x),y(y),z(z)
	{}

	double get_x()const {return x;}
	double get_y()const {return y;}
	double get_z()const {return z;}

	void set_x(double x1){ x = x1;}
	void set_y(double y1){ y = y1;}
	void set_z(double z1){ z = z1;}
	
	void mult_vector(vector&);
	double vector_dot_product(vector&);
	vector unit_vector();
	void rotate_vec(double,double);
	
	void rotate_x(int,int);
	void rotate_y(int,int);
	void rotate_z(int,int);

	void operator=(vector&);
};

typedef vector Matrix[3];



void set_init_matrix (vector *mat);
void tidy_matrix (vector *mat);

#endif