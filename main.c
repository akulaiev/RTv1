
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

void	shading_help(t_shd *s, t_col *constant_col, t_intersection *its)
{
	s->h_vect[s->i] = vector_add(s->l_vect[s->i].vect, s->v_vect);
	normalize(&s->h_vect[s->i]);
	s->nl[s->i] = fmax(0, vector_scalar(its->normal, s->l_vect[s->i].vect));
	s->hl[s->i] = fmax(0, pow(vector_scalar(its->normal, s->h_vect[s->i]), 100));
	s->tmp_r += constant_col->struct_col.r * s->nl[s->i] + 131 * s->hl[s->i];
	s->tmp_g += constant_col->struct_col.g * s->nl[s->i] + 131 * s->hl[s->i];
	s->tmp_b += constant_col->struct_col.b * s->nl[s->i] + 131 * s->hl[s->i];
}

t_col	blinn_phong_shading(t_col *constant_col, t_intersection *its, t_thread *t)
{
	t_shd			s;
	t_intersection	its1[t->win->num_l];
	t_l_lst			*temp;
	t_sh_lst		*tmp;

	s.tmp_r = 0;
	s.tmp_g = 0;
	s.tmp_b = 0;
	s.i = -1;
	s.v_vect = vector_minus(t->camera.origin, its->ray_point);
	normalize(&s.v_vect);
	s.l_vect = (t_ray*)malloc(sizeof(t_ray) * t->win->num_l);
	s.h_vect = (t_dot*)malloc(sizeof(t_dot) * t->win->num_l);
	s.nl = (double*)malloc(sizeof(double) * t->win->num_l);
	s.hl = (double*)malloc(sizeof(double) * t->win->num_l);
	s.light_len = (double*)malloc(sizeof(double) * t->win->num_l);
	temp = t->lights;
	tmp = t->shapes;
	while (++s.i < t->win->num_l && temp)
	{
		s.l_vect[s.i].origin = its->ray_point;
		s.l_vect[s.i].vect = vector_minus(temp->light_coord, s.l_vect[s.i].origin);
		s.light_len[s.i] = sqrt(vector_scalar(s.l_vect[s.i].vect, s.l_vect[s.i].vect));
		s.l_vect[s.i].vect = vector_divide(s.l_vect[s.i].vect, s.light_len[s.i]);
		normalize(&s.l_vect[s.i].vect);
		while (tmp->next && !tmp->f(tmp->data, s.l_vect[s.i], &its1[s.i]))
			tmp = tmp->next;
		if (s.light_len[s.i] < its1[s.i].t || its1[s.i].t < 0.00001)
			shading_help(&s, constant_col, its);
		temp = temp->next;
	}
	s.tmp_r > 0xFF ? (s.col.struct_col.r = 0xFF) : (s.col.struct_col.r = s.tmp_r);
	s.tmp_g > 0xFF ? (s.col.struct_col.g = 0xFF) : (s.col.struct_col.g = s.tmp_g);
	s.tmp_b > 0xFF ? (s.col.struct_col.b = 0xFF) : (s.col.struct_col.b = s.tmp_b);
	free(s.l_vect);
	free(s.h_vect);
	free(s.nl);
	free(s.hl);
	free(s.light_len);
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

int		main(int argc, char **argv)
{
	int		fd;
	t_cam	camera;
	t_data	data;

	if (argc != 2)
		return (write(1, "Scene file needed!\n", 19));
	fd = open(argv[1], O_RDONLY);
	parser(fd, &camera, &data);
}
