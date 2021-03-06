#include "vector.hpp"
#include <math.h>


static const Matrix start_matrix = 
{
	{1.0,0.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,-1.0}
};

/*
*funciton multiplies this vector with a second matrix 
*and updates fields of current vector (this vector)
*/
void vector::mult_vector(vector *matrix)
{
	double t_x, t_y, t_z;
	t_x = (x * matrix[0].x) + (y * matrix[0].y) + (z * matrix[0].z);
	t_y = (x * matrix[1].x) + (y * matrix[1].y) + (z * matrix[1].z);
	t_z = (x * matrix[2].x) + (y * matrix[2].y) + (z * matrix[2].z);

	x = t_x;
	y = t_y;
	z = t_z;
}

/*
* Calculate the dot product of two vectors sharing a common point.
* Returns the cosine of the angle between the two vectors.
*/
double vector::vector_dot_product(vector &vec)
{
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

/*
 * Convert a vector into a vector of unit (1) length.
 */
vector vector::unit_vector()
{
	double uni;
	uni = sqrt (x * x + y * y + z * z);

	return vector((x / uni),(y / uni),(z / uni));
}

/*
* rotates vector
* replaces rotate_vec function in space.c
* consolidate vector functions to vector class
*/
void vector::rotate_vec(double alpha, double beta)
{
	double t_x, t_y, t_z;

	t_y = y - alpha * x;
	t_x = x + alpha * t_y;
	t_y = t_y - beta * z;
	t_z = z + beta * t_y;

	x = t_x;
	y = t_y;
	z = t_z;
}

void vector::rotate_var(int first, int second, int direction)
{
	double fx,ux;

	fx = first;
	ux = second;

	if (direction < 0)
	{	
		first = fx - (fx / 512) + (ux / 19);
		second = ux - (ux / 512) - (fx / 19);
	}
	else
	{
		first = fx - (fx / 512) - (ux / 19);
		second = ux - (ux / 512) + (fx / 19);
	}
}

/*
*	Functions rotates the x,y or z values with another vector's
*	x,y, or z value - (not too sure)
*
*/
void vector::rotate_x(int t_x,int direction)
{
	rotate_var(x,t_x,direction);
}

void vector::rotate_y(int t_y,int direction)
{
	rotate_var(y,t_y,direction);
}

void vector::rotate_z(int t_z,int direction)
{
	rotate_var(z,t_z,direction);
}

/*
* overload assignment operator
*/
void vector::operator=(const vector &second)
{
	if(this != &second)
	{
		x = second.x;
		y = second.y;
		z = second.z;	
	}

	
}


/*
*	Resets matrix
*
*
*/
void set_init_matrix (vector *mat)
{
	int i;

	for (i = 0; i < 3; i++)
		mat[i] = start_matrix[i];
}

void tidy_matrix (vector *mat)
{
	mat[2] = mat[2].unit_vector();

	if ((mat[2].get_x() > -1) && (mat[2].get_x() < 1))
	{
		if ((mat[2].get_y() > -1) && (mat[2].get_y() < 1))
		{
			mat[1].set_z(-(mat[2].get_x() * mat[1].get_x() + mat[2].get_y() * mat[1].get_y()) / mat[2].get_z());
		}
		else
		{
			mat[1].set_y(-(mat[2].get_x() * mat[1].get_x() + mat[2].get_z() * mat[1].get_z()) / mat[2].get_y());
		}
	}
	else
	{
		mat[1].set_x(-(mat[2].get_y() * mat[1].get_y() + mat[2].get_z() * mat[1].get_z()) / mat[2].get_x());
	}
	
	mat[1] = mat[1].unit_vector();
	

	/* xyzzy... nothing happens. :-)*/
	
	mat[0].set_x(mat[1].get_y() * mat[2].get_z() - mat[1].get_z() * mat[2].get_y());
	mat[0].set_y(mat[1].get_z() * mat[2].get_x() - mat[1].get_x() * mat[2].get_z());
	mat[0].set_z(mat[1].get_x() * mat[2].get_y() - mat[1].get_y() * mat[2].get_x());
}