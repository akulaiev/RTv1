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
	shapes = NULL;
	while (++i < rf.num_lines && !shapes)
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
				shapes = get_shapes(&rf.full_file[i - 1], rf.num_lines - i, shapes, -1);
		}
	}
	t_sh_lst	*test = shapes;
	while (test)
	{
		printf("%s\n", ((t_fig*)test->data)->name);
		printf("%#x\n", ((t_fig*)test->data)->constant_col.integer);
		test = test->next;
	}
	printf("\n");
	t_l_lst *test1 = l;
	while (test1)
	{
		printf("%f %f %f\n", test1->light_coord.x, test1->light_coord.y, test1->light_coord.z);
		test1 = test1->next;
	}
	ft_double_free((void**)rf.full_file, 80);
}
