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

double	rand_in_range(double min, double max)
{
	return (min + (double)(rand() / (double)(RAND_MAX) * (max - min)));
}

void	fill_min_max(float *dest, float *minmax, int i)
{
	if (dest[i] > minmax[0])
		minmax[0] = dest[i];
	else if (dest[i] < minmax[3])
		minmax[3] = dest[i];
	if (dest[i + 1] > minmax[1])
		minmax[1] = dest[i + 1];
	else if (dest[i + 1] < minmax[4])
		minmax[4] = dest[i + 1];
	if (dest[i + 2] > minmax[2])
		minmax[2] = dest[i + 2];
	else if (dest[i + 2] < minmax[5])
		minmax[5] = dest[i + 2];
}

void	align_rotation_axis(float *dest, float *minmax, int i)
{
	while (i >= 0)
	{
		dest[i] = dest[i] - (minmax[0] + minmax[3]) / 2;
		dest[i + 1] = dest[i + 1] - (minmax[1] + minmax[4]) / 2;
		dest[i + 2] = dest[i + 2] - (minmax[2] + minmax[5]) / 2;
		i -= 3;
	}
}

void	fill_colors(float *d, float *r, float *col, int i)
{
	d[i] = r[i];
	d[i + 1] = r[i + 1];
	d[i + 2] = r[i + 2];
	col[i] = rand_in_range(0.2, 0.8);
	col[i + 1] = col[i];
	col[i + 2] = col[i];
}

void	get_vertices_into_vbo(t_window_context *c, float *d, float *col, int i)
{
	char	**array;
	float	minmax[6];
	float	r[c->vertex_number];
	int		j;

	j = 0;
	ft_bzero(minmax, sizeof(float) * 6);
	array = ft_strsplit(c->obj_file, '\n');
	free(array[j]);
	array[j] = NULL;
	while (array[++j])
	{
		if ((array[j] && ft_strstr(array[j], "v ") != 0))
		{
			sscanf(array[j], "v %f %f %f", &r[i], &r[i + 1], &r[i + 2]);
			fill_colors(d, r, col, i);
			fill_min_max(d, minmax, i);
			i += 3;
		}
		ft_strdel(&array[j]);
	}
	free(array);
	align_rotation_axis(d, minmax, i);
}
