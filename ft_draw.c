/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 18:48:30 by esuits            #+#    #+#             */
/*   Updated: 2018/01/02 20:38:40 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

void	ft_draw2(t_env *env)
{
	if (env->frac == 10)
		ft_celtic_mult(env);
	if (env->frac == 11)
		ft_julia_celtic_mult(env);
	if (env->frac == 12)
		ft_druid_mult(env);
	if (env->frac == 13)
		ft_julia_druid_mult(env);
	mlx_put_image_to_window(NULL, env->win, (char *)env->pimg, 0, 0);
}

void	ft_draw(t_env *env)
{
	if (env->frac == 0)
		ft_mandel_mult(env);
	if (env->frac == 1)
		ft_julia_mult(env);
	if (env->frac == 2)
		ft_mand_pow_mult(env);
	if (env->frac == 3)
		ft_julia_pow_mult(env);
	if (env->frac == 4)
		ft_perpendic_mult(env);
	if (env->frac == 5)
		ft_julia_perpendic_mult(env);
	if (env->frac == 6)
		ft_ship_mult(env);
	if (env->frac == 7)
		ft_julia_ship_mult(env);
	if (env->frac == 8)
		ft_bird_mult(env);
	if (env->frac == 9)
		ft_julia_bird_mult(env);
	ft_draw2(env);
}

int		ft_colorroll(void *params)
{
	int		tmp;
	int		i;
	t_env	*env;

	env = (t_env*)params;
	if (!env->flagcol)
		return (0);
	i = -1;
	if (env->flagcol == 1)
	{
		tmp = env->color[0];
		while (++i < NB_COL * 2)
			env->color[i] = env->color[i + 1];
		env->color[NB_COL * 2] = tmp;
	}
	ft_draw(env);
	return (0);
}

void	ft_changecol(int keycode, t_env *env)
{
	if (keycode == 18)
		env->flagcol = (env->flagcol + 1) % 2;
	if (keycode == 19)
		env->color = ft_rainbow(env->color);
	if (keycode == 24 && env->pow < 8)
		env->pow++;
	if (keycode == 27 && env->pow > 1)
		env->pow--;
	ft_draw(env);
}
