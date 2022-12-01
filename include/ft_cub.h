/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:55:18 by shamizi           #+#    #+#             */
/*   Updated: 2022/12/01 13:32:03 by mlaneyri         ###   ########.fr       */
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

# define FOV 90
# define PI 3.14159265359

# define VERY_BIG 1e30

# define X 0
# define Y 1

//# define AZERTY
//# define MOUSE_HIDE

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
# define KEY_SPR 0xff09

# define IDX_FWD 0
# define IDX_BWD 1
# define IDX_LSD 2
# define IDX_RSD 3
# define IDX_RTL 4
# define IDX_RTR 5
# define IDX_SPR 6

# define DDIST 0
# define SDIST 1
# define STEP 2

typedef enum e_face
{
	no,
	so,
	ea,
	we
}	t_face;

typedef struct s_hit
{
	double	dist;
	t_face	face;
	double	texx;
}	t_hit;

typedef struct s_cub	t_cub;
struct					s_cub
{
	int		bonus;
	int		update;
	int		i;
	int		error;
	int		fc;
	int		flmap;
	int		mapsize[2];
	int		nbligne;
	char	*texpath[8];
	int		f;
	int		c;
	char	**map;
	int		minimap;
	double	pos[2];
	double	a;
	double	or_cam[2];
	double	or_plancam[2];
	int		key_buffer[7];
	t_image	*texture[4];
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
void	texture_check(t_cub *cub);
void	ft_init(t_cub *cub);
int		free_cub(t_cub *cub);
void	floodfill(t_cub *cub, int x, int y, int overflow);
void	pos_start(t_cub *cub);
void	ft_color(char **str, t_cub *cub);
int		ft_fc(char *str, t_cub *cub);

/*
**	frame.c: -------------------------------------------------------------------
*/

int		frame(t_cub *cub);

/*
**	hud.c: ---------------------------------------------------------------------
*/

void	draw_hud(t_cub *cub);

/*
**	hooks.c: -------------------------------------------------------------------
*/

int		destroy_hook(t_disp *d);
int		key_hook(int x, t_cub *cub);
int		release_hook(int x, t_cub *cub);
int		mouse_motion_hook(int x, int y, t_cub *cub);
int		loop_hook(t_cub *cub);

/*
**	mouse.c: -------------------------------------------------------------------
*/

int		mouse(t_disp *d, int action);

/*
**	player_input.c: ------------------------------------------------------------
*/

int		do_inputs(t_cub *cub);

/*
**	trace_ray.c: ---------------------------------------------------------------
*/

t_hit	*trace_ray(t_cub *cub, double *ray, t_hit *ret);

/*
**	draw_hit.c: ----------------------------------------------------------------
*/

int		draw_hit(t_cub *cub, t_hit hit, int x);

#endif
