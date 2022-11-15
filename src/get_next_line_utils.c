/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:35:03 by shamizi           #+#    #+#             */
/*   Updated: 2021/04/14 14:42:27 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*desti;
	unsigned char	*srci;

	desti = (unsigned char *)dest;
	srci = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < len)
	{
		desti[i] = srci[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			str[n];

	ft_memcpy(str, src, n);
	ft_memcpy(dest, str, n);
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s_total;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	s_total = s1_len + s2_len;
	if (!(str = malloc(sizeof(char) * (s_total + 1))))
		return (0);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[s_total] = '\0';
	free((char *)s1);
	return (str);
}
