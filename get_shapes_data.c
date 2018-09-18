/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:17:08 by akulaiev          #+#    #+#             */
/*   Updated: 2018/09/18 11:17:09 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>


t_fig		*struct_fig_create(char **lines, char *name)
{
	int		i;
	t_fig	*fig_tmp;

	i = -1;
	if ((fig_tmp = (t_fig*)malloc(sizeof(t_fig))))
	{
		fig_tmp->name = name;
		while (lines[++i] && lines[i][0] != '}')
		{
			if (!strcmp(&lines[i][1], ":centre:"))
			{
				fig_tmp->centre.x = ft_atod(&lines[i + 1][5]);
				fig_tmp->centre.y = ft_atod(&lines[i + 2][5]);
				fig_tmp->centre.z = ft_atod(&lines[i + 3][5]);
				i += 3;
			}
			else if (!strcmp(&lines[i][1], ":normal:"))
			{
				fig_tmp->normal.x = ft_atod(&lines[i + 1][5]);
				fig_tmp->normal.y = ft_atod(&lines[i + 2][5]);
				fig_tmp->normal.z = ft_atod(&lines[i + 3][5]);
				i += 3;
			}
			else if (!strcmp(&lines[i][1], ":direction:"))
			{
				fig_tmp->direction.x = ft_atod(&lines[i + 1][5]);
				fig_tmp->direction.y = ft_atod(&lines[i + 2][5]);
				fig_tmp->direction.z = ft_atod(&lines[i + 3][5]);
				i += 3;
			}
			else if (!strncmp(&lines[i][1], ":radius:", 8))
				fig_tmp->radius = ft_atod(&lines[i][9]);
			else if (!strncmp(&lines[i][1], ":color:", 7))
				fig_tmp->constant_col.integer = ft_atoi_base(&lines[i][11], 16);
			else if (!strncmp(&lines[i][1], ":angle:", 7))
				fig_tmp->angle = ft_atod(&lines[i][9]);
		}
	}
	return (fig_tmp);
}

static t_sh_lst		*shapes_list_create(t_sh_lst *shapes, t_fig *fig_tmp,
int (*funct)(t_fig *shape_type, t_ray ray, t_intersection *its))
{
	t_sh_lst *new;
	t_sh_lst *temp;

	new = NULL;
	if (!shapes && (shapes = (t_sh_lst*)malloc(sizeof(t_sh_lst))))
	{
		shapes->data = (void*)fig_tmp;
		shapes->f = funct;
		shapes->next = NULL;
	}
	else if (shapes && (new = (t_sh_lst*)malloc(sizeof(t_sh_lst))))
	{
		new->data = (void*)fig_tmp;
		new->f = funct;
		new->next = NULL;
		temp = shapes;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (shapes);
}

t_sh_lst	*get_shapes(char **full_file, int num_lines, t_sh_lst *shapes, int i)
{
	int 		(*funct)(t_fig *shape_type, t_ray ray, t_intersection *its);
	char		*name;

	name = NULL;
	while (++i < num_lines)
	{
		if (full_file[i][0] == '{' && (++i))
		{
			if (!ft_strcmp(&full_file[i][1], "<sphere>")
			&& (name = ft_strdup("sphere")))
				funct = &sphere_intersection;
			else if (!ft_strcmp(&full_file[i][1], "<plane>")
			&& (name = ft_strdup("plane")))
				funct = &plane_intersection;
			else if (!ft_strcmp(&full_file[i][1], "<cylinder>")
			&& (name = ft_strdup("cylinder")))
				funct = &cylinder_intersection;
			else if (!ft_strcmp(&full_file[i][1], "<cone>")
			&& (name = ft_strdup("cone")))
				funct = &cone_intersection;
			shapes = shapes_list_create(shapes, struct_fig_create(&full_file[i], name), funct);
		}
	}
	return (shapes);
}
