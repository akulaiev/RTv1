/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:36:23 by akulaiev          #+#    #+#             */
/*   Updated: 2018/08/07 11:36:25 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		get_closest_shape(t_thread *t, t_ray ray, t_intersection *its)
{
	int			col;
	int			i;
	t_shape		*temp;

	its->closest_t = INFINITY;
	col = 0;
	temp = t->shapes;
	i = -1;
	while (++i < t->win->num_shapes)
	{
		if (temp[i].f(temp[i].data, ray, its) && its->t < its->closest_t)
		{
			col = get_its_params((*(t_fig*)temp[i].data), ray, its, t).integer;
			its->closest_t = its->t;
		}
	}
	return (col);
}

int		cylinder_intersection(t_fig *cy, t_ray ray, t_intersection *its)
{
	t_cy	c;

	c.delta_p = vmn(ray.origin, cy->centre);
	c.tmp = vmn(ray.dir_vect, vm(cy->dir, vs(ray.dir_vect, cy->dir)));
	c.tmp1 = vmn(c.delta_p, vm(cy->dir, vs(c.delta_p, cy->dir)));
	c.a = vs(c.tmp, c.tmp);
	c.b = 2 * vs(c.tmp, c.tmp1);
	c.c = vs(c.tmp1, c.tmp1) - (cy->radius * cy->radius);
	its->d = pow(c.b, 2) - 4 * c.a * c.c;
	if (its->d < 0 || (c.a == 0 && c.b == 0))
		return (0);
	its->t0 = (-c.b - sqrt(its->d)) / (2 * c.a);
	its->t1 = (-c.b + sqrt(its->d)) / (2 * c.a);
	if (its->t0 > 0.00001 && its->t1 > 0.00001)
		its->t = fmin(its->t0, its->t1);
	else
		its->t = fmax(its->t0, its->t1);
	return (its->t > 0.00001);
}

int		cone_intersection(t_fig *co, t_ray ray, t_intersection *its)
{
	t_cy	c;

	c.delta_p = vmn(ray.origin, co->centre);
	c.tmp = vmn(ray.dir_vect, vm(co->dir, vs(ray.dir_vect, co->dir)));
	c.tmp1 = vmn(c.delta_p, vm(co->dir, vs(c.delta_p, co->dir)));
	c.a = pow(cos(co->angle), 2) * vs(c.tmp, c.tmp) -
	pow(sin(co->angle), 2) * pow(vs(ray.dir_vect, co->dir), 2);
	c.b = 2 * pow(cos(co->angle), 2) * vs(c.tmp, c.tmp1) -
	2 * pow(sin(co->angle), 2) *
	vs(ray.dir_vect, co->dir) * vs(c.delta_p, co->dir);
	c.c = pow(cos(co->angle), 2) * vs(c.tmp1, c.tmp1)
	- (co->radius * co->radius) -
	pow(sin(co->angle), 2) * pow(vs(c.delta_p, co->dir), 2);
	its->d = pow(c.b, 2) - 4 * c.a * c.c;
	if (its->d < 0 || (c.a == 0 && c.b == 0))
		return (0);
	its->t0 = (-c.b - sqrt(its->d)) / (2 * c.a);
	its->t1 = (-c.b + sqrt(its->d)) / (2 * c.a);
	if (its->t0 > 0.00001 && its->t1 > 0.00001)
		its->t = fmin(its->t0, its->t1);
	else
		its->t = fmax(its->t0, its->t1);
	return (its->t > 0.00001);
}

int		sphere_intersection(t_fig *sphere, t_ray ray, t_intersection *its)
{
	double			p1;
	double			p2;
	t_dot			e_min_c;

	e_min_c = vmn(ray.origin, sphere->centre);
	p1 = vs(ray.dir_vect, e_min_c);
	p1 *= p1;
	p2 = vs(ray.dir_vect, ray.dir_vect) *
	vs(e_min_c, e_min_c) - (sphere->radius * sphere->radius);
	its->d = p1 - p2;
	if (its->d < 0)
		return (0);
	else
	{
		its->t0 = (vs(vm(ray.dir_vect, -1), e_min_c) + sqrt(its->d))
		/ vs(ray.dir_vect, ray.dir_vect);
		its->t1 = (vs(vm(ray.dir_vect, -1), e_min_c) - sqrt(its->d))
		/ vs(ray.dir_vect, ray.dir_vect);
		if (its->t0 > 0.00001 && its->t1 > 0.00001)
			its->t = fmin(its->t0, its->t1);
		else
			its->t = fmax(its->t0, its->t1);
		return (its->t > 0.00001);
	}
}

int		plane_intersection(t_fig *plane, t_ray ray, t_intersection *its)
{
	double			denom;
	t_dot			diff;

	denom = vs(plane->normal, ray.dir_vect);
	if (fabs(denom) > 0.00001)
	{
		diff = vmn(plane->centre, ray.origin);
		its->t = vs(diff, plane->normal) / denom;
		if (its->t > 0.00001)
		{
			if (denom >= 0 && its->closest_t != -INFINITY)
			{
				plane->normal.x *= -1;
				plane->normal.y *= -1;
				plane->normal.z *= -1;
			}
			return (1);
		}
	}
	return (0);
}
