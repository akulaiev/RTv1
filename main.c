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
	t_shd			s;
	int				i;
	double			light_len;
	t_intersection	its1;

	s.tmp_r = 0;
	s.tmp_g = 0;
	s.tmp_b = 0;
	s.i = -1;
	s.v_vect = vector_minus(t->camera.origin, its->ray_point);
	normalize(&s.v_vect);
	while (++s.i < t->lights.num_l)
	{
		s.l_vect[s.i].origin.x = its->ray_point.x;
		s.l_vect[s.i].origin.y = its->ray_point.y;
		s.l_vect[s.i].origin.z = its->ray_point.z;
		s.l_vect[s.i].vect = vector_minus(t->lights.lts[s.i], s.l_vect[s.i].origin);
		light_len = sqrt(s.l_vect[s.i].vect.x * s.l_vect[s.i].vect.x + s.l_vect[s.i].vect.y *
		s.l_vect[s.i].vect.y + s.l_vect[s.i].vect.z * s.l_vect[s.i].vect.z);
		normalize(&s.l_vect[s.i].vect);
		i = -1;
		while (++i < 4)
		{
			if (t->shapes[i].f(t->shapes[i].data, s.l_vect[s.i], &its1) && light_len > its1.t)
			{
				s.col.integer = 0;
				return (s.col);
			}
		}
		s.h_vect[s.i] = vector_add(s.l_vect[s.i].vect, s.v_vect);
		normalize(&s.h_vect[s.i]);
		s.nl = fmax(0, vector_scalar(its->normal, s.l_vect[s.i].vect));
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
	t_fig		cone;
	t_shape		shapes[2];
	t_light		l;
	t_fig		cylinder;


	data.ww = 950;
	data.wh = 950;

	camera.origin.x = 5;
	camera.origin.y = -20;
	camera.origin.z = 10;
	camera.basis.dir_vect.x = -1;
	camera.basis.dir_vect.y = 5;
	camera.basis.dir_vect.z = -1;
	normalize(&camera.basis.dir_vect);
	camera.basis = get_basis(camera.basis.dir_vect);

	l.lts[0].x = 5;
	l.lts[0].y = -6;
	l.lts[0].z = 5;
	l.lts[1].x = -5;
	l.lts[1].y = -6;
	l.lts[1].z = 1;
	l.num_l = 1;

	sphere.centre.x = -2;
	sphere.centre.y = -3;
	sphere.centre.z = 3;
	sphere.radius = 3;
	sphere.constant_col.integer = 0x42f489;
	sphere.name = "sphere";

	plane.centre.x = 3;
	plane.centre.y = 0;
	plane.centre.z = 0;
	plane.normal.x = 0;
	plane.normal.y = 0;
	plane.normal.z = 10;
	normalize(&plane.normal);
	plane.constant_col.integer = 0xcccecc;
	plane.name = "plane";

	cylinder.centre.x = 3;
	cylinder.centre.y = 7;
	cylinder.centre.z = 1;
	cylinder.direction.x = 6;
	cylinder.direction.y = 2;
	cylinder.direction.z = -10;
	normalize(&cylinder.direction);
	cylinder.radius = 5;
	cylinder.constant_col.integer = 0x4161f4;
	cylinder.name = "cylinder";

	cone.centre.x = 5;
	cone.centre.y = 1;
	cone.centre.z = 1;
	cone.direction.x = -5;
	cone.direction.y = 1;
	cone.direction.z = -9;
	normalize(&cone.direction);
	cone.angle = 0.25;
	cone.constant_col.integer = 0xf441a6;
	cone.name = "cone";

	shapes[0].data = &sphere;
	shapes[0].f = &sphere_intersection;
	shapes[1].data = &plane;
	shapes[1].f = &plane_intersection;
	shapes[2].data = &cylinder;
	shapes[2].f = &cylinder_intersection;
	shapes[3].data = &cone;
	shapes[3].f = &cone_intersection;

	open_win(&data);
	deal_with_threads(&data, camera, shapes, l);
	mlx_put_image_to_window(data.mlx_p, data.mlx_nw, data.mlx_img, 0, 0);
	mlx_loop(data.mlx_p);
}
