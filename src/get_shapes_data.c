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

static int			struct_fig_create_help(char **l, int i, t_fig *f)
{
	if (l[i][0] == '\t' && !ft_strcmp(&l[i][1], ":centre:"))
		i = tdc(&f->centre, i, l);
	else if (l[i][0] == '\t' && !ft_strcmp(&l[i][1], ":normal:") &&
	(i = tdc(&f->normal, i, l)))
		normalize(&f->normal);
	else if (l[i][0] == '\t' && !ft_strcmp(&l[i][1], ":direction:") &&
	(i = tdc(&f->dir, i, l)))
		normalize(&f->dir);
	else if (l[i][0] == '\t' && !ft_strncmp(&l[i][1], ":radius:", 8))
		f->radius = ft_atod(&l[i][9]);
	else if (l[i][0] == '\t' && !ft_strncmp(&l[i][1], ":color:", 7))
		f->constant_col.integer = ft_atoi_base(&l[i][11], 16);
	else if (l[i][0] == '\t' && !ft_strncmp(&l[i][1], ":angle:", 7))
		f->angle = ft_atod(&l[i][9]);
	else
	{
		free(f);
		exit(write(2, "Bad shapes' parameters names!\n", 30));
	}
	return (i);
}

static t_fig		*struct_fig_create(char **l, char *name, int i)
{
	t_fig	*f;

	if ((f = (t_fig*)malloc(sizeof(t_fig))))
	{
		f->angle = 0;
		f->radius = 0;
		f->constant_col.integer = 0;
		f->name = name;
		f->centre.x = INFINITY;
		f->normal.x = INFINITY;
		f->dir.x = INFINITY;
		while (l[++i] && l[i][0] != '}')
			i = struct_fig_create_help(l, i, f);
	}
	if (!f->constant_col.integer || f->centre.x == INFINITY ||
	(!ft_strcmp(name, "cone") && !f->angle) || ((!ft_strcmp(name, "cylinder")
	|| !ft_strcmp(name, "sphere")) && !f->radius) ||
	((!ft_strcmp(name, "cylinder") || !ft_strcmp(name, "cone"))
	&& f->dir.x == INFINITY) ||
	(!ft_strcmp(name, "plane") && f->normal.x == INFINITY))
	{
		free(f);
		exit(write(2, "Bad shapes' parameters!\n", 24));
	}
	return (f);
}

static t_shape		*shapes_list_create(t_shape *shapes, t_fig *fig_tmp,
int (*funct)(t_fig *shape_type, t_ray ray, t_intersection *its), t_data *data)
{
	t_shape *new;
	int		i;

	new = NULL;
	data->num_shapes++;
	if (!shapes && (shapes = (t_shape*)malloc(sizeof(t_shape))))
	{
		shapes[data->num_shapes - 1].data = (void*)fig_tmp;
		shapes[data->num_shapes - 1].f = funct;
		return (shapes);
	}
	else if ((new = (t_shape*)malloc(sizeof(t_shape) * data->num_shapes)))
	{
		i = -1;
		while (++i < data->num_shapes - 1)
		{
			new[i].data = shapes[i].data;
			new[i].f = shapes[i].f;
		}
		new[i].data = (void*)fig_tmp;
		new[i].f = funct;
		free(shapes);
	}
	return (new);
}

static void			get_shapes_help(char **f, int i, char **name,
int (**funct)(t_fig *shape_type, t_ray ray, t_intersection *its))
{
	if (f[i][0] == '\t' && !ft_strcmp(&f[i][1], "<sphere>")
	&& (*name = ft_strdup("sphere")))
		*funct = &sphere_intersection;
	else if (f[i][0] == '\t' && !ft_strcmp(&f[i][1], "<plane>")
	&& (*name = ft_strdup("plane")))
		*funct = &plane_intersection;
	else if (f[i][0] == '\t' && !ft_strcmp(&f[i][1], "<cylinder>")
	&& (*name = ft_strdup("cylinder")))
		*funct = &cylinder_intersection;
	else if (f[i][0] == '\t' && !ft_strcmp(&f[i][1], "<cone>")
	&& (*name = ft_strdup("cone")))
		*funct = &cone_intersection;
	else
		exit(write(2, "Problem with source file: shapes' names!\n", 41));
}

t_shape				*get_shapes(char **full_file, int num_lines,
t_data *data)
{
	int			(*funct)(t_fig *shape_type, t_ray ray, t_intersection *its);
	char		*name;
	int			i;
	t_shape		*shapes;

	name = NULL;
	funct = NULL;
	shapes = NULL;
	i = -1;
	while (++i < num_lines)
	{
		if (full_file[i][0] == '{' && (++i))
		{
			get_shapes_help(full_file, i, &name, &funct);
			shapes = shapes_list_create(shapes,
			struct_fig_create(&full_file[i], name, 0), funct, data);
		}
	}
	return (shapes);
}
