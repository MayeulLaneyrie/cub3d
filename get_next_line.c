/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:56:55 by shamizi           #+#    #+#             */
/*   Updated: 2021/04/21 16:20:51 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int		end_of_line(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_write_line(char *str)
{
	char		*res;
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_left(char *str)
{
	int			i;
	int			j;
	char		*res;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	if (!(res = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1))))
		return (0);
	i++;
	while (str[i])
		res[j++] = str[i++];
	free(str);
	res[j] = '\0';
	return (res);
}

int		get_next_line(int fd, char **line)
{
	int			res;
	char		*buff;
	static char	*saved;

	res = 1;
	if (BUFFER_SIZE <= 0 || !line || fd < 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (res != 0 && !end_of_line(saved))
	{
		if ((res = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[res] = '\0';
		saved = ft_strjoin(saved, buff);
	}
	free(buff);
	*line = ft_write_line(saved);
	saved = ft_left(saved);
	if (res == 0)
		return (0);
	return (1);
}
