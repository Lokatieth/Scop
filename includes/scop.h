
#ifndef SCOP_H
# define SCOP_H
#define GLFW_DLL
#define GL_LOG_FILE "gl.log"
#define PI 3.1415
#define PI_OVER_360 3.1415/360
#define OBJ_PATH "./models/42.obj"
#define CAMERA_SPEED deltaTime * 20
#define DEBUG 1

#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdarg.h>


typedef struct s_mat3
{
	double x;
	double y;
	double z;
}				s_mat3;

typedef struct s_mat4
{
	double x;
	double y;
	double z;
	double w;
}				s_mat4;

typedef struct 	s_key_inputs
{
	int w;
	int a;
	int s;
	int d;
}				s_keys;

typedef struct		s_window_context
{
	GLFWwindow* window;
	float ratio;
    int width;
    int height;
    char const *obj_file;
    int vertex_number;
    int face_number;
    s_keys keys;
    GLuint texId;
}					s_window_context;


int restart_gl_log();
int gl_log(const char* message, ...);
int gl_log_err(const char* message, ...);
void glfw_error_callback(int error, const char* description);
int check_shader_compilation(GLuint shader_index);
s_mat3 x_rotate_mat3(s_mat3 *mat, int theta);
s_mat3 y_rotate_mat3(s_mat3 *mat, int theta);
s_mat3 z_rotate_mat3(s_mat3 *mat, int theta);
double degrees_to_radians(double degree);
double radians_to_degrees(double radian);
void multiply_mat4(float *c, float *a, float *b);
void  matrix_mul_scalar(float *c,float *a,float b);
void matrix_print(float *m);
void rotate_mat4_x(float *c, float *a, float theta);
void rotate_mat4_y(float *c, float *a, float theta);
void rotate_mat4_z(float *c, float *a, float theta);
void get_vertices_into_vbo(s_window_context *c, float *dest);
void scale_mat4(float*c, float *a, float scale);
void get_faces_into_array(s_window_context *c, GLuint *dest);
void translate_mat4(float *c, float *a, float x, float y, float z);
// int  get_face_number(const char *obj_file);
void copy_mat4(float*c, float *a);
void build_perspective( float *m, float fov, float aspect, float nearDist, float farDist);
void frustum(float *m, float left, float right, float bottom, float top, float near, float far);
void mat4_loadIdentity(float *m);


#endif