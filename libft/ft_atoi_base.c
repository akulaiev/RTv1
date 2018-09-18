/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:30:05 by akulaiev          #+#    #+#             */
/*   Updated: 2018/03/01 18:30:08 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_help(char c)
{
	int		diff;

	if (c && c >= '0' && c <= '9')
	{
		diff = '0';
		return (diff);
	}
	if (c && c >= 'A' && c <= 'F')
	{
		diff = '7';
		return (diff);
	}
	if (c && c >= 'a' && c <= 'f')
	{
		diff = 'W';
		return (diff);
	}
	return (0);
}

int			ft_atoi_base(const char *str, int base)
{
	int		i;
	int		diff;
	int		temp;
	int		check;

	i = 0;
	temp = 0;
	check = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check = 1;
		i++;
	}
	while ((diff = ft_help(str[i])))
	{
		temp *= base;
		temp += str[i] - diff;
		i++;
	}
	if (check)
		return (-temp);
	return (temp);
}
