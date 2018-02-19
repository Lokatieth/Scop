#include "../includes/scop.h"

double radians_to_degrees(double radian)
{
	return (radian / (PI * 180));
}

double degrees_to_radians(double degree)
{
	return (degree * PI / 180);
}

void rotate_mat4_x(float *c, float *a, float t)
{
	GLfloat matrot[16] = {
		1,   	0,   		0,        	0,
		0,  	cos(t), 	sin(t),   	0,
		0,  	-sin(t),	cos(t),   	0,
		0,  	0,        	0,        	1,
	};
	multiply_mat4(c, a, matrot);
}

void rotate_mat4_y(float *c, float *a, float t)
{
	GLfloat matrot[16] = {
		cos(t),  	0,			-sin(t),  0,
		0,       	1,      	0,        0,
		sin(t),  	0,   		cos(t),   0,
		0,        	0,			0,        1,
	};
	multiply_mat4(c, a, matrot);
}

void rotate_mat4_z(float *c, float *a, float t)
{
	GLfloat matrot[16] = {
		cos(t),   sin(t),   0,        0,
		-sin(t),  cos(t),   0,        0,
		0,        0,        1,        0,
		0,        0,        0,        1,
	};
	multiply_mat4(c, a, matrot);
}


void translate_mat4(float *c, float *a, float x, float y, float z)
{
	GLfloat matrot[16] = {
		1,   	0,   	0,        0,
		0,  	1,   	0,        0,
		0,      0,      1,        0,
		x,      y,      z,        1,
	};
	multiply_mat4(c, a, matrot);
}


s_mat3 x_rotate_mat3(s_mat3 *mat, int theta)
{
	s_mat3 result;

	result.x = mat->x;
	result.y = mat->y * cos(radians_to_degrees(theta)) - mat->z * sin(radians_to_degrees(theta));
	result.z = mat->y * sin(radians_to_degrees(theta)) + mat->z * cos(radians_to_degrees(theta));
	return (result);
}

s_mat3 y_rotate_mat3(s_mat3 *mat, int theta)
{
	s_mat3 result;

	result.x = mat->z * sin(radians_to_degrees(theta)) + mat->x * cos(radians_to_degrees(theta));	
	result.y = mat->y;
	result.z = mat->z * cos(radians_to_degrees(theta)) - mat->x * sin(radians_to_degrees(theta)); 
	return (result);
}

s_mat3 z_rotate_mat3(s_mat3 *mat, int theta)
{
	s_mat3 result;

	result.x = mat->x * cos(radians_to_degrees(theta)) - mat->y * sin(radians_to_degrees(theta));
	result.y = mat->x * sin(radians_to_degrees(theta)) + mat->y * cos(radians_to_degrees(theta));
	result.z = mat->z;
	return (result);
}

void copy_mat4(float*c, float *a)
{
	int i;
	GLfloat q[16];

	i = 0;
	while(i < 16)
	{
		q[i] = a[i];
	}
    for(int i=0;i<16;i++) c[i]=q[i];
}

void scale_mat4(float*c, float *a, float scale)
{
	int i;
	GLfloat q[16];

	i = 0;
	while (i < 16)
	{
		q[i] = a[i] * scale;
	}
    for(int i=0;i<16;i++) c[i]=q[i];
	
}

void multiply_mat4(float *c, float *a, float *b)
{
	GLfloat q[16];
    q[ 0] = (a[ 0] * b[ 0]) + (a[ 1] * b[ 4]) + (a[ 2] * b[ 8]) + (a[ 3] * b[12]);
    q[ 1] = (a[ 0] * b[ 1]) + (a[ 1] * b[ 5]) + (a[ 2] * b[ 9]) + (a[ 3] * b[13]);
    q[ 2] = (a[ 0] * b[ 2]) + (a[ 1] * b[ 6]) + (a[ 2] * b[10]) + (a[ 3] * b[14]);
    q[ 3] = (a[ 0] * b[ 3]) + (a[ 1] * b[ 7]) + (a[ 2] * b[11]) + (a[ 3] * b[15]);
    q[ 4] = (a[ 4] * b[ 0]) + (a[ 5] * b[ 4]) + (a[ 6] * b[ 8]) + (a[ 7] * b[12]);
    q[ 5] = (a[ 4] * b[ 1]) + (a[ 5] * b[ 5]) + (a[ 6] * b[ 9]) + (a[ 7] * b[13]);
    q[ 6] = (a[ 4] * b[ 2]) + (a[ 5] * b[ 6]) + (a[ 6] * b[10]) + (a[ 7] * b[14]);
    q[ 7] = (a[ 4] * b[ 3]) + (a[ 5] * b[ 7]) + (a[ 6] * b[11]) + (a[ 7] * b[15]);
    q[ 8] = (a[ 8] * b[ 0]) + (a[ 9] * b[ 4]) + (a[10] * b[ 8]) + (a[11] * b[12]);
    q[ 9] = (a[ 8] * b[ 1]) + (a[ 9] * b[ 5]) + (a[10] * b[ 9]) + (a[11] * b[13]);
    q[10] = (a[ 8] * b[ 2]) + (a[ 9] * b[ 6]) + (a[10] * b[10]) + (a[11] * b[14]);
    q[11] = (a[ 8] * b[ 3]) + (a[ 9] * b[ 7]) + (a[10] * b[11]) + (a[11] * b[15]);
    q[12] = (a[12] * b[ 0]) + (a[13] * b[ 4]) + (a[14] * b[ 8]) + (a[15] * b[12]);
    q[13] = (a[12] * b[ 1]) + (a[13] * b[ 5]) + (a[14] * b[ 9]) + (a[15] * b[13]);
    q[14] = (a[12] * b[ 2]) + (a[13] * b[ 6]) + (a[14] * b[10]) + (a[15] * b[14]);
    q[15] = (a[12] * b[ 3]) + (a[13] * b[ 7]) + (a[14] * b[11]) + (a[15] * b[15]);
    for(int i=0;i<16;i++) c[i]=q[i];
}

