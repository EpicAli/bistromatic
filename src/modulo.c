/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:59:24 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/18 10:59:25 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 3 % 4
// str1:4
// str2:3

#include "../header/bistromatic.h"

int g_FLAG;

char			*modulo(char *str1, char *str2)
{
	int			i;
	char		*tmp;

	i = 0;
	if (is_smaller(str2, str1) == 0)
	{
		return ("0");
		ft_strdel(&str1);
		ft_strdel(&str2);
	}
	else if (is_smaller(str2, str1) == 1)
		return (str2);
	else
	{
		while (is_smaller(str2, str1) == -1 || is_smaller(str2, str1) == 0)
			str2 = checkfor0(division(str1, str2, 1));
		tmp = ft_strnew(ft_strlen(str2));
		ft_strcpy(tmp, str2);
		ft_strdel(&str2);
		ft_strdel(&str1);
		if (g_FLAG == -1)
		{
			tmp = add_minus(str2);
			g_FLAG = -g_FLAG;
		}
		ft_strdel(&str1);
		ft_strdel(&str2);
		return (tmp);
	}
}
