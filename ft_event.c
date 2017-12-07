/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:13:13 by esuits            #+#    #+#             */
/*   Updated: 2017/12/07 21:10:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

void	ft_zoom(t_env *env, int keycode)
{
	if (keycode == 69)
		env->zoom *= 2;
	else
		env->zoom /= 2;
	ft_mandel_mult(env);
	mlx_put_image_to_window(NULL, env->win, (char *)env->pimg, 0, 0);
}

void	ft_deplace(t_env *env, int keycode)
{
	if (keycode == 123)
		(env->center.x) -= 10;
	if (keycode == 124)
		(env->center.x) += 10;
	if (keycode == 125)
		(env->center.y) -= 10;
	if (keycode == 126)
		(env->center.y) += 10;
	ft_mandel_mult(env);
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
