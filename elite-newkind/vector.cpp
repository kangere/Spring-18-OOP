#include "vector.hpp"
#include <math.h>

/*
*funciton multiplies this vector with a matrix 
*and updates fields of current vector
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

	return vector((x / uni),(y / uni),(z / uni))
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

/*
* overload assignment operator
*/
void vector::operator=(vector &second)
{
	x = second.x;
	y = second.y;
	z = second.z;
}

