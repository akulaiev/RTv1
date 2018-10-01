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
	c.tmp = vmn(ray.vect, vm(cy->direction, vs(ray.vect, cy->direction)));
	c.tmp1 = vmn(c.delta_p, vm(cy->direction, vs(c.delta_p, cy->direction)));
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
	c.tmp = vmn(ray.vect, vm(co->direction, vs(ray.vect, co->direction)));
	c.tmp1 = vmn(c.delta_p, vm(co->direction, vs(c.delta_p, co->direction)));
	c.a = pow(cos(co->angle), 2) * vs(c.tmp, c.tmp) -
	pow(sin(co->angle), 2) * pow(vs(ray.vect, co->direction), 2);
	c.b = 2 * pow(cos(co->angle), 2) * vs(c.tmp, c.tmp1) -
	2 * pow(sin(co->angle), 2) *
	vs(ray.vect, co->direction) * vs(c.delta_p, co->direction);
	c.c = pow(cos(co->angle), 2) * vs(c.tmp1, c.tmp1)
	- (co->radius * co->radius) -
	pow(sin(co->angle), 2) * pow(vs(c.delta_p, co->direction), 2);
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

	e_min_c = va(ray.origin, vm(sphere->centre, -1));
	p1 = vs(ray.vect, e_min_c);
	p1 *= p1;
	p2 = vs(ray.vect, ray.vect) *
	vs(e_min_c, e_min_c) - (sphere->radius * sphere->radius);
	its->d = p1 - p2;
	if (its->d < 0)
		return (0);
	else
	{
		its->t0 = (vs(vm(ray.vect, -1), e_min_c) + sqrt(its->d))
		/ vs(ray.vect, ray.vect);
		its->t1 = (vs(vm(ray.vect, -1), e_min_c) - sqrt(its->d))
		/ vs(ray.vect, ray.vect);
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

	denom = vs(plane->normal, ray.vect);
	if (fabs(denom) > 0.00001)
	{
		diff = va(plane->centre, vm(ray.origin, -1));
		its->t = vs(diff, plane->normal) / denom;
		if (its->t > 0.00001)
			return (1);
	}
	return (0);
}
