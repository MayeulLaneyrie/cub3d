/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:35:03 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/15 16:19:58 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	ft_strlen(char *str)
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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int		i;
	const unsigned char	*src_char;
	unsigned char		*dst_char;

	i = 0;
	src_char = src;
	dst_char = dst;
	if (src == dst)
		return (dst);
	while (src > dst && i < len)
	{
		dst_char[i] = src_char[i];
		i++;
	}
	while (src < dst && i < len)
	{
		dst_char[len - i - 1] = src_char[len - i - 1];
		i++;
	}
	return (dst);
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
	str = malloc(sizeof(char) * (s_total + 1));
	if (!str)
		return (0);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[s_total] = '\0';
	free((char *)s1);
	return (str);
}
