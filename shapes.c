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

void	double_swap(double a, double b)
{
	double temp;

	temp = a;
	a = b;
	b = temp;
}

void	get_its_params(t_fig fig, t_ray ray, t_intersection *its)
{
	its->ray_point = vector_add(ray.origin, vector_mult(ray.vect, its->t));
	if (!fig.normal.x && !fig.normal.y && !fig.normal.z)
	{
		its->normal = vector_divide(vector_add(its->ray_point,
		vector_mult(fig.centre, -1)), fig.radius);
		normalize(&its->normal);
	}
	else
		its->normal = fig.normal;
	fig.col = lambert_shading(&fig.constant_col, its);
	its->col = fig.col.integer;
}

int		sphere_intersection(t_fig *sphere, t_ray ray, t_intersection *its)
{
	double			p1;
	double			p2;
	t_dot			e_min_c;

	e_min_c = vector_add(ray.origin, vector_mult(sphere->centre, -1));
	p1 = vector_scalar(ray.vect, e_min_c);
	p1 *= p1;
	p2 = vector_scalar(e_min_c, e_min_c) - (sphere->radius * sphere->radius);
	its->d = p1 - p2;
	if (its->d < 0)
		return (0);
	else
	{
		its->t0 = vector_scalar(vector_mult(ray.vect, -1), e_min_c) + sqrt(its->d);
		its->t1 = vector_scalar(vector_mult(ray.vect, -1), e_min_c) - sqrt(its->d);
		if (its->t0 > its->t1)
			double_swap(its->t0, its->t1);
		if (its->t0 < 0) 
		{ 
			its->t0 = its->t1;
			if (its->t0 < 0)
				return (0);
		}
		its->t = its->t0; 
		get_its_params(*sphere, ray, its);
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
		{
			get_its_params(*plane, ray, its);
			return (1);
		}
	}
	return (0);
}

