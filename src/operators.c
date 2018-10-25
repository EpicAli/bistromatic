/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:27:14 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/15 15:27:16 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

void			add_operator(t_operators **head, t_operands **op_head, char c)
{
	t_operators	*current;

	if (!*head)
		*head = make_new_operator(c, NULL);
	else
	{
		current = make_new_operator(c, NULL);
		if ((current->weight <= (*head)->weight) && ((*head)->op != '('))
		{
			while ((*head && current->weight <= (*head)->weight) && ((*head)->op != '('))
			{
				if (*op_head && (*op_head)->next)
					do_calcul(pop_operator(head), op_head);
				else
					break ;
			}
			current->next = *head;
			*head = current;
		}
		else
		{
			current->next = *head;
			*head = current;
		}
	}
}

int				add_operator_until(char c, t_operators **head)
{
	t_operators	*current;

	g_y = 0;
	if (c == '(')
	{
		if (g_x == 0 && (*head) && (*head)->op == '-')
			g_x++;
		else if (g_x != 0)
			g_x++;
	}
	else if (c == ')')
		g_x--;
	if (!*head)
		*head = make_new_operator(c, NULL);
	else
	{
		current = make_new_operator(c, NULL);
		if (g_x <= 0)
		{
			if (c == ')')
				return (-1);
			else if ((*head && current->weight <= (*head)->weight) && ((*head)->op != '('))
				return (-1);
			else
			{
				current->next = *head;
				*head = current;
			}
		}
		else
		{
			current->next = *head;
			*head = current;
		}
	}
	return (0);
}

t_operators		*make_new_operator(char c, t_operators *next)
{
	t_operators	*new;
	int			weight;

	if (c == '+' || c == '-')
		weight = 1;
	else if (c == '*' || c == '/' || c == '%')
		weight = 2;
	else if (c == '(' || c == ')')
		weight = 3;
	if ((new = (t_operators *)malloc(sizeof(t_operators))))
	{
		new->op = c;
		new->weight = weight;
		new->next = next;
	}
	else
		new = NULL;
	return (new);
}

char			pop_operator(t_operators **head)
{
	t_operators	*current;
	char		c;

	current = *head;
	c = (*head)->op;
	*head = (*head)->next;
	free(current);
	current = NULL;
	return (c);
}
