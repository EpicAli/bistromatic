/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:57:46 by amagnan           #+#    #+#             */
/*   Updated: 2018/09/21 15:35:01 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	helper_function1(va_list ap, char str)
{
	char	*s;
	int		d;
	char	c;

	if (str == 's')
	{
		s = (char *)va_arg(ap, char *);
		if (!s)
			ft_putstr("(null)");
		else
			ft_putstr(s);
	}
	if (str == 'd' || str == 'i')
	{
		d = (int)va_arg(ap, int);
		ft_putnbr(d);
	}
	if (str == 'c')
	{
		c = (char)va_arg(ap, int);
		ft_putchar(c);
	}
}

static void	helper_function2(va_list ap, char str)
{
	int				o;
	unsigned int	u;
	int				x;
	uint64_t		p;

	if (str == 'o')
	{
		o = (int)va_arg(ap, int);
		ft_putstr(ft_itoa_base_long(o, 8, "0123456789abcdef"));
	}
	else if (str == 'u')
	{
		u = (unsigned int)va_arg(ap, unsigned int);
		ft_putnbr(u);
	}
	else if (str == 'x')
	{
		x = (int)va_arg(ap, int);
		ft_putstr(ft_itoa_base_long(x, 16, "0123456789abcdef"));
	}
	else if (str == 'p')
	{
		p = (uint64_t)va_arg(ap, void *);
		ft_putstr0x(ft_itoa_base(p, 16, "0123456789abcdef"));
	}
}

int		b_printf(char *format, ...)
{
	va_list		ap;
	int			i;

	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's' || format[i] == 'd' ||
				format[i] == 'i' || format[i] == 'c')
				helper_function1(ap, format[i]);
			else if (format[i] == 'o' || format[i] == 'u' ||
				format[i] == 'x' || format[i] == 'p')
				helper_function2(ap, format[i]);
			else
				ft_putchar(format[i]);
		}
		else
			ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (g_glob);
}
