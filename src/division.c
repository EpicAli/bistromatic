/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   division.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:59:09 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/18 10:59:09 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int g_FLAG;

char 			get_next_char(char *str, int i)
{
	if (str[i + 1])
		return (str[i + 1]);
	return ('\0');
}

char 			*division(char *str1, char *str2, int x)
{
	char 		*tmp;
	int			count;
	char 		*new;
	int			j;
	int			i;
	int			k;

	k = 0;
	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(str2));
	if (is_smaller(str2, str1) == 0)
	{
		tmp = ft_strnew(1);
		tmp[0] = ft_get_char(1);
		ft_strdel(&str1);
		ft_strdel(&str2);
		return (tmp);
	}
	else if (is_smaller(str2, str1) == 1)
	{
		tmp = ft_strnew(1);
		tmp[0] = ft_get_char(0);
		ft_strdel(&str1);
		ft_strdel(&str2);
		return (tmp);
	}
	else
	{
		tmp = ft_strnew(ft_strlen(str1) + 1);
		tmp[j++] = str2[i];
		while (is_smaller(tmp, str1) == 1)
		{
			tmp[j] = get_next_char(str2, i);
			i++;
			j++;
		}
		while (str2[i])
		{
			if (is_smaller(tmp, str1) == -1 || is_smaller(tmp, str1) == 0)
			{
				count = 0;
				while (is_smaller(tmp, str1) == -1 || is_smaller(tmp, str1) == 0)
				{
					tmp = checkfor0(soustraction(str1, tmp, 0));
					count++;
				}
				new[k++] = ft_get_char(count);
			}
			else
				new[k++] = '0';
			tmp[ft_strlen(tmp)] = get_next_char(str2, i);
			tmp = checkfor0(tmp);
			i++;
		}
		if (x == 1)
			return (tmp);
		ft_strdel(&tmp);
	}
	if (g_FLAG == -1)
	{
		new = add_minus(new);
		k++;
		g_FLAG = -g_FLAG;
	}
	new[k] = '\0';
	return (new);
}