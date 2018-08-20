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
# define NUM_TH 17

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
	unsigned int	integer;
	t_color			struct_col;
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

typedef	struct	s_fig
{
	t_dot	centre;
	int		radius;
	t_dot	normal;
	t_col	col;
	t_col	constant_col;
}				t_fig;

typedef struct	s_intersection
{
	double	t;
	double	t0;
	double	t1;
	double	closest_t;
	double	d;
	t_dot	normal;
	t_dot	ray_point;
	int		col;
	t_fig	closest_shape;
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

typedef struct	s_data
{
	void	*mlx_p;
	void	*mlx_nw;
	void	*mlx_img;
	char	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		ww;
	int		wh;
	int		lines_per_th;
}				t_data;

typedef struct	s_iter
{
	int		x;
	int		y;
	double	x_norm;
	double	y_norm;
}				t_iter;

typedef	struct s_shape
{
	void 		*data;
	int 		(*f)(t_fig *shape_type,
	t_ray ray, t_intersection *its);
}				t_shape;

typedef struct	s_thread
{
	int		current_y;
	t_data	*win;
	t_cam 	camera;
	t_shape *shapes;
}				t_thread;

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
int			sphere_intersection(t_fig *shape_type, t_ray ray, t_intersection *its);
int			plane_intersection(t_fig *shape_type, t_ray ray, t_intersection *its);
t_col		lambert_shading(t_col *constant_col, t_intersection *its);
void		img_pixel_put(t_data *win, int x, int y, int col);
void		deal_with_threads(t_data *win, t_cam camera, t_shape *shapes);
void		*create_ray(void *w);

t_col	get_its_params(t_fig fig, t_ray ray, t_intersection *its);
int		get_closest_shape(t_thread *t, t_ray ray, t_intersection *its);

#endif
