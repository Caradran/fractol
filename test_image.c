/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:50:07 by esuits            #+#    #+#             */
/*   Updated: 2017/12/14 20:55:43 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int		ft_init_env(t_env *env, char **av)
{
	if (!(env->color = ft_palette1(0x000000, 0xff0000, 0x000000)))
		return (0);
	if (!ft_strcmp("Julia", av[1]))
		env->frac = 1;
	else if (!ft_strcmp("Mandelbrot", av[1]))
		env->frac = 0;
	else
		return (0);
	env->zoom = 1;
	env->center = ft_cmpl_create_alg(0, 0);
	env->flag = 1;
	env->flagcol = 0;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_L, WIN_H, "mlx 42");
	env->pimg = mlx_new_image(env->mlx, WIN_L, WIN_H);
	env->simg = (int *)mlx_get_data_addr(env->pimg, &(env->bpp), &(env->s_l),
			&(env->endian));
	return (1);
}

int		ft_error(int a)
{
	if (a == 0)
		write(0, "usage : fractol nomfractal [palette]\n", 37);
	else if (a == 1)
		write(0, "error\n", 6);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	env;

	if (ac <= 1)
		return (ft_error(0));
	if (!ft_init_env(&env, av))
		return (ft_error(1));
	ft_draw(&env);
	mlx_loop_hook(env.mlx, ft_colorroll, (void*)&env);
	mlx_hook(env.win, 6, (1L<<6), ft_mouse, (void*)&env);
	mlx_mouse_hook(env.win, ft_mouse_key, (void*)&env); 
	mlx_key_hook(env.win, ft_key, (void*)&env);
	mlx_loop(env.mlx);
}
