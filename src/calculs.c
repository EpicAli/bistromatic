/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:28:26 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/15 15:28:27 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"
#include <stdio.h>

int g_FLAG;

char		*erase_minus(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == '-')
		i++;
	new_str = ft_strnew(ft_strlen(str) - i);
	while (str[i + j])
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char		*checkfor0(char *str)
{
	int		i;
	char	*tmp;
	int		j;
	int		flag;

	flag = (str[0] == '-') ? 1: 0;
	i = 0;
	j = 0;
	if (str[i] != '0' && str[i] != '-')
		return (str);
	else
	{
		while (str[i] == '0' || (str[i] == '-'))
			i++;
		if (str[i])
		{
			tmp = ft_strnew(ft_strlen(str) - i + 1);
			if (flag == 1)
				tmp[j++] = '-';
			while (str[i])
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			tmp[j] = '\0';
		}
		else
		{
			// g_FLAG = -g_FLAG;
			tmp = ft_strnew(2);
			tmp[0] = '0';
			tmp[1] = '\0';
		}
		return (tmp);
	}
}

char 		check_for_operation(char *c, t_operands **head)
{
	if (*c == '+')
	{
		if ((*head)->number[0] == '-' && (ft_isbase((*head)->next->number[0]) == 1))
		{
			*c = '-';
			(*head)->number = erase_minus((*head)->number);
			g_FLAG = -g_FLAG;
 			ft_strswap(&(*head)->number, &(*head)->next->number);
 			check_for_operation(c, head);
		}
		else if ((*head)->next->number[0] == '-' && (ft_isbase((*head)->number[0]) == 1))
		{
			*c = '-';
			(*head)->next->number = erase_minus((*head)->next->number);
			g_FLAG = -g_FLAG;
			check_for_operation(c, head);
		}
		else
			return (*c);
	}
	else if (*c == '-')
	{
		if ((*head)->number[0] == '-' && (ft_isbase((*head)->next->number[0]) == 1))
		{
			*c = '+';
			(*head)->number = erase_minus((*head)->number);
			g_FLAG = -g_FLAG;
			check_for_operation(c, head);
		}
		else if ((*head)->next->number[0] == '-' && (ft_isbase((*head)->number[0]) == 1))
		{
			*c = '+';
			g_FLAG = -g_FLAG;
			(*head)->next->number = erase_minus((*head)->next->number);
			check_for_operation(c, head);
		}
		else if ((*head)->number[0] == '-' && (*head)->next->number[0] == '-')
		{
			*c = '+';
			(*head)->next->number = erase_minus((*head)->next->number);
			check_for_operation(c, head);
		}
		else
			return (*c);
	}
	else if (*c == '*' || *c == '/')
	{
		if ((*head)->number[0] == '-' && (ft_isbase((*head)->next->number[0]) == 1))
		{
			(*head)->number = erase_minus((*head)->number);
			g_FLAG = -g_FLAG;
			check_for_operation(c, head);
		}
		else if ((*head)->next->number[0] == '-' && (ft_isbase((*head)->number[0]) == 1))
		{
			(*head)->next->number = erase_minus((*head)->next->number);
			g_FLAG = -g_FLAG;
			check_for_operation(c, head);
		}
		else if ((*head)->number[0] == '-' && (*head)->next->number[0] == '-')
		{
			(*head)->number = erase_minus((*head)->number);
			(*head)->next->number = erase_minus((*head)->next->number);
			check_for_operation(c, head);
		}
		else
			return (*c);
	}
	else if (*c == '%')
	{
		if ((*head)->next->number[0] == '-' && (ft_isbase((*head)->number[0]) == 1))
		{
			(*head)->next->number = erase_minus((*head)->next->number);
			g_FLAG = -g_FLAG;
			check_for_operation(c, head);
		}
		else if ((*head)->number[0] == '-' && (ft_isbase((*head)->next->number[0]) == 1))
		{
			(*head)->number = erase_minus((*head)->number);
			check_for_operation(c, head);
		}
		else if ((*head)->number[0] == '-' && (*head)->next->number[0] == '-')
		{
			(*head)->number = erase_minus((*head)->number);
			(*head)->next->number = erase_minus((*head)->next->number);
			g_FLAG = -g_FLAG;
			check_for_operation(c, head);
		}
	}
	return (*c);
}



void		do_calcul(char c, t_operands **head)
{
	char	*result;

	if (*head && (*head)->next)
	{
		c = check_for_operation(&c, head);
		if (c == '+')
		{
			result = addition(pop_operand(head), pop_operand(head));
			add_operand(head, checkfor0(result));
		}
		else if (c == '-')
		{
			result = soustraction(pop_operand(head), pop_operand(head), 1);
			add_operand(head, checkfor0(result));
		}
		else if (c == '*')
		{
			result = multiplication(pop_operand(head), pop_operand(head));
			add_operand(head, checkfor0(result));
		}
		else if (c == '/')
		{
			result = division(pop_operand(head), pop_operand(head), 0);
			add_operand(head, checkfor0(result));
		}
		else if (c == '%')
		{
			result = modulo(pop_operand(head), pop_operand(head));
			add_operand(head, checkfor0(result));
		}
	}
	else
	{
		ft_putstr("Tried to calculate with only one number");
		exit(0);
	}
}
