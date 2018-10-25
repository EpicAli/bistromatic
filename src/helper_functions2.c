/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:09:48 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/21 18:09:51 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int			priority_problem(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '-' && str[i + 1] == '(')
			return (1);
	}
	return (0);
}

char		*clean_str(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		sign;

	sign = 1;
	i = 0;
	j = 0;
	if (ft_isbase(str[i]) == 0)
	{
		if (str[i] == '(')
			return (str);
		while (ft_isbase(str[i]) == 0 && str[i] != '(')
		{
			if (str[i] == '-')
				sign *= -1;
			i++;
		}
		if (i == 0 || (i == 1 && str[0] == '-'))
			return (str);
		new = ft_strnew(ft_strlen(str) - i + 1);
		if (sign == -1)
			new[j++] = '-';
		while (str[i])
		{
			new[j] = str[i];
			i++;
			j++;
		}
		new[j] = '\0';
		ft_strdel(&str);
		return (new);
	}
	else
		return (str);
}

char		*check_for_change(t_operators *operator, char *str)
{
	char	*new;

	if (operator->op == '-')
	{
		new = ft_strnew(ft_strlen(str) + 1);
		new[0] = '-';
		ft_strcat(new, str);
		return (new);
	}
	return (str);
}

int			get_index(char *str, int i)
{
	t_operators *operator;
	int			count;

	count = 1;
	operator = NULL;
	while (str[++i] && count > 0)
	{
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;
	}
	if (str[i] == ')' && str[i + 1])
		return (i + 1);
	else
		return (i);
}

char		get_next_operator(char *str, int i)
{
	while (str[i++])
		if (is_operator(str[i]))
			break ;
	return (str[i]);
}

