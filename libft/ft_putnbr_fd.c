/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:19:35 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:19:38 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
		write(fd, "-", 1);
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
		write(fd, &c_i, 1);
	}
}
