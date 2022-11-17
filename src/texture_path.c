/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:24:15 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/17 10:35:36 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	open_texture(t_cub *cub, char *fichier, /*,structure mlx*/)
{
	int	fd;

	fd = open(fichier, O_RDONLY);
	if (fd < 0)
	{
		close (fd);
		ft_error("Chemin vers texture invalide\n", ft_strlen(fichier));
	}
	close (fd);
	//img->img = mlx_xpm_file_to_image(mlx, fichier, &img->width, &img->height);
	//img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
}

int	texture_check(t_cub *cub /*mlx*/)
{

	open_texture(cub, cub->no /*struct ;lx*/);
	open_texture(cub, cub->so /*struct ;lx*/);
	open_texture(cub, cub->ea /*struct ;lx*/);
	open_texture(cub, cub->we /*struct ;lx*/);
	//////////////////////////////////////////
	/*mlx->window.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	  mlx->window.addr = (int *)mlx_get_data_addr(mlx->windoz.img, &mlx->window.bpp, &mlx->window.line_length, &mlx->window.endian);
	  mlx->window.width = mlx->width;
	  mlx->window.height = mlx->height;
	  return(0);
}
