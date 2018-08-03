/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 21:15:01 by akulaiev          #+#    #+#             */
/*   Updated: 2017/12/01 21:15:02 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsort(char **str, int num)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (j < num)
	{
		j = i + 1;
		while (j < num)
		{
			if (ft_strcmp(str[i], str[j]))
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (str);
}
