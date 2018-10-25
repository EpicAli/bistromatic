/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:58:57 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/18 10:59:00 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int g_FLAG;

char 		*add_zero(char *str)
{
	char 	*new_str;
	int		i;

	i = 0;
	new_str = ft_strnew(ft_strlen(str) + 1);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '0';
	new_str[i + 1] = '\0';
	ft_strdel(&str);
	return (new_str);
}

char 		*add_minus(char *str)
{
	char 	*new_str;
	int		i;

	i = 0;
	new_str = ft_strnew(ft_strlen(str) + 1);
	new_str[i] = '-';
	while (str[i])
	{
		new_str[i + 1] = str[i];
		i++;
	}
	new_str[i + 1] = '\0';
	ft_strdel(&str);
	return (new_str);
}

char 		*correct_str(char *str)
{
	int		i;

	i = 0;
	while ((str[i] && ft_isdigit(str[i]) == 1) || (str[i] == '-' && i == 0))
		i++;
	str[i] = '\0';
	return (str);
}

char 		*multiplication(char *str1, char *str2)
{
	char 	*new;
	char 	**tab;
	int		i;
	int		k;
	int		j;
	int		a;
	int		b;
	int		result;
	int		rest;
	int		x;
	int		flag;

	x = 0;
	if (is_smaller(str1, str2) == 1)
		ft_strswap(&str1, &str2);
	i = ft_strlen(str2) - 1;
	tab = (char **)malloc(sizeof(char *) * ft_strlen(str2) + 1);
	while (str2[i] && i >= 0)
	{
		rest = 0;
		k = 0;
		j = ft_strlen(str1) - 1;
		a = ft_get_index(str2[i]);
		new = ft_strnew(ft_strlen(str1) + ft_strlen(str2) + 1);
		while (str1[j] && j >= 0)
		{
			b = ft_get_index(str1[j]);
			result = ((a * b) + rest) % 10;
			rest = ((a * b) + rest) / 10;
			new[k] = ft_get_char(result);
			k++;
			j--;
		}
		if (rest > 0)
			new[k] = ft_get_char(rest);
		k++;
		new[k] = '\0';
		new = ft_strrevdup(new);
		new[k] = '\0';
		tab[x++] = ft_strdup(new);
		str1 = add_zero(str1);
		i--;
	}
	tab[x] = 0;
	x = 0;
	flag = g_FLAG;
	while (tab[x] && tab[x + 1])
	{
		tab[x + 1] = ft_strdup(addition(tab[x], tab[x + 1]));
		x++;
	}
	if (flag == -1)
	{
		tab[x] = add_minus(tab[x]);
		g_FLAG = 1;
	}
	tab[x] = correct_str(tab[x]);
	return (tab[x]);
}
