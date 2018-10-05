/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 15:18:15 by akulaiev          #+#    #+#             */
/*   Updated: 2018/09/17 15:18:17 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				tdc(t_dot *vect, int i, char **lines)
{
	if ((!ft_isdigit(lines[i + 1][6]) && lines[i + 1][6] != '-') ||
	(lines[i + 1][2] != 'x' || lines[i + 2][2] != 'y' ||
	lines[i + 3][2] != 'z'))
		exit(write(2, "Problem with source file: bad coordinates!\n", 43));
	vect->x = ft_atod(&lines[i + 1][5]);
	vect->y = ft_atod(&lines[i + 2][5]);
	vect->z = ft_atod(&lines[i + 3][5]);
	i += 3;
	return (i);
}

void			get_win_data(char **lines, t_data *data)
{
	int		i;

	i = -1;
	data->ww = 0;
	data->wh = 0;
	while (lines[++i] && lines[i][0] != '}')
	{
		if (!strncmp(&lines[i][1], ":width:", 7) && lines[i][0] == '\t')
			data->ww = ft_atod(&lines[i][8]);
		else if (!strncmp(&lines[i][1], ":height:", 8) && lines[i][0] == '\t')
			data->wh = ft_atod(&lines[i][9]);
		else
			exit(write(2, "Problem with source file: reading!\n", 35));
	}
	if (!data->ww || !data->wh)
		exit(write(2, "Problem with source file: no window params!\n", 44));
}

void			get_camera_data(char **lines, t_cam *camera)
{
	int		i;

	i = -1;
	camera->origin.x = INFINITY;
	camera->basis.dir_vect.x = INFINITY;
	while (lines[++i] && lines[i][0] != '}')
	{
		if (!strncmp(&lines[i][1], ":origin:", 8) && lines[i][0] == '\t')
			i = tdc(&camera->origin, i, lines);
		else if (!strncmp(&lines[i][1], ":direction:", 11) &&
		lines[i][0] == '\t')
		{
			i = tdc(&camera->basis.dir_vect, i, lines);
			normalize(&camera->basis.dir_vect);
			camera->basis = get_basis(camera->basis.dir_vect);
		}
		else
			exit(write(2, "Bad camera params!\n", 19));
	}
	if (camera->origin.x == INFINITY || camera->basis.dir_vect.x == INFINITY)
		exit(write(2, "Bad camera params!\n", 19));
}

static t_dot	*lights_list_create(t_dot *l, t_dot tmp, t_data *data)
{
	t_dot	*new;
	int		i;

	new = NULL;
	data->num_l++;
	if (!l && (l = (t_dot*)malloc(sizeof(t_dot))))
	{
		l[data->num_l - 1] = tmp;
		return (l);
	}
	else if ((new = (t_dot*)malloc(sizeof(t_dot) * data->num_l)))
	{
		i = -1;
		while (++i < data->num_l - 1)
			new[i] = l[i];
		new[i] = tmp;
		free(l);
	}
	return (new);
}

t_dot			*get_lights(char **lines, int i, t_data *data)
{
	t_dot	tmp;
	t_dot	*l;

	l = NULL;
	while (lines[++i] && lines[i][0] != '}')
	{
		if (lines[i][1] == ':' && lines[i][0] == '\t')
			i = tdc(&tmp, i, lines);
		else
			exit(write(2, "Problem with source file!\n", 26));
		l = lights_list_create(l, tmp, data);
	}
	return (l);
}
