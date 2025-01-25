/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 06:17:11 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/23 06:53:14 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**str_array_insert(char **array, char *to_insert, int index)
{
	char	**res ;
	int		i ;

	i = 0 ;
	while (array && array[i])
		i++ ;
	res = malloc((i + 2) * sizeof(char *));
	i = 0 ;
	while (array[i] && i < index)
	{
		res[i] = array[i];
		i++ ;
	}
	res[i++] = to_insert ;
	while (array[i - 1])
	{
		res[i] = array[i - 1];
		i++ ;
	}
	res[i] = NULL ;
	free(array);
	return (res);
}
