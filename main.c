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

void	lambert_shading(t_sph *sphere, t_intersection its)
{
	t_dot	light;
	t_dot	l_vect;

	light.x = 10;
	light.y = 10;
	light.z = 5;
	l_vect = vector_add(light, vector_mult(its.ray_point, -1));
	normalize(&l_vect);
	sphere->col.struct_col.r = sphere->constant_col.struct_col.r * 
	fmax(0, vector_scalar(its.normal, l_vect));
	sphere->col.struct_col.g = sphere->constant_col.struct_col.g * 
	fmax(0, vector_scalar(its.normal, l_vect));
	sphere->col.struct_col.b = sphere->constant_col.struct_col.b * 
	fmax(0, vector_scalar(its.normal, l_vect));
}

void	lambert_shading_pl(t_pln *sphere, t_intersection its)
{
	t_dot	light;
	t_dot	l_vect;

	light.x = 10;
	light.y = 10;
	light.z = 5;
	l_vect = vector_add(light, vector_mult(its.ray_point, -1));
	normalize(&l_vect);
	sphere->col.struct_col.r = sphere->constant_col.struct_col.r * 
	fmax(0, vector_scalar(its.normal, l_vect));
	sphere->col.struct_col.g = sphere->constant_col.struct_col.g * 
	fmax(0, vector_scalar(its.normal, l_vect));
	sphere->col.struct_col.b = sphere->constant_col.struct_col.b * 
	fmax(0, vector_scalar(its.normal, l_vect));
}

int		get_intersection(t_sph *sphere, t_ray ray) //sphere
{
	double			p1;
	double			p2;
	t_dot			e_min_c;
	t_intersection	its;

	e_min_c = vector_add(ray.origin, vector_mult(sphere->centre, -1));
	p1 = vector_scalar(ray.vect, e_min_c);
	p1 *= p1;
	p2 = vector_scalar(e_min_c, e_min_c) - (sphere->radius * sphere->radius);
	its.d = p1 - p2;
	if (its.d < 0)
		return (0);
	else
	{
		// ray.t1 = vector_scalar(vector_mult(ray.vect, -1), e_min_c) + sqrt(d);
		its.t = vector_scalar(vector_mult(ray.vect, -1), e_min_c) - sqrt(its.d);
		its.ray_point = vector_add(ray.origin, vector_mult(ray.vect, its.t));
		its.normal = vector_divide(vector_add(its.ray_point,
		vector_mult(sphere->centre, -1)), sphere->radius);
		normalize(&its.normal);
		lambert_shading(sphere, its);
		return (1);
	}
}

int		get_intersection_plane(t_pln *plane, t_ray ray) //plane
{
	double			denom;
	t_intersection	its;
	t_dot			diff;

	denom = vector_scalar(plane->normal, ray.vect);
	if (fabs(denom) > 0.0001)
	{
		diff = vector_add(plane->centre, vector_mult(ray.origin, -1));
		its.t = vector_scalar(diff, plane->normal) / denom;
		if (its.t > 0.0001)
		{
			its.normal = plane->normal;
			// lambert_shading_pl(plane, its);
			return (1);
		}
	}
	return (0);
}

void	create_ray(t_data *data, t_cam camera, void *figure, int type)
{
	int		x;
	int		y;
	double	x_norm;
	double	y_norm;
	t_ray	ray;

	y = -1;
	while (++y < data->wh)
	{
		x = -1;
		while (++x < data->ww)
		{
			x_norm = (((x + 0.5) / data->ww) * 2 - 1) * data->ww / data->wh;
			y_norm = ((y + 0.5) / data->wh) * 2 - 1;
			ray.vect = vector_add(camera.basis.dir_vect, 
			vector_add(vector_mult(camera.basis.up_vect, y_norm),
			vector_mult(camera.basis.right_vect, x_norm)));
			normalize(&ray.vect);
			ray.origin = camera.origin;
			if (type == 1 && get_intersection((t_sph*)figure, ray))
				mlx_pixel_put(data->mlx_p, data->mlx_nw, x, y, ((t_sph*)figure)->col.integer);
			else if (type == 0 && get_intersection_plane((t_pln*)figure, ray))
			{
				((t_pln*)figure)->col.integer = ((t_pln*)figure)->constant_col.integer;
				mlx_pixel_put(data->mlx_p, data->mlx_nw, x, y, ((t_pln*)figure)->col.integer);
			}
			// else
			// 	mlx_pixel_put(data->mlx_p, data->mlx_nw, x, y, 0xe2b7d9);
		}
	}
}

int		main(void)
{
	t_data		data;
	t_cam		camera;
	t_sph		sphere;
	t_pln		plane;
	// t_sph		sphere1;


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

	// sphere1.centre.x = -3;
	// sphere1.centre.y = 0;
	// sphere1.centre.z = 5;
	// sphere1.radius = 1;
	// sphere1.constant_col.integer = 0x42f4f1;

	plane.centre.x = 0;
	plane.centre.y = 0;
	plane.centre.z = 9;
	t_base tmp = get_basis(plane.centre);
	plane.normal = tmp.up_vect;
	plane.constant_col.integer = 0xeef441;

	open_win(&data);
	create_ray(&data, camera, (void*)&plane, 0);
	create_ray(&data, camera, (void*)&sphere, 1);
	// create_ray(&data, camera, &sphere1);
	mlx_loop(data.mlx_p);
}
