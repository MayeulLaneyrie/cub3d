/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/16 15:37:06 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	ft_check_fc(char *str, t_cub *cub)
{
	int	i;
	int	nb;
	int	virgule;

	i = 1;
	nb = 0;
	virgule = 0;
	if (str[1] != ' ')
		cub->error = 2;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != ',' && !(str[i] >= '0' && str[i] <= '9'))
			cub->error = 1;
		if (str[i] >= '0' && str[i] <= '9' && nb == 0)
			nb = 1;
		if (nb == 1 && str[i] == ',')
		{
			virgule++;
			nb = 0;
		}
		i++;
	}
	if (virgule != 2)
		cub->error = 1;
}

int	ft_fc(char *str, t_cub *cub)
{
	int	check;
	int	n;

	n = 24;
	cub->fc = 0;
	ft_check_fc(str, cub);
	while (str[cub->i] == ' ' || str[cub->i] == ',')
	{
		check = 0;
		cub->i++;
		while (str[cub->i] >= '0' && str[cub->i] <= '9')
		{
			check = check * 10 + str[cub->i] - 48;
			if (str[cub->i + 1] < '0' || str[cub->i] > '9')
			{
				n -= 8;
				cub->fc += check << n;
			}
			cub->i++;
		}
		if (check > 255 || check < 0)
			cub->error = 2;
	}
	return (cub->fc);
}

void	ft_color(char **str, t_cub *cub)
{
	int	i;

	i = 0;
	cub->i = 1;
	if (cub->nbligne > 0 && (cub->no == NULL || cub->so == NULL
			|| cub->ea == NULL || cub->we == NULL))
		cub->error = 3;
	if (*str[i] == 'F')
		cub->f = ft_fc(*str, cub);
	else if (*str[i] == 'C')
		cub->c = ft_fc(*str, cub);
}

void	ft_path(char *str, t_cub *cub, char **texture, int i)
{
	int	j;

	j = 0;
	if (*texture != NULL)
		cub->error = 4;
	while (str[i] && str[i] == ' ')
		i++;
	*texture = (char *)(malloc(sizeof(char) * (ft_strlen(str) + 1)));
	if (!*texture)
		cub->error = 4;
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
	int	i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		ft_path(str, cub, &cub->no, 2);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		ft_path(str, cub, &cub->so, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_path(str, cub, &cub->ea, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_path(str, cub, &cub->we, 2);
}

void	ft_parsing(char *fichier, t_cub *cub, int ret)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(fichier, O_DIRECTORY);
	if (fd != -1)
		ft_error("IS A DIRECTORY\n", 15);
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		ft_error("INVALIDE .CUB\n", 14);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, 1);
		if (cub->error != 0)
			ft_error("erreur de parsing\n", 18);
		ft_color(&str, cub);
		ft_texture(str, cub);
		ft_map(str, cub);
		free(str);
	}
	close (fd);
	if (cub->nbligne == 0)
		ft_error("pas de map\n", 11);
	stock_map(fichier, cub);
}

int	check_cub(char *str, t_cub *cub)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != '.')
	{
		if (i == 0)
		{
			ft_error("nom de fichier invalide\n", 24);
			return (0);
		}
		i--;
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3]
		== 'b' && str[i + 4] == '\0')
		ft_parsing(str, cub, 1);
	else
		ft_error("nom de fichier invalide\n", 24);
	return (0);
}

void	ft_init(t_cub *cub)
{
	cub->i = 0;
	cub->error = 0;
	cub->fc = 0;
	cub->nbligne = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->f = -1;
	cub->c = -1;
	cub->map = NULL;
	cub->flmap = 0;
	cub->pos[0] = 0;
	cub->pos[1] = 0;
	cub->a = 0;
	cub->or_cam[0] = 0;
	cub->or_cam[1] = 0;
	cub->or_plancam[0] = 0;
	cub->or_plancam[1] = 0;
	cub->posx = 0;
	cub->posy = 0;
}
