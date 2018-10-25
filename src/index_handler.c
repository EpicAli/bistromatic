/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:07:29 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/20 14:07:30 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int			ft_get_index(char c)
{
	int		i;

	i = 0;
	while (g_base[i] != c)
		i++;
	return (i);
}

char		ft_get_char(int i)
{
	return (g_base[i]);
}

int			ft_isbase(char c)
{
	int		i;

	i = 0;
	while (g_base[i])
	{
		if (g_base[i] == c)
			return (1);
		i++;
	}
	return (0);
}
