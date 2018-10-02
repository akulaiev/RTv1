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

t_col		get_its_params(t_fig f, t_ray r, t_intersection *i, t_thread *t)
{
	i->ray_point = va(r.origin, vm(r.dir_vect, i->t));
	if (!ft_strcmp(f.name, "sphere"))
	{
		i->normal = vd(vmn(i->ray_point, f.centre), f.radius);
		normalize(&i->normal);
	}
	else if (!ft_strcmp(f.name, "cylinder"))
	{
		i->normal = vmn(vmn(i->ray_point, f.centre),
		vm(f.dir, vs(f.dir, vmn(i->ray_point, f.centre))));
		normalize(&i->normal);
	}
	else if (!ft_strcmp(f.name, "cone"))
	{
		i->normal = vmn(vmn(i->ray_point, f.centre),
		vm(f.dir, vs(f.dir, vmn(i->ray_point, f.centre))));
		normalize(&i->normal);
		i->normal = va(vm(i->normal,
		cos(f.angle)), vm(f.dir, sin(f.angle)));
	}
	else if (!ft_strcmp(f.name, "plane"))
		i->normal = f.normal;
	return (blinn_phong_shading(&f.constant_col, i, t));
}

static void	shading_help(t_shd *s, t_col *constant_col, t_intersection *its)
{
	s->h_vect = va(s->l.dir_vect, s->v_vect);
	normalize(&s->h_vect);
	s->nl = fmax(0, vs(its->normal, s->l.dir_vect));
	s->hl = fmax(0,
	pow(vs(its->normal, s->h_vect), 100));
	s->tmp_r += constant_col->struct_col.r * s->nl + 131 * s->hl;
	s->tmp_g += constant_col->struct_col.g * s->nl + 131 * s->hl;
	s->tmp_b += constant_col->struct_col.b * s->nl + 131 * s->hl;
}

static void	init(t_shd *s, t_thread *t, t_intersection *its)
{
	s->v_vect = vmn(t->camera.origin, its->ray_point);
	normalize(&s->v_vect);
	s->tmp_r = 0;
	s->tmp_g = 0;
	s->tmp_b = 0;
	s->i = -1;
	s->l.origin = its->ray_point;
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
	t_shape			*shape;

	shape = t->shapes;
	init(&s, t, its);
	while (++s.i < t->win->num_l)
	{
		s.l.dir_vect = vmn(t->lights[s.i], s.l.origin);
		s.light_len = sqrt(vs(s.l.dir_vect, s.l.dir_vect));
		s.l.dir_vect = vd(s.l.dir_vect, s.light_len);
		s.j = 0;
		while (s.j < t->win->num_shapes)
		{
			if (!shape[s.j].f(shape[s.j].data, s.l, &its1) ||
			s.light_len < its1.t || its1.t < 0.00001)
				s.j++;
			else
				break ;
		}
		if (s.j == t->win->num_shapes)
			shading_help(&s, constant_col, its);
	}
	integer_to_col(&s);
	return (s.col);
}
