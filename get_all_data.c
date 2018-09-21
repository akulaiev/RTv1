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
	while (lines[++i]  && lines[i][0] != '}')
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

static t_l_lst		*lights_list_create(t_l_lst *l, t_dot tmp, t_data *data)
{
	t_l_lst *new;
	t_l_lst *temp;

	new = NULL;
	data->num_l++;
	if (!l && (l = (t_l_lst*)malloc(sizeof(t_l_lst))))
	{
		l->light_coord = tmp;
		l->next = NULL;
	}
	else if (l && (new = (t_l_lst*)malloc(sizeof(t_l_lst))))
	{
		new->light_coord = tmp;
		new->next = NULL;
		temp = l;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (l);
}

t_l_lst			*get_lights(char **lines, t_l_lst *l, int i, t_data *data)
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