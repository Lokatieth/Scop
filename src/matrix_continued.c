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

double	rtod(double radian)
{
	return (radian / (PI * 180));
}

double	dtor(double degree)
{
	return (degree * PI / 180);
}

void	rotate_mat4_y(float *c, float *a, float t)
{
	GLfloat matrot[16];

	matrot[0] = cos(t);
	matrot[1] = 0;
	matrot[2] = -sin(t);
	matrot[3] = 0;
	matrot[4] = 0;
	matrot[5] = 1;
	matrot[6] = 0;
	matrot[7] = 0;
	matrot[8] = sin(t);
	matrot[9] = 0;
	matrot[10] = cos(t);
	matrot[11] = 0;
	matrot[12] = 0;
	matrot[13] = 0;
	matrot[14] = 0;
	matrot[15] = 1;
	multiply_mat4(c, a, matrot);
}

void	translate_mat4(float *c, float x, float y, float z)
{
	GLfloat matrot[16];

	matrot[0] = 1;
	matrot[1] = 0;
	matrot[2] = 0;
	matrot[3] = 0;
	matrot[4] = 0;
	matrot[5] = 1;
	matrot[6] = 0;
	matrot[7] = 0;
	matrot[8] = 0;
	matrot[9] = 0;
	matrot[10] = 1;
	matrot[11] = 0;
	matrot[12] = x;
	matrot[13] = y;
	matrot[14] = z;
	matrot[15] = 1;
	multiply_mat4(c, c, matrot);
}
