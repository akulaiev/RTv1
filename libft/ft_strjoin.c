/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:20:37 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:20:38 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_n;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 != NULL && s2 != NULL &&
	(str_n = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
	{
		while (s1[i] && (str_n[j] = s1[i]))
		{
			j++;
			i++;
		}
		i = 0;
		while (s2[i] && (str_n[j] = s2[i]))
		{
			i++;
			j++;
		}
		str_n[j++] = '\0';
		return (str_n);
	}
	return (0);
}
