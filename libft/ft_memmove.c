/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:57:07 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/13 13:57:10 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	dst1 = (char*)dst;
	src1 = (char*)src;
	if (src1 == dst1 || len == 0)
		return (dst1);
	if (src1 < dst1)
	{
		while (len--)
			dst1[len] = src1[len];
		dst1[0] = src1[0];
	}
	else
	{
		i = 0;
		while (i < len && (dst1[i] = src1[i]))
			i++;
	}
	return (dst1);
}
