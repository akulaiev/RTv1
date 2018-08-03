/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:21:37 by akulaiev          #+#    #+#             */
/*   Updated: 2017/11/30 12:21:39 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*s_new;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	s_new = NULL;
	if (s == NULL)
		return (NULL);
	k = ft_strlen(s) - 1;
	while ((s[k] == ' ' || s[k] == '\n' || s[k] == '\t') && k)
		k--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (k > 0 && (s_new = (char*)malloc(sizeof(char) * k - i + 2)))
	{
		while (i <= k && (s_new[j++] = s[i++]))
			s_new[j] = '\0';
	}
	else if (i == ft_strlen(s) && (s_new = (char*)malloc(1)))
		s_new[0] = '\0';
	return (s_new);
}
