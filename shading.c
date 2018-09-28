/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:28:49 by akulaiev          #+#    #+#             */
/*   Updated: 2018/09/21 15:28:51 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void	shading_help(t_shd *s, t_col *constant_col, t_intersection *its)
{
	s->h_vect = vector_add(s->l.vect, s->v_vect);
	normalize(&s->h_vect);
	s->nl = fmax(0, vector_scalar(its->normal, s->l.vect));
	s->hl = fmax(0,
	pow(vector_scalar(its->normal, s->h_vect), 100));
	s->tmp_r += constant_col->struct_col.r * s->nl + 131 * s->hl;
	s->tmp_g += constant_col->struct_col.g * s->nl + 131 * s->hl;
	s->tmp_b += constant_col->struct_col.b * s->nl + 131 * s->hl;
}

static void	init(t_shd *s, t_thread *t, t_intersection *its)
{
	s->v_vect = vector_minus(t->camera.origin, its->ray_point);
	normalize(&s->v_vect);
	s->tmp_r = 0;
	s->tmp_g = 0;
	s->tmp_b = 0;
}

static void	integer_to_col(t_shd *s)
{
	if (s->tmp_r > 0xFF)
		s->col.struct_col.r = 0xFF;
	else
		s->col.struct_col.r = s->tmp_r;
	if (s->tmp_g > 0xFF)
		s->col.struct_col.g = 0xFF;
	else
		s->col.struct_col.g = s->tmp_g;
	if (s->tmp_b > 0xFF)
		s->col.struct_col.b = 0xFF;
	else
		s->col.struct_col.b = s->tmp_b;
}

t_col		blinn_phong_shading(t_col *constant_col,
t_intersection *its, t_thread *t)
{
	t_shd			s;
	t_intersection	its1;
	t_dot			*light;
	t_shape			*shape;

	light = t->lights;
	shape = t->shapes;
	init(&s, t, its);
	s.i = -1;
	s.l.origin = its->ray_point;
	while (++s.i < t->win->num_l)
	{
		s.l.vect = vector_minus(light[s.i],
		s.l.origin);
		s.light_len = sqrt(vector_scalar(s.l.vect,
		s.l.vect));
		s.l.vect = vector_divide(s.l.vect, s.light_len);
		s.j = 0;
		while (s.j < t->win->num_shapes)
		{
			if (!shape[s.j].f(shape[s.j].data, s.l, &its1) ||
			s.light_len < its1.t || its1.t < 0.00001)
				s.j++;
			else
				break;
		}
		if (s.j == t->win->num_shapes)
			shading_help(&s, constant_col, its);
	}
	integer_to_col(&s);
	return (s.col);
}
