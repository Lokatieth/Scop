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

int		check_shader_compilation(GLuint s_i)
{
	int		params;
	int		max_length;
	int		actual_length;
	char	shader_log[2048];

	params = 0;
	max_length = 2048;
	actual_length = 0;
	glGetShaderiv(s_i, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", s_i);
		glGetShaderInfoLog(s_i, max_length, &actual_length, shader_log);
		printf("shader info log for GL index %u:\n%s\n", s_i, shader_log);
		return (0);
	}
	return (1);
}

int		restart_gl_log(void)
{
	FILE	*file;
	time_t	now;
	char	*date;

	file = fopen(GL_LOG_FILE, "w");
	if (!file)
	{
		fprintf(stderr,
		"ERROR: could not open GL_LOG_FILE log file %s for writing\n",
		GL_LOG_FILE);
		return (0);
	}
	now = time(NULL);
	date = ctime(&now);
	fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
	fclose(file);
	return (1);
}

int		gl_log(const char *message, ...)
{
	va_list	argptr;
	FILE	*file;

	file = fopen(GL_LOG_FILE, "a");
	if (!file)
	{
		fprintf(
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending\n",
			GL_LOG_FILE);
		return (0);
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	fclose(file);
	return (1);
}

int		gl_log_err(const char *message, ...)
{
	va_list	argptr;
	FILE	*file;

	file = fopen(GL_LOG_FILE, "a");
	if (!file)
	{
		fprintf(stderr,
		"ERROR: could not open GL_LOG_FILE %s file for appending\n",
		GL_LOG_FILE);
		return (0);
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	fclose(file);
	return (1);
}

void	glfw_error_callback(int error, const char *description)
{
	gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}
