/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:50:07 by esuits            #+#    #+#             */
/*   Updated: 2017/12/07 21:31:48 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"
/*
int		ft_mandelbrot_iter(t_cmpl z, float x, float y, int count)
{
	double tmp;

	tmp = z.x * z.x - z.y * z.y + x;
	z.y = 2 * z.x * z.y + y;
	z.x = tmp;
	if (z.x * z.x + z.y * z.y > 2 || count > (1024))
		return (count);
	else
		return (ft_mandelbrot_iter(z, x, y, count + 1));
}

t_env	ft_mandel(double zoom, t_cmpl z, t_env env, int color)
{
	int		y;
	int		x;
	int		*tab;

	(void)color;
	if (!(tab = ft_palette1(0,0,0,0)))
		return (env);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_L)
		{
			env.simg[y * WIN_L + x] = tab[ft_mandelbrot_iter(
					ft_cmpl_create_alg(0, 0),
					(float)(x - WIN_L / 2 + z.x * zoom) / ((WIN_L / 4) * zoom),
					(float)(y - WIN_H / 2 + z.y * zoom) / ((WIN_H / 4) * zoom),
					0) / 2];
			++x;
		}
		++y;
	}
	ft_memdel((void**)&tab);
	return (env);
}*/

void	ft_init_env(t_env *env, int ac, char **av)
{
	if (!(env->color = ft_palette1(0, 0, 0xffffff, 0)))
		return ;
	ft_putendl("1");
	env->zoom = 1;
	env->center = ft_cmpl_create_alg(0, 0);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_L, WIN_H, "mlx 42");
	env->pimg = mlx_new_image(env->mlx, WIN_L, WIN_H);
	env->simg = (int *)mlx_get_data_addr(env->pimg, &(env->bpp), &(env->s_l),
			&(env->endian));
}

int		main(int ac, char **av)
{
	t_env	env;

	ft_putendl("0");
	ft_init_env(&env, ac, av);
	ft_mandel_mult(&env);
	ft_putendl("10");
	mlx_put_image_to_window(NULL, env.win, (char *)env.pimg, 0, 0);
	ft_putendl("11");
	mlx_key_hook(env.win, ft_key, (void*)&env);
	mlx_loop(env.mlx);
}
