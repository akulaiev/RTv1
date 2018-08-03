/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_manipulate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 12:43:46 by akulaiev          #+#    #+#             */
/*   Updated: 2018/08/03 12:43:48 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normalize(t_dot *ray)
{
	double	ray_len;

	ray_len = sqrt(ray->x * ray->x + ray->y * ray->y + ray->z * ray->z);
	ray->x /= ray_len;
	ray->y /= ray_len;
	ray->z /= ray_len;
}

t_base	get_basis(t_dot vect)
{
	t_dot	tmp;
	t_base	res;

	tmp.x = vect.x;
	tmp.y = vect.y + 0.0001;
	tmp.z = vect.z + 0.0002;
	res.right_vect = vector_cross(vect, tmp);
	normalize(&res.right_vect);
	res.up_vect = vector_cross(vect, res.right_vect);
	normalize(&res.up_vect);
	res.right_vect = vector_cross(vect, res.up_vect);
	normalize(&res.right_vect);
	res.dir_vect = vect;
	return (res);
}
