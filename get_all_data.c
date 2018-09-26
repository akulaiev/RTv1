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
#include <stdio.h>

void			get_win_data(char **lines, t_data *data)
{
	int		i;

	i = -1;
	while (lines[++i] && lines[i][0] != '}')
	{
		if (!strncmp(&lines[i][1], ":width:", 7))
			data->ww = ft_atod(&lines[i][8]);
		else if (!strncmp(&lines[i][1], ":height:", 8))
			data->wh = ft_atod(&lines[i][9]);
	}
}

void			get_camera_data(char **lines, t_cam *camera)
{
	int		i;

	i = -1;
	while (lines[++i] && lines[i][0] != '}')
	{
		if (!strncmp(&lines[i][1], ":origin:", 8))
			i = t_dot_create(&camera->origin, i, lines);
		else if (!strncmp(&lines[i][1], ":direction:", 11))
		{
			i = t_dot_create(&camera->basis.dir_vect, i, lines);
			normalize(&camera->basis.dir_vect);
			camera->basis = get_basis(camera->basis.dir_vect);
		}
	}
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

t_dot			*get_lights(char **lines, t_dot *l, int i, t_data *data)
{
	t_dot	tmp;

	data->num_l = 0;
	while (lines[++i] && lines[i][0] != '}')
	{
		if (lines[i][1] == ':')
		{
			tmp.x = ft_atod(&lines[i + 1][5]);
			tmp.y = ft_atod(&lines[i + 2][5]);
			tmp.z = ft_atod(&lines[i + 3][5]);
			i += 3;
		}
		l = lights_list_create(l, tmp, data);
	}
	return (l);
}
