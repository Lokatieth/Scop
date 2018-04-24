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
#include <time.h>

void	get_vertex_values(GLuint *dest, GLuint *src, int i, int j)
{
	dest[i] = src[j] - 1;
	dest[i + 1] = src[j + 1] - 1;
	dest[i + 2] = src[j + 2] - 1;
}

void	get_vertex_values2(GLuint *dest, GLuint *src, int i, int j)
{
	dest[i] = src[j] - 1;
	dest[i + 1] = src[j + 2] - 1;
	dest[i + 2] = src[j + 3] - 1;
}

void	schlag2(t_window_context *c, GLuint (r)[c->face_number],
GLuint *d, int *i)
{
	if (ft_get_number_of_words(c->array[i[2]], ' ') == 4 && (i[1] = i[1] + 3))
	{
		sscanf(c->array[i[2]], "f %i %i %i", &r[i[1]],
		&r[i[1] + 1], &r[i[1] + 2]);
		get_vertex_values(d, r, i[0], i[1]);
	}
	else if (ft_get_number_of_words(c->array[i[2]], ' ') == 5 && (i[1] += 4))
	{
		sscanf(c->array[i[2]], "f %i %i %i %i",
		&r[i[1]], &r[i[1] + 1], &r[i[1] + 2], &r[i[1] + 3]);
		get_vertex_values(d, r, i[0], i[1]);
		get_vertex_values2(d, r, i[0] += 3, i[1]);
	}
}

void	get_faces_into_array(t_window_context *c, GLuint *dest, int *i)
{
	GLuint	r[c->face_number];

	c->array = ft_strsplit(c->obj_file, '\n');
	free(c->array[i[2]]);
	while (c->array[i[2]] && c->array[++i[2]])
	{
		if (c->array[i[2]] && c->array[i[2]][0] == 'f' && (i[0] = i[0] + 3))
		{
			schlag2(c, r, dest, i);
		}
		free(c->array[i[2]]);
	}
	c->array[i[2] - 1] = NULL;
	free(c->array);
}
