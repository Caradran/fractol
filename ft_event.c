/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:13:13 by esuits            #+#    #+#             */
/*   Updated: 2017/12/13 21:34:32 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

void	ft_zoom(t_env *env, int keycode)
{
	if (keycode == 69)
	{
		env->center.x *= 1.5;
		env->center.y *= 1.5;
		env->zoom *= 1.5;
	}
	else
	{
		env->center.x /= 1.5;
		env->center.y /= 1.5;
		env->zoom /= 1.5;
	}
	if (env->frac == 1)
		ft_mandel_mult(env);
	if (env->frac == 2)
		ft_julia_mult(env);
	mlx_put_image_to_window(NULL, env->win, (char *)env->pimg, 0, 0);
}

void	ft_deplace(t_env *env, int keycode)
{
	if (keycode == 123)
		(env->center.x) -= 10;
	if (keycode == 124)
		(env->center.x) += 10;
	if (keycode == 125)
		(env->center.y) += 10;
	if (keycode == 126)
		(env->center.y) -= 10;
	if (env->frac == 1)
		ft_mandel_mult(env);
	if (env->frac == 2)
		ft_julia_mult(env);
	mlx_put_image_to_window(NULL, env->win, (char *)env->pimg, 0, 0);
}

int		ft_key(int keycode, void *params)
{
	t_env	*tmp;

	tmp = (t_env*)params;
	if (keycode == 53)
		exit(0);
	if (keycode == 69 || keycode == 78)
		ft_zoom(tmp, keycode);
	if (keycode <= 126 && keycode >= 123)
		ft_deplace(tmp, keycode);
	ft_putnbr(keycode);
	ft_putchar('\n');
	return (0);
}

int		ft_mouse(int x, int y, void *params)
{
	t_env	*env;

	env  = (t_env*)params;
	env->julia.x =  (x  - WIN_L / 2) / (float)(WIN_L / 2);
	env->julia.y =  (y  - WIN_H / 2) / (float)(WIN_H / 2);
	printf("%f, %f\n", env->julia.x, env->julia.y);
	env->julia.iter = 0;
	ft_julia_mult(env);
	mlx_put_image_to_window(NULL, env->win, (char*)env->pimg, 0 , 0);
	return (0);
}
