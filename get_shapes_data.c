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

int		t_dot_create(t_dot *vect, int i, char **lines)
{
	vect->x = ft_atod(&lines[i + 1][5]);
	vect->y = ft_atod(&lines[i + 2][5]);
	vect->z = ft_atod(&lines[i + 3][5]);
	i += 3;
	return (i);
}

t_fig		*struct_fig_create(char **lines, char *name, int i)
{
	t_fig	*fig_tmp;

	if ((fig_tmp = (t_fig*)malloc(sizeof(t_fig))))
	{
		fig_tmp->name = name;
		while (lines[++i] && lines[i][0] != '}')
		{
			if (!strcmp(&lines[i][1], ":centre:"))
				i = t_dot_create(&fig_tmp->centre, i, lines);
			else if (!strcmp(&lines[i][1], ":normal:") &&
			(i = t_dot_create(&fig_tmp->normal, i, lines)))
				normalize(&fig_tmp->normal);
			else if (!strcmp(&lines[i][1], ":direction:") &&
			(i = t_dot_create(&fig_tmp->direction, i, lines)))
				normalize(&fig_tmp->direction);
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
			shapes = shapes_list_create(shapes, struct_fig_create(&full_file[i], name, -1), funct);
		}
	}
	return (shapes);
}
