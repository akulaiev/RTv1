/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:45:14 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/09 11:45:16 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	point;
	char	*bign;

	bign = (char*)big;
	i = 0;
	if (*little)
	{
		while (bign[i])
		{
			j = 0;
			point = i;
			while (bign[i] == little[j] && little[j] && bign[i])
			{
				i++;
				j++;
			}
			if (!little[j])
				return (&bign[point]);
			i = point + 1;
		}
		return (0);
	}
	return (bign);
}
