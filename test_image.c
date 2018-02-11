/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:50:07 by esuits            #+#    #+#             */
/*   Updated: 2018/01/02 13:23:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int		ft_init_env(t_env *env)
{
	int i;

	i = NB_COL;
	if (!(env->color = (int*)malloc(sizeof(int) * i * 2 + 1)))
		return (0);
	env->color = ft_palette1(0xff0000, 0xffff00, 0xff0000, env->color);
	env->frac = 0;
	env->zoom = 1;
	env->center = ft_cmpl_create_alg(0, 0);
	env->pow = 3;
	env->flag = 1;
	env->flagcol = 0;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_L, WIN_H, "fractol 42");
	env->pimg = mlx_new_image(env->mlx, WIN_L, WIN_H);
	env->simg = (int*)mlx_get_data_addr(env->pimg, &(env->bpp), &(env->s_l),
			&(env->endian));
	return (1);
}

int		ft_error(int a)
{
	if (a == 0)
		write(0, "usage : fractol\n", 16);
	else if (a == 1)
		write(0, "Error\n", 6);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	env;

	(void)av;
	if (ac != 1)
		return (ft_error(0));
	if (!ft_init_env(&env))
		return (ft_error(1));
	ft_draw(&env);
	mlx_loop_hook(env.mlx, ft_colorroll, (void*)&env);
	mlx_hook(env.win, 6, (1L << 6), ft_mouse, (void*)&env);
	mlx_mouse_hook(env.win, ft_mouse_key, (void*)&env);
	mlx_key_hook(env.win, ft_key, (void*)&env);
	mlx_loop(env.mlx);
	return (0);
}
