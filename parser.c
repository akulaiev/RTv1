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

static t_parce	read_file(int fd, t_parce res)
{
	char	*tmp_line;

	tmp_line = NULL;
	res.num_lines = 0;
	while (get_next_line(fd, &tmp_line))
	{
		res.f = ft_realloc_2d(res.f, res.num_lines);
		res.f[res.num_lines] = tmp_line;
		res.num_lines++;
	}
	return (res);
}

t_shape			*parser_help(t_cam **camera, t_data *data,
t_dot **l, t_parce rf)
{
	int		i;

	i = -1;
	while (++i < rf.num_lines)
	{
		if (rf.f[i][0] == '{' && (++i))
		{
			if (rf.f[i][0] == '\t')
			{
				if (!ft_strcmp(&rf.f[i][1], "<window>") && (++i))
					get_win_data(&rf.f[i], data);
				else if (!ft_strcmp(&rf.f[i][1], "<camera>") && (++i))
					get_camera_data(&rf.f[i], *camera);
				else if (!ft_strcmp(&rf.f[i][1], "<lights>") && (++i))
					*l = get_lights(&rf.f[i], -1, data);
				else
					return (get_shapes(&rf.f[i - 1], rf.num_lines - i, data));
			}
			else
				exit(write(2, "Problem with source file!\n", 26));
		}
	}
	return (NULL);
}

void			parser(int fd, t_cam *camera, t_data *data)
{
	t_parce		rf;
	t_shape		*shapes;
	t_dot		*l;

	rf.f = NULL;
	l = NULL;
	rf = read_file(fd, rf);
	data->ww = 0;
	data->wh = 0;
	camera->origin.x = INFINITY;
	camera->basis.dir_vect.x = INFINITY;
	shapes = parser_help(&camera, data, &l, rf);
	if (!data->num_l || !data->num_shapes || !data->ww || !data->wh ||
	camera->origin.x == INFINITY || camera->basis.dir_vect.x == INFINITY)
		exit(write(2, "Problem with source file!\n", 26));
	open_win(data);
	deal_with_threads(data, *camera, shapes, l);
	mlx_put_image_to_window(data->mlx_p, data->mlx_nw, data->mlx_img, 0, 0);
	mlx_loop(data->mlx_p);
	ft_double_free((void**)rf.f, rf.num_lines);
}
