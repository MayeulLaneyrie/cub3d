/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:24:15 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/18 17:31:27 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	open_texture(t_cub *cub, char *fichier, t_image *img)
{
/*	int	fd;

	fd = open(fichier, O_RDONLY);
	if (fd < 0)
	{
		close (fd);
		ft_error("Chemin vers texture invalide\n", 29, cub);
	}
	close (fd);*/
	img = pcr_load_img(cub->d->mlx, fichier);
	if (img == NULL)
		ft_error("path\n", 5, cub);
}

void	texture_check(t_cub *cub)
{
	open_texture(cub, cub->no, cub->texture[0]);
	open_texture(cub, cub->so , cub->texture[1]);
	open_texture(cub, cub->ea , cub->texture[2]);
	open_texture(cub, cub->we , cub->texture[3]);
}
