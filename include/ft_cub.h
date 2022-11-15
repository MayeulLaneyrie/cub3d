/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:55:18 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/15 17:45:48 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB_H
# define FT_CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "pcr.h"

# define BUFFER_SIZE 10000

# define WIN_H 480
# define WIN_W 640

# define FOV 90
# define PI 3.14159265

typedef enum	e_or
{
	no,
	so,
	ea,
	we
}	t_or;

typedef	struct	t_hit
{
	double	dist;
	t_or	orient;
}

typedef struct s_cub	t_cub;
struct					s_cub
{
	int		i;
	int		error;
	int		fc;
	int		nbligne;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		f;
	int		c;
	char	**map;
	int		flmap;
	double	pos[2];
	double	a;
	double	or_cam[2];
	double	or_plancam[2];
	double	posx;
	double	posy;
	t_disp	*d;
};

int		get_next_line(int fd, char **line);

int		ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_error(char *str, int i);
int		stock_map(char *str, t_cub *cub);
void	ft_map(char *str, t_cub *cub);
int		check_cub(char *str, t_cub *cub);

void	ft_init(t_cub *cub);

int		frame(t_cub *cub);

/*
**	vect_op.c: -----------------------------------------------------------------
*/

int	add_v(double const *u, double const *v, double *dst);
int	sub_v(double const *u, double const *v, double *dst);
int	mul_rv(double t, double const *u, double *dst);

#endif
