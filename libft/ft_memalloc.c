/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:28:39 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/28 20:28:41 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	char	*mem_s;
	size_t	i;

	i = 0;
	if ((mem = malloc(sizeof(void) * size)))
	{
		mem_s = (char*)mem;
		while (i < size)
			mem_s[i++] = 0;
		mem_s[i] = '\0';
		return (mem_s);
	}
	return (0);
}
