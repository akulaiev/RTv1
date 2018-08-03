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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	point;
	char	*bign;

	bign = (char*)big;
	i = 0;
	if (little[0] == '\0')
		return (bign);
	while (i <= len - 1 && len != 0)
	{
		j = 0;
		point = i;
		while (bign[i] == little[j] && j < ft_strlen(little) &&
		i < ft_strlen(big) && i <= len - 1)
		{
			i++;
			j++;
		}
		if (little[j] == '\0')
			return (&bign[point]);
		i = point + 1;
	}
	return (0);
}
