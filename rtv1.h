/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:08:52 by akulaiev          #+#    #+#             */
/*   Updated: 2018/07/31 14:08:54 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"
# include <string.h>
# include <pthread.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_color;

typedef union	u_col
{
	unsigned int		integer;
	t_color	struct_col;
}				t_col;

typedef struct	s_dot
{
	double	x;
	double	y;
	double	z;
}				t_dot;

typedef struct	s_ray
{
	t_dot	vect;
	t_dot	origin;
}				t_ray;

typedef struct	s_intersection
{
	double	t;
	double	t1;
	double	d;
	t_dot	normal;
	t_dot	ray_point;
}				t_intersection;

typedef struct	s_base
{
	t_dot	dir_vect;
	t_dot	up_vect;
	t_dot	right_vect;
}				t_base;

typedef	struct	s_cam
{
	t_dot	origin;
	t_base	basis;
}				t_cam;

typedef	struct	s_sph
{
	t_dot	centre;
	int		radius;
	t_col	col;
	t_col	constant_col;
}				t_sph;

typedef	struct	s_pln
{
	t_dot	centre;
	t_dot	normal;
	t_col	col;
	t_col	constant_col;
}				t_pln;

typedef struct	s_data
{
	void	*mlx_p;
	void	*mlx_nw;
	int		ww;
	int		wh;
}				t_data;

int			key_react(int keycode, void *param);
t_dot		vector_add(t_dot first, t_dot second);
t_dot		vector_mult(t_dot first, double val);
t_dot		vector_divide(t_dot first, double val);
double		vector_scalar(t_dot first, t_dot second);
t_dot		vector_cross(t_dot first, t_dot second);
void		normalize(t_dot *ray);
t_base		get_basis(t_dot vect);
int			key_react(int keycode, void *param);
void		open_win(t_data *win);

#endif
