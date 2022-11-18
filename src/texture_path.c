/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:24:15 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/18 18:22:01 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	open_texture(t_cub *cub, char *fichier, int n)
{
	cub->texture[n] = pcr_load_img(cub->d->mlx, fichier);
	if (cub->texture[n] == NULL)
		ft_error("path\n", 5, cub);
}

void	texture_check(t_cub *cub)
{
	open_texture(cub, cub->no, 0);
	open_texture(cub, cub->so, 1);
	open_texture(cub, cub->ea, 2);
	open_texture(cub, cub->we, 3);
}
