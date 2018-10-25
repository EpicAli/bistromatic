/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:27:06 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/15 15:27:07 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bistromatic.h"

t_operands		*make_new_operand(char *str, t_operands *next)
{
	t_operands	*new;

	if ((new = (t_operands *)malloc(sizeof(t_operands))))
	{
		if (!str)
			new->number = NULL;
		new->number = ft_strdup(str);
		new->next = next;
	}
	return (new);
}

void			add_operand(t_operands **head, char *str)
{
	if (!*head)
		*head = make_new_operand(str, NULL);
	else
		*head = make_new_operand(str, *head);
}

char			*pop_operand(t_operands **head)
{
	t_operands	*current;
	char		*str;

	current = *head;
	str = ft_strdup((*head)->number);
	*head = (*head)->next;
	free(current);
	current = NULL;
	return (str);
}
