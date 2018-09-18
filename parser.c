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
		res.full_file = ft_realloc_2d(res.full_file, res.num_lines);
		res.full_file[res.num_lines] = tmp_line;
		res.num_lines++;
	}
	return (res);
}

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
			else if (!strcmp(&lines[i][1], ":radius:"))
				fig_tmp->radius = ft_atod(&lines[i][9]);
			else if (!strcmp(&lines[i][1], ":color:"))
				fig_tmp->constant_col.integer = ft_atoi_base(&lines[i + 1][9], 16);
			else if (!strcmp(&lines[i][1], ":angle:"))
				fig_tmp->angle = ft_atod(&lines[i + 1][9]);
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

t_sh_lst	*get_shapes(char **full_file, int num_lines)
{	
	printf("\nhere\n");
	t_sh_lst	*shapes;
	int			i;

	i = -1;
	while (++i < num_lines)
	{
		if (full_file[i][0] == '{' && (++i))
		{
			if (!ft_strcmp(&full_file[i][1], "<sphere>") && (i++))
				shapes = shapes_list_create(shapes, struct_fig_create(&full_file[i], "sphere"), &sphere_intersection);
			else if (!ft_strcmp(&full_file[i][1], "<plane>") && (i++))
				shapes = shapes_list_create(shapes, struct_fig_create(&full_file[i], "plane"), &plane_intersection);
			else if (!ft_strcmp(&full_file[i][1], "<cylinder>") && (i++))
				shapes = shapes_list_create(shapes, struct_fig_create(&full_file[i], "cylinder"), &cylinder_intersection);
			else if (!ft_strcmp(&full_file[i][1], "<cone>") && (i++))
				shapes = shapes_list_create(shapes, struct_fig_create(&full_file[i], "cone"), &cone_intersection);
		}
	}
	return (shapes);
}

void		parser(int fd, t_cam *camera, t_data *data)
{
	t_parce		rf;
	t_sh_lst	*shapes;
	int			i;
	t_l_lst		*l;

	rf.full_file = NULL;
	l = NULL;
	rf = read_file(fd, rf);
	i = -1;
	while (++i < rf.num_lines)
	{
		if (rf.full_file[i][0] == '{' && (++i))
		{
			if (!ft_strcmp(&rf.full_file[i][1], "<window>") && (++i))
				get_win_data(&rf.full_file[i], data);
			else if (!ft_strcmp(&rf.full_file[i][1], "<camera>") && (++i))
				get_camera_data(&rf.full_file[i], camera);
			else if (!ft_strcmp(&rf.full_file[i][1], "<lights>") && (++i))
				l = get_lights(&rf.full_file[i], l, -1);
			else
				shapes = get_shapes(&rf.full_file[i], rf.num_lines);
		}
	}
	ft_double_free((void**)rf.full_file, 80);
}
