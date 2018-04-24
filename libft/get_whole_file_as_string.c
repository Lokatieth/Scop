/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:30:33 by vbauguen          #+#    #+#             */
/*   Updated: 2016/02/16 12:57:53 by vbauguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_whole_file_as_string(char *path)
{
	char				*rest;
	int					fd;
	char				buffer[BUFF_SIZE];
	int					ret;

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		rest = ft_strnew(1);
	}
	else
	{
		ft_putendl("There was an error opening this file.");
		exit(0);
	}
	while (fd >= 0 && fd < 256 && (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		rest = ft_strjoinopt(rest, buffer);
	}
	close(fd);
	return (rest);
}
