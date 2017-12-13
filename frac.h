/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:55:02 by esuits            #+#    #+#             */
/*   Updated: 2017/12/13 22:10:12 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAC_H
# define FRAC_H

# include <math.h>
# include "./minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

# define WIN_L 1000
# define WIN_H 1000
# define ITERATIONS 128
# define NB_COL 64
# define THREADS 256

typedef struct		s_cmpl
{
	double		x;
	double		y;
}					t_cmpl;
typedef struct		s_mand
{
	double iter;
	double x;
	double y;
}					t_mand;
typedef struct		s_env
{
	void	*mlx;
	void	*win;
	void	*pimg;
	int		*simg;
	int		*color;
	int		bpp;
	int		s_l;
	int		endian;
	double	zoom;
	int		frac;
	t_mand	julia;
	t_cmpl	center;
}					t_env;
typedef struct		s_env_th
{
	t_env	*env;
	int		*color;
	int		part;
}					t_env_th;
int					ft_mouse(int x, int y, void *params);
void				ft_mandel_mult(t_env *env);
void				ft_julia_mult(t_env	*env);
t_mand				ft_mand_th_iter(t_cmpl a, t_mand b);
int					*ft_color_smooth(int a, int b);
void				ft_memncat(void *dst, void *src, size_t d, size_t n);
int					*ft_palette1(int j, int c1, int c2, int c3);
t_cmpl				ft_cmpl_mult(t_cmpl a, t_cmpl b);
t_cmpl				ft_cmpl_mod(t_cmpl z);
t_cmpl				ft_cmpl_add(t_cmpl a, t_cmpl b);
t_cmpl				ft_cmpl_create_alg(double x, double y);
t_cmpl				ft_cmpl_create_geo(double r, double th);
int					ft_mandelbrot_iter(t_cmpl z, float x, float y, int count);
int					ft_key(int keycode, void *params);
int					ft_hex_atoi(char *str);
#endif
