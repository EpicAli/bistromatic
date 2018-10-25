/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:58:36 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/18 10:58:38 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int g_FLAG;

char		*addition(char *str1, char *str2)
{
	char	*new;
	int		i;
	int		j;
	int		k;
	int		rest;

	if (str1[0] == '-' && str2[0] == '-')
	{
		str1 = erase_minus(str1);
		str2 = erase_minus(str2);
		g_FLAG = -g_FLAG;
	}
	new = ft_strnew(ft_strlen(str1) + ft_strlen(str2));
	(ft_strlen(str1) > ft_strlen(str2)) ? ft_strswap(&str1, &str2) : 0;
	i = ft_strlen(str1) - 1;
	j = ft_strlen(str2) - 1;
	rest = 0;
	k = 0;
	while (str1[i] && ft_isbase(str1[i]) == 1 && i >= 0)
	{
		new[k] = ft_get_char(((ft_get_index(str1[i]) + ft_get_index(str2[j]) + rest) % 10));
		rest = ((ft_get_index(str1[i]) + ft_get_index(str2[j]) + rest) / 10);
		k++;
		j--;
		i--;
	}
	if (str2[j])
	{
		while (str2[j] && ft_isbase(str2[j]) && j >= 0)
		{
			new[k] = ft_get_char(((ft_get_index(str2[j]) + rest) % 10));
			rest = ((ft_get_index(str2[j]) + rest) / 10);
			k++;
			j--;
		}
	}
	if (rest != 0)
	{
		new[k++] = ft_get_char(rest);
		rest = 0;
	}
	if (g_FLAG == -1)
	{
		new[k] = '-';
		g_FLAG = -g_FLAG;
		k++;
	}
	new[k] = '\0';
	new = ft_strrevdup(new);
	new[k] = '\0';
	return (new);
}
