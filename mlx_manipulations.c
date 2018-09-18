/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:12:17 by akulaiev          #+#    #+#             */
/*   Updated: 2018/08/03 14:12:18 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		key_react(int keycode, void *param)
{
	param = NULL;
	if (keycode == 53)
		exit(0);
	return (0);
}

void	open_win(t_data *win)
{
	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->ww, win->wh, "Test");
	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wh);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
}

void		deal_with_threads(t_data *win, t_cam camera, t_sh_lst *shapes, t_l_lst *l)
{
	int			j;
	int			iter;
	t_thread	w[NUM_TH];
	pthread_t	th_id[NUM_TH];

	win->lines_per_th = win->wh / NUM_TH;
	iter = -1;
	j = -1;
	while (++iter < NUM_TH)
	{
		w[iter].current_y = j;
		w[iter].win = win;
		w[iter].camera = camera;
		w[iter].shapes = shapes;
		w[iter].lights = l;
		j += win->lines_per_th;
	}
	iter = -1;
	while (++iter < NUM_TH)
		pthread_create(&th_id[iter], NULL, create_ray, w + iter);
	iter = -1;
	while (++iter < NUM_TH)
		pthread_join(th_id[iter], NULL);
}

void		img_pixel_put(t_data *win, int x, int y, int col)
{
	if (x < win->ww && y < win->wh && x >= 0 && y >= 0)
		*(int*)(win->img_ptr + (x * win->bits_per_pixel / 8 +
		y * win->size_line)) = col;
}