void  matrix_mul_vector(float *c,float *a,float *b)
{
GLfloat q[3];
q[0]=(a[ 0]*b[0])+(a[ 1]*b[1])+(a[ 2]*b[2])+(a[ 3]);
q[1]=(a[ 4]*b[0])+(a[ 5]*b[1])+(a[ 6]*b[2])+(a[ 7]);
q[2]=(a[ 8]*b[0])+(a[ 9]*b[1])+(a[10]*b[2])+(a[11]);
for(int i=0;i<3;i++) c[i]=q[i];
}

void  matrix_mul_scalar(float *c,float *a,float b)
{
GLfloat q[3];
q[0] = (a[ 0] * b) + (a[ 1] * b) + (a[ 2] * b) + (a[ 3]);
q[1] = (a[ 4] * b) + (a[ 5] * b) + (a[ 6] * b) + (a[ 7]);
q[2] = (a[ 8] * b) + (a[ 9] * b) + (a[10] * b) + (a[11]);
for(int i=0;i<3;i++) c[i]=q[i];
}

void matrix_print(float *m)
{
   	printf("-------------------\n");
	for (int i = 0; i < 16; ++i)
   	{
   		printf(" [%lf] ", m[i]);
   		if (i%4 == 3)
   		{
   			printf("\n");
   		}
   	}
   	printf("-------------------\n");
}

void mat4_loadIdentity(float *m)
{
	m[ 0] = 1;
	m[ 1] = 0;
	m[ 2] = 0;
	m[ 3] = 0;
	m[ 4] = 0;
	m[ 5] = 1;
	m[ 6] = 0;
	m[ 7] = 0;
	m[ 8] = 0;
	m[ 9] = 0;
	m[10] = 1;
	m[11] = 0;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;

}

	void frustum(float *m, float left, float right, float bottom, float top, float near, float far)
	 {

    float r_width  = 1.0f / (right - left);
    float r_height = 1.0f / (top - bottom);
    float r_depth  = 1.0f / (far - near);
    float x =  2.0f * (r_width);
    float y =  2.0f * (r_height);
    float z =  2.0f * (r_depth);
    float A = (right + left) * r_width;
    float B = (top + bottom) * r_height;
    float C = (far + near) * r_depth;
    m[0] = x;
    m[3] = -A;
    m[5] = y;
    m[7] = -B;
    m[10] = -z;
    m[11] = -C;
    m[ 1] = 0.0f;
    m[ 2] = 0.0f;
    m[ 4] = 0.0f;
    m[ 6] = 0.0f;
    m[ 8] = 0.0f;
    m[ 9] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;

}


void build_perspective( float *m, float fov, float aspect, float nearDist, float farDist)
{
    //
    // General form of the Projection Matrix
    //
    // uh = Cot( fov/2 ) == 1/Tan(fov/2)
    // uw / uh = 1/aspect
    // 
    //   uw         0       0       0
    //    0        uh       0       0
    //    0         0      f/(f-n)  1
    //    0         0    -fn/(f-n)  0
    //
    // Make result to be identity first

    // check for bad parameters to avoid divide by zero:
    // if found, assert and return an identity matrix.
    float frustumDepth = farDist - nearDist;
    float oneOverDepth = 1 / frustumDepth;
    mat4_loadIdentity(m);

    m[0] =  -1* m[5] / aspect;
    m[5] = 1 / tan(0.5f * fov);
    m[10] = farDist * oneOverDepth;
    m[14] = (-farDist * nearDist) * oneOverDepth;
    m[11] = 1;
    m[15] = 0;
}








