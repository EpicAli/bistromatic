/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:09:39 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/21 18:09:40 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

char 		*last_check(char *str)
{
	char 	*new_str;
	int		sign;
	int		i;
	int		j;

	sign = 1;
	i = 0;
	j = 0;
	while ((str[i] == '0') || (is_operator(str[i]) == 1))
	{
		if (is_operator(str[i]) == 1)
		{
			if (str[i] == '-')
				sign = -sign;
		}
		if (str[i] == '0' && !str[i + 1])
			break ;
		i++;
	}
	new_str = ft_strnew(ft_strlen(str) - i + 1);
	if (sign == -1 && str[i] != '0')
		new_str[j++] = '-';
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	ft_strdel(&str);
	new_str[j] = '\0';
	return (new_str);
}

int			is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '%' || c == '(' || c == ')')
		return (1);
	return (0);
}

char		*get_number(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[i] > '0')
		return (str);
	else
	{
		while (str[i] == '0')
			i++;
		new = ft_strnew(ft_strlen(str) - i);
		while (str[i + j])
		{
			new[j] = str[i + j];
			j++;
		}
		new[j] = '\0';
		return (new);
	}
}

char 		*copy_number(char *str, int *i)
{
	int		j;
	int		entered;
	char 	*tmp;
	int		buf;

	j = 0;
	entered = 1;
	buf = 1;
	tmp = ft_strnew(buf);
	while ((ft_isbase(str[*i]) == 1) || (str[*i] == '-' && entered > 0) || ((is_operator(str[*i]) == 1) && (*i == 0)))
	{
		entered--;
		if (!tmp[j])
		{
			buf = buf * 2;
			tmp = ft_realloc(tmp, buf);
		}	
		tmp[j] = str[*i];
		*i += 1;
		j++;
	}
	tmp[j] = '\0';
	tmp = get_number(tmp);
	return (tmp);
}

void		create_stacks(char *str, t_operands **operand,
	t_operators **operator)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (str[i] && i < ft_strlen(str))
	{
		if ((ft_isbase(str[i]) == 1) || (str[i] == '-' && i == 0))
		{
			tmp = copy_number(str, (int*)&i);
			add_operand(operand, checkfor0(tmp));
			tmp = NULL;
		}
		else if (is_operator(str[i]) == 1)
		{
			if (str[i] == '-' && ft_is_operation(str[i - 1]) == 1)
			{
				tmp = copy_number(str, (int*)&i);
				add_operand(operand, checkfor0(tmp));
				tmp = NULL;
			}
			else if (str[i] != ')')
				add_operator(operator, operand, str[i]);
			else
			{
				while ((*operator) && (*operator)->op != '(')
					do_calcul(pop_operator(operator), operand);
				if (*operator)
					pop_operator(operator);
			}
			i++;
		}
		else
			break ;
	}
}

