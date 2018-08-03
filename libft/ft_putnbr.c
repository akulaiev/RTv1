/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:19:47 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:19:49 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long long	i;
	long long	i_new;
	long long	dvd;
	char		c_i;

	i = (long long)n;
	dvd = 1;
	if (n < 0)
	{
		i = -i;
		write(1, "-", 1);
	}
	i_new = i;
	while (i_new > 9)
	{
		i_new /= 10;
		dvd *= 10;
	}
	while (dvd)
	{
		c_i = (i / dvd) + '0';
		i = i % dvd;
		dvd /= 10;
		write(1, &c_i, 1);
	}
}
