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

void		tex_b(unsigned int w, unsigned int h,
unsigned char *data, GLuint *id)
{
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR,
	GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint		load_bmp(const char *imagepath)
{
	unsigned char	header[54];
	unsigned int	lol[4];
	unsigned char	*data;
	GLuint			texid;
	FILE			*file;

	file = fopen(imagepath, "rb");
	if (!file || (fread(header, 1, 54, file) != 54))
		return (0);
	if (header[0] != 'B' || header[1] != 'M')
		return (0);
	lol[0] = *(int*)&(header[0x0A]);
	lol[3] = *(int*)&(header[0x22]);
	lol[1] = *(int*)&(header[0x12]);
	lol[2] = *(int*)&(header[0x16]);
	if (lol[3] == 0)
		lol[3] = lol[1] * lol[2] * 3;
	if (lol[0] == 0)
		lol[0] = 54;
	data = (unsigned char*)malloc(sizeof(unsigned char) * lol[3] + 1);
	fread(data, 1, lol[3], file);
	fclose(file);
	tex_b(lol[1], lol[2], data, &texid);
	free(data);
	return (texid);
}
