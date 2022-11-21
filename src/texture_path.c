/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:24:15 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/21 13:50:18 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	texture_check(t_cub *cub)
{
	t_face	i;

	i = no - 1;
	while (++i <= we)
	{
		cub->texture[i] = pcr_load_img(cub->d, cub->texpath[i]);
		if (!cub->texture[i])
			ft_error("path\n", 5, cub);
	}
}
