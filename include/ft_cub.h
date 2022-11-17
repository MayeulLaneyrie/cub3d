/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:55:18 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/17 15:13:12 by shamizi          ###   ########.fr       */
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
# include <math.h>

# include "pcr.h"

# define BUFFER_SIZE 10000

# define WIN_H 720
# define WIN_W 1280

# define FOV 70
# define PI 3.14159265359

# define VERY_BIG 1e30

# define X 0
# define Y 1

# define AZERTY

# ifdef AZERTY
#  define KEY_FWD 'z'
#  define KEY_LSD 'q'
# else
#  define KEY_FWD 'w'
#  define KEY_LSD 'a'
# endif

# define KEY_BWD 's'
# define KEY_RSD 'd'
# define KEY_RTL 0xff51
# define KEY_RTR 0xff53
# define KEY_ESC 0xff1b

typedef enum	e_face
{
	no,
	so,
	ea,
	we
}	t_face;

typedef	struct	s_hit
{
	double	dist;
	t_face	face;
}	t_hit;

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
	t_disp	*d;
};

int		get_next_line(int fd, char **line, int res);

int		ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_error(char *str, int i, t_cub *cub);
int		stock_map(char *str, t_cub *cub);
void	ft_map(char *str, t_cub *cub);
int		check_cub(char *str, t_cub *cub);

void	ft_init(t_cub *cub);
void	free_cub(t_cub *cub);

int		frame(t_cub *cub);

t_hit	*trace_ray(t_cub *cub, double *ray, t_hit *ret);

int		draw_hit(t_cub *cub, t_hit hit, int x);

/*
**	vect_op.c: -----------------------------------------------------------------
*/

int	add_v(double const *u, double const *v, double *dst);
int	sub_v(double const *u, double const *v, double *dst);
int	mul_rv(double t, double const *u, double *dst);

#endif
