/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:49:08 by vbauguen          #+#    #+#             */
/*   Updated: 2015/12/11 18:06:24 by vbauguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# define GLFW_DLL
# define GL_LOG_FILE "gl.log"
# define PI 3.1415
# define PI_OVER_360 3.1415/360
# define OBJ_PATH "./models/teapot2.obj"
# define BMP_PATH "./textures/glass.bmp"
# define CAMERA_SPEED deltatime * 20
# define DEBUG 0

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <math.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include <stdio.h>
# include <assert.h>
# include <time.h>
# include <stdarg.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <string.h>

typedef struct		s_window_context
{
	float			ratio;
	GLFWwindow		*window;
	int				width;
	int				height;
	char			**array;
	char			*obj_file;
	int				vertex_number;
	int				face_number;
	GLuint			texid;
	GLfloat			model[16];
	GLfloat			view[16];
	GLfloat			projection[16];
	GLfloat			mat4[16];
	float			texon;
	float			perlstr;
	GLuint			points_vbo;
	GLuint			colours_vbo;
	GLuint			index_buffer;
	GLuint			vao;
}					t_window_context;

int					restart_gl_log();
int					gl_log(const char *message, ...);
int					gl_log_err(const char *message, ...);
int					check_shader_compilation(GLuint shader_index);
unsigned int		obj_load_image(const char *filename);
void				update_camera(t_window_context *context,
	float deltatime, float *view);
void				init_structure(t_window_context *c);
void				gl_settings(t_window_context *c);
void				ft_load_shaders(GLuint *shader_programme);
void				glfw_error_callback(int error, const char *description);
double				dtor(double degree);
double				rtod(double radian);
void				multiply_mat4(float *c, float *a, float *b);
void				matrix_print(float *m);
void				rotate_mat4_y(float *c, float *a, float theta);
void				get_vertices_into_vbo(t_window_context *c, float *dest,
	float *colours, int i);
void				get_faces_into_array(t_window_context *c,
	GLuint *dest, int *i);
void				translate_mat4(float *c, float x, float y, float z);
void				frustum(float *m, float *schlag);
void				mat4_loadid(float *m);
GLuint				load_bmp(const char *imagepath);

#endif
