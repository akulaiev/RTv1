/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:48:25 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/10 17:48:26 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	c1;
	unsigned char	*b1;
	size_t			i;

	c1 = (unsigned char)c;
	b1 = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		b1[i] = c1;
		i++;
	}
	return (b1);
}
