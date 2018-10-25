/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soustraction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:58:46 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/18 10:58:48 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int g_FLAG;

int			is_smaller(char *str1, char *str2)
{
	int		i;

	i = 0;
	if (ft_strlen(str1) < ft_strlen(str2))
		return (1);
	if (ft_strlen(str1) > ft_strlen(str2))
		return (-1);
	while (str1[i] && str2[i])
	{
		if (ft_get_index(str1[i]) < ft_get_index(str2[i]))
			return (1);
		else if (ft_get_index(str1[i]) > ft_get_index(str2[i]))
			return (-1);
		i++;
	}
	return (0);
}

char		*soustraction(char *str1, char *str2, int x)
{
	char	*new;
	int		i;
	int		j;
	int		rest;
	int		k;
	int		sum;

	new = ft_strnew(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (is_smaller(str2, str1) == 1)
	{
		ft_strswap(&str1, &str2);
		g_FLAG = -g_FLAG;
	}
	j = ft_strlen(str1) - 1;
	i = ft_strlen(str2) - 1;
	rest = 0;
	k = 0;
	while (str1[j] && j >= 0)
	{
		sum = (ft_get_index(str2[i]) - ft_get_index(str1[j]) - rest);
		if (sum < 0)
		{
			sum += 10;
			rest = 1;
		}
		else
			rest = 0;
		new[k] = ft_get_char(sum);
		k++;
		j--;
		i--;
	}
	if (str2[i])
	{
		while (str2[i] && i >= 0)
		{
			sum = (ft_get_index(str2[i]) - rest);
			if (sum < 0)
			{
				sum += 10;
				rest = 1;
			}
			else
				rest = 0;
			new[k] = ft_get_char(sum);
			i--;
			k++;
		}
	}
	if (x == 1 && g_FLAG == -1)
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
