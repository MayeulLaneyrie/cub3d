/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 14:47:25 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	ft_path(char *str, t_cub *cub, char **texture, int i)
{
	int	j;

	j = 0;
	if (*texture != NULL)
	{
		cub->error = 4;
		return ;
	}
	if (str[i] != ' ')
		cub->error = 4;
	while (str[i] && str[i] == ' ')
		i++;
	*texture = (char *)(malloc(sizeof(char) * (ft_strlen(str) + 1)));
	if (!*texture)
		return ;
	while (str[i])
	{
		(*texture)[j] = str[i];
		i++;
		j++;
	}
	(*texture)[j] = '\0';
}

void	ft_texture(char *str, t_cub *cub)
{
	static const char	*lookup[4] = {"NO", "SO", "EA", "WE"};
	t_face				i;

	i = -1;
	while (++i < 4)
	{
		if (str[0] == lookup[i][0] && str[1] == lookup[i][1])
		{
			ft_path(str, cub, &(cub->texpath[i]), 2);
			break ;
		}
	}
}

void	ft_parsing(char *fichier, t_cub *cub, int ret)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(fichier, O_DIRECTORY);
	if (fd != -1)
		ft_error("IS A DIRECTORY\n", 15, cub);
	fd = open(fichier, O_RDONLY);
	if (fd < 0)
		ft_error("INVALIDE .CUB\n", 14, cub);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, 1);
		ft_color(&str, cub);
		ft_texture(str, cub);
		ft_map(str, cub);
		free(str);
	}
	close (fd);
	if (cub->error != 0)
		ft_error("erreur de parsing\n", 18, cub);
	if (!cub->mapsize[Y])
		ft_error("pas de map\n", 11, cub);
	stock_map(fichier, cub);
}

int	check_cub(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	if (!str)
		ft_error("Nom de fichier invalide\n", 24, cub);
	while (str[i])
		i++;
	while (str[i] != '.')
	{
		if (i == 0)
			ft_error("nom de fichier invalide\n", 24, cub);
		i--;
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3]
		== 'b' && str[i + 4] == '\0')
		ft_parsing(str, cub, 1);
	else
		ft_error("nom de fichier invalide\n", 24, cub);
	return (0);
}

void	ft_init(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 7)
		cub->key_buffer[i] = 0;
	i = -1;
	while (++i < 4)
	{
		cub->texpath[i] = NULL;
		cub->texture[i] = NULL;
		cub->pos[i / 2] = 0;
		cub->or_cam[i / 2] = 0;
		cub->or_plancam[i / 2] = 0;
		cub->mapsize[i / 2] = 0;
	}
	cub->update = 0;
	cub->i = 0;
	cub->error = 0;
	cub->fc = 0;
	cub->f = -1;
	cub->c = -1;
	cub->map = NULL;
	cub->flmap = 0;
	cub->a = 0;
	cub->d = NULL;
}
