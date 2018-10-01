/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:29:30 by akulaiev          #+#    #+#             */
/*   Updated: 2018/09/21 15:29:32 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	calculate_ray(t_iter it, t_ray *ray, t_thread *t)
{
	it.x_norm = (((it.x + 0.5) / t->win->ww) * 2 - 1) * t->win->ww / t->win->wh;
	it.y_norm = ((it.y + 0.5) / t->win->wh) * 2 - 1;
	ray->vect = va(t->camera.basis.dir_vect,
	va(vm(t->camera.basis.up_vect, it.y_norm),
	vm(t->camera.basis.right_vect, it.x_norm)));
	normalize(&ray->vect);
	ray->origin = t->camera.origin;
}

void	*create_ray(void *w)
{
	t_iter			it;
	t_ray			ray;
	t_thread		*t;
	t_intersection	its;

	t = (t_thread*)w;
	it.y = t->current_y;
	while (++it.y < t->win->wh)
	{
		it.x = -1;
		while (++it.x < t->win->ww)
		{
			calculate_ray(it, &ray, t);
			img_pixel_put(t->win, it.x, it.y,
			get_closest_shape(t, ray, &its));
		}
	}
	pthread_exit(NULL);
}
