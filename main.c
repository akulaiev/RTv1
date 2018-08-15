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

t_col	lambert_shading(t_col *constant_col, t_intersection *its)
{
	t_dot	light;
	t_dot	l_vect;
	t_col	col;

	light.x = 10;
	light.y = 10;
	light.z = 5;
	l_vect = vector_add(light, vector_mult(its->ray_point, -1));
	normalize(&l_vect);
	col.struct_col.r = constant_col->struct_col.r * 
	fmax(0, vector_scalar(its->normal, l_vect));
	col.struct_col.g = constant_col->struct_col.g * 
	fmax(0, vector_scalar(its->normal, l_vect));
	col.struct_col.b = constant_col->struct_col.b * 
	fmax(0, vector_scalar(its->normal, l_vect));
	return (col);
}

void	calculate_ray(t_iter it, t_ray *ray, t_thread *t)
{
	it.x_norm = (((it.x + 0.5) / t->win->ww) * 2 - 1) * t->win->ww / t->win->wh;
	it.y_norm = ((it.y + 0.5) / t->win->wh) * 2 - 1;
	ray->vect = vector_add(t->camera.basis.dir_vect, 
	vector_add(vector_mult(t->camera.basis.up_vect, it.y_norm),
	vector_mult(t->camera.basis.right_vect, it.x_norm)));
	normalize(&ray->vect);
	ray->origin = t->camera.origin;
}

void	*create_ray(void *w)
{
	t_iter			it;
	t_ray			ray;
	t_intersection	its;
	t_thread		*t;
	int 			i;

	t = (t_thread*)w;
	it.y = t->current_y;
	while (++it.y < t->win->wh)
	{
		it.x = -1;
		while (++it.x < t->win->ww)
		{
			calculate_ray(it, &ray, t);
			i = -1;
			while (++i < 3)
			{
				if (t->shapes[i].f(t->shapes[i].data, ray, &its))
					img_pixel_put(t->win, it.x, it.y, its.col);
			}
		}
	}
	pthread_exit(NULL);
}

int		main(void)
{
	t_data		data;
	t_cam		camera;
	t_fig		sphere;
	t_fig		plane;
	t_fig		sphere1;
	t_shape		shapes[3];


	data.ww = 950;
	data.wh = 950;
	camera.origin.x = 0;
	camera.origin.y = 0;
	camera.origin.z = 0;

	camera.basis.dir_vect.x = 0;
	camera.basis.dir_vect.y = 0;
	camera.basis.dir_vect.z = 1;
	normalize(&camera.basis.dir_vect);
	camera.basis = get_basis(camera.basis.dir_vect);

	sphere.centre.x = 0;
	sphere.centre.y = 0;
	sphere.centre.z = 5;
	sphere.radius = 1;
	sphere.constant_col.integer = 0xff00c7;

	sphere1.centre.x = -3;
	sphere1.centre.y = 0;
	sphere1.centre.z = 5;
	sphere1.radius = 1;
	sphere1.constant_col.integer = 0x42f4f1;

	plane.centre.x = 0;
	plane.centre.y = -5;
	plane.centre.z = 0;
	plane.normal.x = 0;
	plane.normal.y = 1;
	plane.normal.z = 0;
	plane.constant_col.integer = 0xcccecc;

	shapes[0].data = &sphere;
	shapes[0].f = &sphere_intersection;
	shapes[1].data = &sphere1;
	shapes[1].f = &sphere_intersection;
	shapes[2].data = &plane;
	shapes[2].f = &plane_intersection;

	open_win(&data);
	deal_with_threads(&data, camera, shapes);
	mlx_put_image_to_window(data.mlx_p, data.mlx_nw, data.mlx_img, 0, 0);
	mlx_loop(data.mlx_p);
}
