/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:41:16 by akulaiev          #+#    #+#             */
/*   Updated: 2018/08/02 18:41:17 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_dot	vector_add(t_dot first, t_dot second)
{
	t_dot	res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	res.z = first.z + second.z;
	return (res);
}

t_dot	vector_mult(t_dot first, double val)
{
	t_dot	res;

	res.x = first.x * val;
	res.y = first.y * val;
	res.z = first.z * val;
	return (res);
}

t_dot	vector_divide(t_dot first, double val)
{
	t_dot	res;

	res.x = first.x / val;
	res.y = first.y / val;
	res.z = first.z / val;
	return (res);
}

double	vector_scalar(t_dot first, t_dot second) 
{
	double	res;

	res = first.x * second.x + first.y * second.y + first.z * second.z;
	return (res);
}

t_dot	vector_cross(t_dot first, t_dot second)
{
	t_dot	res;

	res.x = first.y * second.z - first.z * second.y;
	res.y = first.z * second.x - first.x * second.z;
	res.z = first.x * second.y - first.y * second.x;
	return (res);
}
