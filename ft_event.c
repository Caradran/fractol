/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:13:13 by esuits            #+#    #+#             */
/*   Updated: 2017/12/14 20:45:05 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

void	ft_zoom(t_env *env, int keycode)
{
	if (keycode == 69 || keycode == 5)
	{
		env->center.x *= 1.1;
		env->center.y *= 1.1;
		env->zoom *= 1.1;
	}
	else if (keycode == 78 || keycode == 4)
	{
		env->center.x /= 1.1;
		env->center.y /= 1.1;
		env->zoom /= 1.1;
	}
	ft_draw(env);
}

void	ft_deplace(t_env *env, int keycode, double x, double y)
{
	if (x == 3000)
	{
		if (keycode == 123)
			(env->center.x) -= 10;
		if (keycode == 124)
			(env->center.x) += 10;
		if (keycode == 125)
			(env->center.y) += 10;
		if (keycode == 126)
			(env->center.y) -= 10;
	}
	else
	{
		if (keycode == 5 || keycode == 4)
		{
			env->center.x += x / 4;
			env->center.y += y / 4;
			ft_zoom(env, keycode);
		}
	}
}

int		ft_key(int keycode, void *params)
{
	t_env	*tmp;

	tmp = (t_env*)params;
	if (keycode == 53)
		exit(0);
	if (keycode == 69 || keycode == 78)
		ft_zoom(tmp, keycode);
	if (keycode == 49)
		tmp->flag = !(tmp->flag);
	if (keycode == 15 || keycode == 48)
	{
		if (keycode == 48)
			tmp->frac = (tmp->frac + 1) % 2;
		tmp->zoom = 1;
		tmp->center = ft_cmpl_create_alg(0, 0);
		ft_draw(tmp);
	}
	if (keycode <= 126 && keycode >= 123)
	{
		ft_deplace(tmp, keycode, 3000, 0);
		ft_draw(tmp);
	}
	ft_changecol(keycode, tmp);
	ft_putnbr(keycode);
	ft_putchar('\n');
	return (0);
}

int		ft_mouse(int x, int y, void *params)
{
	t_env	*env;

	env  = (t_env*)params;
	if (!(env->flag) || (env->frac != 1))
		return (0);
	env->julia.x =  (x  - WIN_L / 2) / (float)(WIN_L / 2);
	env->julia.y =  (y  - WIN_H / 2) / (float)(WIN_H / 2);
	printf("%f, %f\n", env->julia.x, env->julia.y);
	env->julia.iter = 0;
	ft_julia_mult(env);
	mlx_put_image_to_window(NULL, env->win, (char*)env->pimg, 0 , 0);
	return (0);
}

int		ft_mouse_key(int button, int x, int y, void *params)
{
	t_env	*env;

	env = (t_env*) params;
	printf("%d\n", env->frac);
	x -= WIN_L / 2;
	y -= WIN_H / 2;
	if (button == 5)
		ft_deplace(env, button, x, y);
	else if (button == 4)
		ft_deplace(env, button, x, y);
	return (0);
}
