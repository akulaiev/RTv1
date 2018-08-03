/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:21:14 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:21:16 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		if (n > ft_strlen(s1))
			n = ft_strlen(s1);
		if (!s1[i] && !s2[i])
			return (1);
		while (s1[i] && i != n && s1[i] == s2[i])
			i++;
		if (i == n)
			return (1);
	}
	return (0);
}
