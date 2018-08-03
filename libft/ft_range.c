/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 22:11:17 by akulaiev          #+#    #+#             */
/*   Updated: 2017/12/01 22:11:19 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int *array;
	int i;

	if (min < max)
	{
		i = 0;
		array = (int*)malloc(sizeof(*array) * (max - min));
		while (min < max)
		{
			array[i] = min;
			min++;
			i++;
		}
		return (array);
	}
	else
		return (0);
}
