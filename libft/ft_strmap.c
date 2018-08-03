/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:20:50 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:20:51 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*s_new;
	int		i;

	i = 0;
	if (s != NULL && (s_new = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
	{
		while (s[i])
		{
			s_new[i] = f(s[i]);
			i++;
		}
		s_new[i] = '\0';
		return (s_new);
	}
	return (0);
}
