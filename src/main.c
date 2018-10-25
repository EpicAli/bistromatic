/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:01:53 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/16 14:06:08 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

int g_FLAG;

char 		*erase_parenthesis(char *str, int i)
{
	char 	*tmp;
	int		j;
	int		save;
	char 	*new;

	j = 0;
	save = i;
	tmp = ft_strnew(ft_strlen(str));
	while (str[--i] && str[i] != '(' && i >= 0)
	{
		tmp[j] = str[i];
		j++;
	}
	tmp[j] = '\0';
	tmp = ft_strrevdup(tmp);
	tmp[j] = '\0';
	new = ft_strnew(save - i - 1);
	new = ft_strncpy(new, str, i);
	new = ft_strcat(new, tmp);
	new = ft_strcat_from(new, str, save + 1);
	ft_strdel(&str);
	ft_strdel(&tmp);
	return (new);
}

char 		*check_for_parenthesis(char *str)
{
	int		i;
	int		count;
	int		n;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
		{
			j = i + 1;
			n = 1;
			count = 0;
			while (str[j] && n > 0)
			{
				if (str[j] == '(')
					n++;
				else if (str[j] == ')')
					n--;
				else if (ft_isbase(str[j]) == 1)
				{
					count++;
					while (ft_isbase(str[j + 1]))
						j++;
				}
				j++;
			}
			if (count < 2)
				break ;
		}
		i++;
	}
	if (count < 2 && j != 0 && n == 0)
	{
		str = erase_parenthesis(str, j - 1);
		check_for_parenthesis(str);
	}
	return (str);
}

char 		*handle_priorities(char *str, int i)
{
	t_operators *operator;
	t_operands *operand;
	char 	*tmp;
	char 	*new;
	int		x;

	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '-' && get_next_operator(str, i) == '(')
		{
			operator = NULL;
			operand = NULL;
			tmp = ft_strnew(ft_strlen(str));
			x = get_index(str, i + 1);
			if (str[x] && str[x] != ')')
				x--;
			tmp = erase_minus(ft_strndup_from(str, i, x));
			create_stacks(tmp, &operand, &operator);
			while (operator && operand && operand->next)
				do_calcul(pop_operator(&operator), &operand);
			if (operator)
				operand->number = check_for_change(operator, operand->number);
			operand->number = last_check(operand->number);
			operand->number = add_minus(operand->number);
			operand->number = clean_str(operand->number);
			new = ft_strcpy_from_to(str, 0, i - 1);
			new = ft_strcat(new, operand->number);
			new = check_for_parenthesis(new);
			if (str[x + 1])
				new = ft_strcat_from(new, str, x);
			if (operator && new[ft_strlen(new) - 1] == ')' && operator->op == '(')
			{
				pop_operator(&operator);
				new[ft_strlen(new) - 1] = '\0';
			}
			new = check_for_parenthesis(new);
			i = i + ft_strlen(operand->number);
			ft_strcpy(str, new);
			ft_strdel(&tmp);
			new = NULL;
		}
		i++;
	}
	ft_strdel(&new);
	return (str);
}

int			check_syntax(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || ft_is_operation(str[i]) == 1)
	{
		ft_putstr("syntax error: Devine\n");
		return (-1);
	}
	while (str[i])
	{
		if (ft_is_operation(str[i]) == 1 && (ft_is_operation(str[i + 1]) == 1 && str[i + 1] != '-'))
		{
			b_printf("syntax error: Invalid operations at index %d-%d\n", i, i + 1);
			return (-1);
		}
		else if (ft_is_operation(str[i]) == 1 && ft_is_operation(str[i + 1]) == 1 && ft_is_operation(str[i + 2]) == 1)
		{
			b_printf("syntax error: Invalid operations at index %d-%d\n", i, i + 1);
			return (-1);
		}
		else if (str[i] == '(')
		{
			if (is_operator(str[i - 1]) == -1)
			{
				b_printf("syntax error: Parenthesis without operator at index %d\n", i);
				return (-1);
			}
			count++;
		}
		else if (str[i] == ')')
			count--;
		i++;
	}
	if (count != 0)
	{
		ft_putstr("syntax error: Parentheses do not match\n");
		return (-1);
	}
	return (0);
}

// ERRORS : 
// echo "-(154352*(1543+154355344355/554545435*(5455343453456/(437658712+78615434%(345540%5+(10*28766785)-487678678688766)+186766)-28766780)/48766783)*287686780)*(-(18768762-98766788*86786742)*(1867886+6886763-58768670/8763))" | ./calc "0123456789" 216
// echo "3+4+-(4*2)" | ./calc 0123456789 10 gives segfault

int			main()
{
	int 	argc = 3;
	int			nb;
	char		*str;
	t_operands	*operand;
	t_operators	*operator;

	g_FLAG = 1;
	operand = NULL;
	operator = NULL;
	if (argc == 3)
	{
		g_base = ft_strdup("0123456789"); //ft_strdup(argv[1]);
		nb = 216;//ft_atoi(argv[2]);
		str = ft_strdup("-(154352*(1543+154355344355/554545435*(5455343453456/(437658712+78615434%(345540%5+(10*28766785)-487678678688766)+186766)-28766780)/48766783)*287686780)*(-(18768762-98766788*86786742)*(1867886+6886763-58768670/8763))"); //ft_strnew(nb);
		// read(0, str, nb);
		str[nb] = '\0';
		if (check_syntax(str) == -1)
			return (-1);
		while (priority_problem(str) == 1)
			ft_strcpy(str, handle_priorities(clean_str(str), 0));
		create_stacks(str, &operand, &operator);
		while (operator && operand && operand->next)
			do_calcul(pop_operator(&operator), &operand);
		if (operator)
			operand->number = check_for_change(operator, operand->number);
		operand->number = last_check(operand->number);
		ft_putstr(operand->number);
		ft_putchar('\n');
	}
	return (0);
}
