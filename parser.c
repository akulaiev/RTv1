/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:20:22 by akulaiev          #+#    #+#             */
/*   Updated: 2018/09/17 11:20:24 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static char		**ft_realloc_2d(char **lines, int num_lines)
{
	char	**new_mem;
	int		i;

	if (!lines || !num_lines)
		return ((char**)ft_memalloc(sizeof(char*)));
	new_mem = (char**)ft_memalloc(sizeof(char*) * num_lines + 1);
	i = -1;
	while (++i < num_lines)
		new_mem[i] = lines[i];
	free(lines);
	return (new_mem);
}

static char		**read_file(int fd)
{
	char	*tmp_line;
	int		num_lines;
	char	**full_file;

	tmp_line = NULL;
	num_lines = 0;
	while (get_next_line(fd, &tmp_line))
	{
		full_file = ft_realloc_2d(full_file, num_lines);
		full_file[num_lines] = tmp_line;
		num_lines++;
	}
	return (full_file);
}

void		parser(int fd, t_cam *camera, t_data *data)
{
	char	**full_file;
	int		i;
	t_l_lst	*l;

	full_file = NULL;
	l = NULL;
	full_file = read_file(fd);
	i = -1;
	while (++i < 80)
	{
		if (full_file[i][0] == '{' && (++i))
		{
			if (!ft_strcmp(&full_file[i][1], "<window>") && (++i))
				get_win_data(&full_file[i], data);
			if (!ft_strcmp(&full_file[i][1], "<camera>") && (++i))
				get_camera_data(&full_file[i], camera);
			if (!ft_strcmp(&full_file[i][1], "<lights>") && (++i))
				l = get_lights(&full_file[i], l, -1);
		}
	}
	ft_double_free((void**)full_file, 80);
}
