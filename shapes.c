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

t_col	get_its_params(t_fig fig, t_ray ray, t_intersection *its, t_thread *t)
{
	its->ray_point = vector_add(ray.origin, vector_mult(ray.vect, its->t));
	if (!ft_strcmp(fig.name, "sphere"))
	{
		its->normal = vector_divide(vector_minus(its->ray_point, fig.centre), fig.radius);
		normalize(&its->normal);
	}
	else if (!ft_strcmp(fig.name, "cylinder"))
	{
		its->normal = vector_minus(vector_minus(its->ray_point, fig.centre), 
		vector_mult(fig.direction, vector_scalar(fig.direction, vector_minus(its->ray_point, fig.centre))));
		normalize(&its->normal);
	}
	else if (!ft_strcmp(fig.name, "plane"))
		its->normal = fig.normal;
	return (blinn_phong_shading(&fig.constant_col, its, t));
}

int		get_closest_shape(t_thread *t, t_ray ray, t_intersection *its)
{
	int		i;
	int		col;

	i = -1;
	its->closest_t = INFINITY;
	col = 0;
	while (++i < 3)
	{
		if (t->shapes[i].f(t->shapes[i].data, ray, its) && its->t < its->closest_t)
		{
			col = get_its_params((*(t_fig*)t->shapes[i].data), ray, its, t).integer;
			its->closest_t = its->t;
		}
	}
	return (col);
}

int		cylinder_intersection(t_fig *cy, t_ray ray, t_intersection *its)
{
	t_dot	tmp;
	t_dot	tmp1;
	double	a;
	double	b;
	double	c;
	t_dot	delta_p;

	delta_p = vector_minus(ray.origin, cy->centre);
	tmp = vector_minus(ray.vect, vector_mult(cy->direction, vector_scalar(ray.vect, cy->direction)));
	tmp1 = vector_minus(delta_p, vector_mult(cy->direction, vector_scalar(delta_p, cy->direction)));
	a = vector_scalar(tmp, tmp);
	b = 2 * vector_scalar(tmp, tmp1);
	c = vector_scalar(tmp1, tmp1) - (cy->radius * cy->radius);
	its->d = pow(b, 2) - 4 * a * c;
	if (its->d < 0 || (a == 0 && b == 0) ||
	((its->t = (-b - sqrt(its->d)) / (2.0 * a)) <= 0.00001 &&
	(its->t = (-b + sqrt(its->d)) / (2.0 * a)) <= 0.00001))
		return (0);
	return (1);
}

int		sphere_intersection(t_fig *sphere, t_ray ray, t_intersection *its)
{
	double			p1;
	double			p2;
	t_dot			e_min_c;

	e_min_c = vector_add(ray.origin, vector_mult(sphere->centre, -1));
	p1 = vector_scalar(ray.vect, e_min_c);
	p1 *= p1;
	p2 = vector_scalar(ray.vect, ray.vect) *
	vector_scalar(e_min_c, e_min_c) - (sphere->radius * sphere->radius);
	its->d = p1 - p2;
	if (its->d < 0)
		return (0);
	else
	{
		its->t0 = (vector_scalar(vector_mult(ray.vect, -1), e_min_c) + sqrt(its->d))
		/ vector_scalar(ray.vect, ray.vect);
		its->t1 = (vector_scalar(vector_mult(ray.vect, -1), e_min_c) - sqrt(its->d))
		/ vector_scalar(ray.vect, ray.vect);
		if ((its->t0 > 0 && its->t1 > 0 && its->t0 < its->t1) || (its->t0 > 0 && its->t1 < 0))
			its->t = its->t0;
		if ((its->t0 > 0 && its->t1 > 0 && its->t1 < its->t0) || (its->t1 > 0 && its->t0 < 0))
			its->t = its->t1;
		return (1);
	}
}

int		plane_intersection(t_fig *plane, t_ray ray, t_intersection *its)
{
	double			denom;
	t_dot			diff;

	denom = vector_scalar(plane->normal, ray.vect);
	if (fabs(denom) > 0.0001)
	{
		diff = vector_add(plane->centre, vector_mult(ray.origin, -1));
		its->t = vector_scalar(diff, plane->normal) / denom;
		if (its->t > 0.0001)
			return (1);
	}
	return (0);
}

