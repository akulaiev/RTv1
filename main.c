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
	t_cam	camera;
	t_data	data;

	if (argc != 2)
		return (write(1, "Scene file needed!\n", 19));
	fd = open(argv[1], O_RDONLY);
	parser(fd, &camera, &data, -1);
}
