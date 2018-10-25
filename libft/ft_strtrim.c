/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:09:21 by amagnan           #+#    #+#             */
/*   Updated: 2018/09/11 14:09:23 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	int		x;
	int		len;
	char	*tmp;

	i = 0;
	x = 0;
	len = ft_strlen(s) - 1;
	while (s[i] == 32 || s[i] == '\n' || s[i] == '\t')
		i++;
	if (i >= len)
		return ("");
	while (s[len] == 32 || s[len] == '\n' || s[len] == '\t')
		len--;
	if ((i == 0 && ft_strlen(s) == 0) || len == 0)
		return ("");
	if (!(tmp = (char *)malloc(sizeof(char) * (len - i) + 2)))
		return (NULL);
	while (s[i + x] && (i + x) <= len)
	{
		tmp[x] = s[i + x];
		x++;
	}
	tmp[x] = '\0';
	return (tmp);
}
