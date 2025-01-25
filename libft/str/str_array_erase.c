/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_erase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 06:39:17 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/23 06:53:01 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	str_array_erase(char **array, int index)
{
	int	i ;

	if (!array)
		return ;
	i = 0 ;
	while (array[i] && i < index)
		i++ ;
	if (array[i] == NULL)
		return ;
	free(array[i]);
	while (array[i + 1])
	{
		array[i] = array[i + 1];
		i++ ;
	}
	array[i] = array[i + 1];
}
