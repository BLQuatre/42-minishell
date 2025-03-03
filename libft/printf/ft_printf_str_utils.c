/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:23:07 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/12 20:14:03 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	ft_isflag(int c)
{
	return (c == '-'
		|| c == '0'
		|| c == '+'
		|| c == ' '
		|| c == '#');
}

bool	ft_isformat(int c)
{
	return (c == 'c'
		|| c == 's'
		|| c == 'p'
		|| c == 'd'
		|| c == 'i'
		|| c == 'u'
		|| c == 'x'
		|| c == 'X'
		|| c == '%');
}
