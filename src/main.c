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

void					up(t_window_context *c, GLuint sp, float tm)
{
	int					u[6];

	u[0] = glGetUniformLocation(sp, "view");
	u[1] = glGetUniformLocation(sp, "model");
	u[2] = glGetUniformLocation(sp, "projection");
	u[3] = glGetUniformLocation(sp, "time");
	u[4] = glGetUniformLocation(sp, "texon");
	u[5] = glGetUniformLocation(sp, "perlstr");
	glUniformMatrix4fv(u[0], 1, GL_FALSE, c->view);
	glUniformMatrix4fv(u[2], 1, GL_FALSE, c->projection);
	glUniformMatrix4fv(u[1], 1, GL_FALSE, c->model);
	glUniformMatrix4fv(u[0], 1, GL_FALSE, c->view);
	glUniformMatrix4fv(u[2], 1, GL_FALSE, c->projection);
	glUniform1f(u[3], tm);
	glUniform1f(u[4], c->texon);
	glUniform1f(u[5], c->perlstr);
}

void					vao_binding(t_window_context *c)
{
	glGenVertexArrays(1, &c->vao);
	glBindVertexArray(c->vao);
	glBindBuffer(GL_ARRAY_BUFFER, c->points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, c->colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->index_buffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	translate_mat4(c->view, 0, 0, -10);
	rotate_mat4_y(c->model, c->model, dtor(90));
}

void					game_loop(t_window_context *c, GLuint sp)
{
	float				start_time;

	while (!glfwWindowShouldClose(c->window))
	{
		start_time = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		rotate_mat4_y(c->model, c->model, dtor(80 * PI / 180 / 10));
		glUseProgram(sp);
		up(c, sp, start_time);
		glDrawElements(GL_TRIANGLES, c->face_number
		* sizeof(GLuint), GL_UNSIGNED_INT, (GLvoid *)0);
		glfwPollEvents();
		glfwSwapBuffers(c->window);
		update_camera(c, (glfwGetTime() - start_time), c->view);
	}
}

static void				draw_window(t_window_context *c)
{
	float				points[c->vertex_number];
	float				colours[c->face_number];
	GLuint				ind[c->face_number];
	GLuint				shader_programme;
	int					lol[3];

	lol[0] = 0;
	lol[1] = 1;
	lol[2] = 0;
	shader_programme = glCreateProgram();
	ft_load_shaders(&shader_programme);
	get_vertices_into_vbo(c, points, colours, 0);
	get_faces_into_array(c, ind, lol);
	glGenBuffers(1, &c->points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, c->points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glGenBuffers(1, &c->colours_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, c->colours_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
	glGenBuffers(1, &c->index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
	vao_binding(c);
	game_loop(c, shader_programme);
}

int						main(void)
{
	t_window_context	context;
	int					width;
	int					height;

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return (1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	context.window = glfwCreateWindow(1680, 1260, "Scop", NULL, NULL);
	glfwGetWindowSize(context.window, &width, &height);
	glfwSetWindowAspectRatio(context.window, width, height);
	glfwMakeContextCurrent(context.window);
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	init_structure(&context);
	draw_window(&context);
	glfwTerminate();
	return (0);
}
