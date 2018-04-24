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

#include "../includes/scop.h"

void	ft_load_shaders(GLuint *shader_programme)
{
	GLuint		vs;
	GLuint		fs;
	const char	*vertex_shader;
	const char	*fragment_shader;

	vertex_shader = get_whole_file_as_string("./src/shaders/vs.glsl");
	fragment_shader = get_whole_file_as_string("./src/shaders/fs.glsl");
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	free((void *)vertex_shader);
	vertex_shader = NULL;
	assert(check_shader_compilation(vs) == 1);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	free((void *)fragment_shader);
	fragment_shader = NULL;
	assert(check_shader_compilation(fs) == 1);
	glAttachShader(*shader_programme, fs);
	glAttachShader(*shader_programme, vs);
	glLinkProgram(*shader_programme);
}

float	*schlag(void)
{
	float *tamerelanorme;

	tamerelanorme = (float *)malloc(6 * sizeof(float));
	tamerelanorme[0] = -(float)1680 / 1260;
	tamerelanorme[1] = (float)1680 / 1260;
	tamerelanorme[2] = -1.0;
	tamerelanorme[3] = 1.0;
	tamerelanorme[4] = 1.0;
	tamerelanorme[5] = 1000;
	return (tamerelanorme);
}

void	init2(t_window_context *c)
{
	float	*tamerelanorme;

	tamerelanorme = schlag();
	mat4_loadid(c->model);
	mat4_loadid(c->view);
	mat4_loadid(c->mat4);
	c->texid = load_bmp(BMP_PATH);
	c->texon = 1;
	c->perlstr = 1;
	c->array = ft_strsplit(c->obj_file, '\n');
	frustum(c->projection, tamerelanorme);
	free(tamerelanorme);
}

void	init_structure(t_window_context *c)
{
	int		x;

	c->obj_file = get_whole_file_as_string(OBJ_PATH);
	x = 0;
	init2(c);
	free(c->array[x]);
	while (c->array[x] && c->array[x++])
	{
		c->array[x - 1] = NULL;
		if (c->array[x] && c->array[x][0] == 'v')
			c->vertex_number += 3;
		else if (c->array[x] && c->array[x][0] == 'f')
		{
			if (ft_get_number_of_words(c->array[x], ' ') == 4)
				c->face_number += 3;
			else if (ft_get_number_of_words(c->array[x], ' ') == 5)
				c->face_number += 6;
		}
		free(c->array[x]);
	}
	c->array[x - 1] = NULL;
	free(c->array);
	c->array = NULL;
}

void	update_camera(t_window_context *context, float deltatime, float *view)
{
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_S))
		translate_mat4(view, 0, 0, -CAMERA_SPEED);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_W))
		translate_mat4(view, 0, 0, CAMERA_SPEED);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_D))
		translate_mat4(view, -CAMERA_SPEED, 0, 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_A))
		translate_mat4(view, CAMERA_SPEED, 0, 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_SPACE))
		translate_mat4(view, 0, -CAMERA_SPEED, 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_LEFT_CONTROL))
		translate_mat4(view, 0, CAMERA_SPEED, 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_T))
		context->texon += (context->texon + 0.01 < 1 ? 0.01 : 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_Y))
		context->texon -= (context->texon - 0.01 > 0 ? 0.01 : 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_G))
		context->perlstr += (context->perlstr + 0.01 < 1 ? 0.01 : 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_H))
		context->perlstr -= (context->perlstr - 0.01 > 0 ? 0.01 : 0);
	if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(context->window, 1);
}
