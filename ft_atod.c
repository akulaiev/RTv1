/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:20:35 by akulaiev          #+#    #+#             */
/*   Updated: 2018/09/18 13:20:36 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**Function has some small bugs, but is still suitable for using in RTv1 project.
**Bugs must be fixed in order for the function to be added to libft
*/

double		ft_atod_help(char *str, int i, float temp)
{
	int		ten;

	ten = 10;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		temp *= 10;
		temp += str[i] - '0';
		i++;
	}
	if (str[i] == '.' && str[i - 1] && str[i - 1] >= '0' && str[i - 1] <= '9')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9' && str[i])
		{
			temp += (double)(str[i] - '0') / ten;
			ten *= 10;
			i++;
		}
	}
	return (temp);
}

double		ft_atod(char *str)
{
	int		i;
	double	temp;
	int		check;

	i = 0;
	temp = 0;
	check = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
	|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check = 1;
		i++;
	}
	temp = ft_atod_help(str, i, temp);
	if (check)
		return (-temp);
	return (temp);
}
