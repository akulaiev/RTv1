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
	s->h_vect[s->i] = vector_add(s->l_vect[s->i].vect, s->v_vect);
	normalize(&s->h_vect[s->i]);
	s->nl[s->i] = fmax(0, vector_scalar(its->normal, s->l_vect[s->i].vect));
	s->hl[s->i] = fmax(0,
	pow(vector_scalar(its->normal, s->h_vect[s->i]), 100));
	s->tmp_r += constant_col->struct_col.r * s->nl[s->i] + 131 * s->hl[s->i];
	s->tmp_g += constant_col->struct_col.g * s->nl[s->i] + 131 * s->hl[s->i];
	s->tmp_b += constant_col->struct_col.b * s->nl[s->i] + 131 * s->hl[s->i];
}

static void	allocate_or_free(t_shd *s, int check, t_thread *t,
t_intersection *its)
{
	if (check)
	{
		s->i = -1;
		s->v_vect = vector_minus(t->camera.origin, its->ray_point);
		normalize(&s->v_vect);
		s->tmp_r = 0;
		s->tmp_g = 0;
		s->tmp_b = 0;
		s->l_vect = (t_ray*)malloc(sizeof(t_ray) * check);
		s->h_vect = (t_dot*)malloc(sizeof(t_dot) * check);
		s->nl = (double*)malloc(sizeof(double) * check);
		s->hl = (double*)malloc(sizeof(double) * check);
	}
	else
	{
		free(s->l_vect);
		free(s->h_vect);
		free(s->nl);
		free(s->hl);
	}
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
	t_intersection	its1[t->win->num_l];
	t_l_lst			*temp;
	t_sh_lst		*tmp;

	temp = t->lights;
	tmp = t->shapes;
	allocate_or_free(&s, t->win->num_l, t, its);
	while (++s.i < t->win->num_l && temp)
	{
		s.l_vect[s.i].origin = its->ray_point;
		s.l_vect[s.i].vect = vector_minus(temp->light_coord,
		s.l_vect[s.i].origin);
		s.light_len = sqrt(vector_scalar(s.l_vect[s.i].vect,
		s.l_vect[s.i].vect));
		s.l_vect[s.i].vect = vector_divide(s.l_vect[s.i].vect, s.light_len);
		while (tmp && !tmp->f(tmp->data, s.l_vect[s.i], &its1[s.i]))
			tmp = tmp->next;
		if (s.light_len < its1[s.i].t || its1[s.i].t < 0.00001 || !tmp)
			shading_help(&s, constant_col, its);
		temp = temp->next;
	}
	integer_to_col(&s);
	allocate_or_free(&s, 0, t, its);
	return (s.col);
}
