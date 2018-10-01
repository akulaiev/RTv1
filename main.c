/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:02:09 by akulaiev          #+#    #+#             */
/*   Updated: 2018/07/31 14:02:10 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_cam	camera;
	t_data	data;
	int		c;

	c = 0;
	if (argc != 2)
		return (write(2, "usage: ./RTv1 source_file.rtv\n", 30));
	i = 0;
	while (argv[1][i])
	{
		if ((argv[1][i + 1] == '\0' && !c) || (argv[1][i] == '.'
		&& (c = 1) && ft_strcmp(&argv[1][i + 1], "rtv")))
		{
			write(2, "Wrong source file extension!\n", 29);
			return (write(2, "usage: ./RTv1 source_file.rtv\n", 30));
		}
		i++;
	}
	data.num_l = 0;
	data.num_shapes = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (write(2, "Source file doesn't exist!\n", 27));
	parser(fd, &camera, &data);
}
