/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistromatic.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:02:27 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/15 12:02:30 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTROMATIC_H
# define BISTROMATIC_H

#include <unistd.h>
#include "../libft/libft.h"

typedef struct 			s_operands
{
	char				*number;
	struct s_operands	*next;
}						t_operands;

typedef struct 			s_operators
{
	char				op;
	int					weight;
	struct s_operators	*next;
}						t_operators;

int						g_FLAG;
int						g_y;
int						g_x;
char 					*g_base;

t_operands				*make_new_operand(char *str, t_operands *next);
void					add_operand(t_operands **head, char *str);
char					*pop_operand(t_operands **head);
t_operators				*make_new_operator(char c, t_operators *next);
char					pop_operator(t_operators **head);
int						is_operator(char c);
char					*addition(char *str1, char *str2);
void					add_operator(t_operators **head, t_operands **op_head, char c);
void					do_calcul(char c, t_operands **head);
char					*soustraction(char *str1, char *str2, int x);
int						is_smaller(char *str1, char *str2);
char					*checkfor0(char *str);
char			 		*multiplication(char *str1, char *str2);
char 					*add_zero(char *str);
char					*erase_minus(char *str);
char 					check_for_operation(char *c, t_operands **head);
char 					*last_check(char *str);
char					*get_number(char *str);
char 					*check_str(char *str, int i);
void					create_stacks(char *str, t_operands **operand, t_operators **operator);
char					*clean_str(char *str);
char					*check_for_change(t_operators *operator, char *str);
char 					*add_minus(char *str);
char					*division(char *str1, char *str2, int x);
char					*modulo(char *str1, char *str2);
int						add_operator_until(char c, t_operators **head);
int						next_operator(char *str, int i);
char 					*check_for_parenthesis(char *str);
char 					*handle_priorities(char *str, int i);
int						ft_get_index(char c);
char					ft_get_char(int i);
int						ft_isbase(char c);
char 					*help_addition(char **new, int *k, int rest);
int						check_syntax(char *str);
char					get_next_operator(char *str, int i);
int						get_index(char *str, int i);
int						priority_problem(char *str);
int						is_heavier(char c, char *str, int i);
int						get_weight(char c);

#endif
