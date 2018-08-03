/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:48:54 by akulaiev          #+#    #+#             */
/*   Updated: 2018/03/15 18:48:56 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_double_free(void **data, int num_lines)
{
	int		i;

	i = 0;
	if (data)
	{
		while (i < num_lines && data[i])
		{
			free(data[i]);
			i++;
		}
		free(data);
		data = NULL;
	}
}
