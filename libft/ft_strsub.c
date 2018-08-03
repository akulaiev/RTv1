/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:21:25 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:21:27 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_n;
	size_t	i;
	size_t	indx;

	i = 0;
	if (s != NULL && s[0] != '\0' &&
	(str_n = (char*)malloc(sizeof(char) * len + 1)))
	{
		if (len <= ft_strlen(s) && start <= ft_strlen(s))
		{
			indx = start + len;
			while (start < indx)
			{
				str_n[i] = s[start];
				i++;
				start++;
			}
			str_n[i] = '\0';
			return (str_n);
		}
	}
	return (NULL);
}
