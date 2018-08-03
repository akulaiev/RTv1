/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:21:04 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:21:05 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_new;
	unsigned int	i;

	i = 0;
	if (s != NULL && (s_new = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
	{
		while (s[i])
		{
			s_new[i] = f(i, s[i]);
			i++;
		}
		s_new[i] = '\0';
		return (s_new);
	}
	return (0);
}
