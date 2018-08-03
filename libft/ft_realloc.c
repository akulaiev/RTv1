/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 19:21:37 by akulaiev          #+#    #+#             */
/*   Updated: 2018/03/01 19:21:38 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_realloc(char *line, size_t old, size_t new)
{
	char *temp;

	if ((new == 0 || new <= old) && line)
		return (line);
	if (!line)
		return (ft_memalloc(new + 1));
	temp = (char*)malloc(new + old + 1);
	ft_strcpy(temp, line);
	free(line);
	return (temp);
}
