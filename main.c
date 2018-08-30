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

t_col	blinn_phong_shading(t_col *constant_col, t_intersection *its, t_thread *t)
{
	t_shd	s;

	s.tmp_r = 0;
	s.tmp_g = 0;
	s.tmp_b = 0;
	s.i = -1;
	s.v_vect = vector_add(t->camera.origin, vector_mult(its->ray_point, -1));
		normalize(&s.v_vect);
	while (++s.i < t->lights.num_l)
	{
		s.l_vect[s.i] = vector_add(t->lights.lts[s.i], vector_mult(its->ray_point, -1));
		normalize(&s.l_vect[s.i]);
		s.h_vect[s.i] = vector_add(s.l_vect[s.i], s.v_vect);
		normalize(&s.h_vect[s.i]);
		s.nl = fmax(0, vector_scalar(its->normal, s.l_vect[s.i]));
		s.hl = fmax(0, pow(vector_scalar(its->normal, s.h_vect[s.i]), 100));
		s.tmp_r += constant_col->struct_col.r * s.nl + 131 * s.hl;
		s.tmp_g += constant_col->struct_col.g * s.nl + 131 * s.hl;
		s.tmp_b += constant_col->struct_col.b * s.nl + 131 * s.hl;
	}
	s.tmp_r > 0xFF ? (s.col.struct_col.r = 0xFF) : (s.col.struct_col.r = s.tmp_r);
	s.tmp_g > 0xFF ? (s.col.struct_col.g = 0xFF) : (s.col.struct_col.g = s.tmp_g);
	s.tmp_b > 0xFF ? (s.col.struct_col.b = 0xFF) : (s.col.struct_col.b = s.tmp_b);
	return (s.col);
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

int		main(void)
{
	t_data		data;
	t_cam		camera;
	t_fig		sphere;
	t_fig		plane;
	t_fig		sphere1;
	t_fig		sphere2;
	t_shape		shapes[4];
	t_light		l;
	t_fig		cylinder;


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

	l.lts[0].x = -3;
	l.lts[0].y = 10;
	l.lts[0].z = 5;
	l.lts[1].x = 3;
	l.lts[1].y = 10;
	l.lts[1].z = -5;
	l.lts[2].x = 1;
	l.lts[2].y = -1;
	l.lts[2].z = 1;
	l.num_l = 3;
	sphere.centre.x = 0;
	sphere.centre.y = -1;
	sphere.centre.z = 5;
	sphere.radius = 1;
	sphere.constant_col.integer = 0xff00c7;
	sphere.name = "sphere";

	sphere1.centre.x = -3;
	sphere1.centre.y = -1;
	sphere1.centre.z = 5;
	sphere1.radius = 1;
	sphere1.constant_col.integer = 0x42f4f1;
	sphere1.name = "sphere";

	sphere2.centre.x = -2;
	sphere2.centre.y = -1;
	sphere2.centre.z = 7;
	sphere2.radius = 1;
	sphere2.constant_col.integer = 0xf4d142;
	sphere2.name = "sphere";

	plane.centre.x = 0;
	plane.centre.y = -5;
	plane.centre.z = 0;
	plane.normal.x = 0;
	plane.normal.y = 1;
	plane.normal.z = 0;
	plane.constant_col.integer = 0xcccecc;
	plane.name = "plane";

	cylinder.centre.x = 0;
	cylinder.centre.y = 0;
	cylinder.centre.z = 0;
	cylinder.va.x = 0;
	cylinder.va.y = 0;
	cylinder.va.z = 1;
	cylinder.radius = 1;
	cylinder.constant_col.integer = 0xadf442;
	cylinder.name = "cylinder";

	shapes[0].data = &sphere;
	shapes[0].f = &sphere_intersection;
	shapes[1].data = &sphere1;
	shapes[1].f = &sphere_intersection;
	shapes[2].data = &plane;
	shapes[2].f = &plane_intersection;
	shapes[3].data = &sphere2;
	shapes[3].f = &sphere_intersection;
	// shapes[4].data = &cylinder;
	// shapes[4].f = &cylinder_intersection;

	// shapes[0].data = &cylinder;
	// shapes[0].f = &cylinder_intersection;

	open_win(&data);
	deal_with_threads(&data, camera, shapes, l);
	mlx_put_image_to_window(data.mlx_p, data.mlx_nw, data.mlx_img, 0, 0);
	mlx_loop(data.mlx_p);
}
