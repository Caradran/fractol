/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multith.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 22:28:56 by esuits            #+#    #+#             */
/*   Updated: 2017/12/07 22:07:38 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"
#include "stdio.h"

t_mand	ft_mand_th_iter(t_cmpl z, t_mand c)
{
	double tmp;

	c.iter = -1;
	if (fabs(sqrt((c.x - 1) * (c.x - 1) + c.y * c.y)) <= 0.5)
	{
		c.iter = ITERATIONS;
		return (c);
	}
	while (++c.iter < ITERATIONS)
	{
		if (z.x * z.x + z.y * z.y > 2)
		{
			c.x = z.x;
			c.y = z.y;
			return (c);
		}
		tmp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.x * z.y + c.y;
		z.x = tmp;
	}
	return (c);
}
/*
t_mand	ft_mand_th_recu(t_cmpl z, t_mand c)
{
	double tmp;

	tmp = z.x * z.x - z.y * z.y + c.x;
	z.y = 2 * z.x * z.y + c.y;
	z.x = tmp;
	if (++c.iter > ITERATIONS || z.x * z.x + z.y * z.y > 2)
	{
		c.x = z.x;
		c.y = z.y;
		return (c);
	}
	else
		return(ft_mand_th_recu(z, c));
}*/

int		ft_interpol(int color1, int color2, double t)
{
	int		color;

	color = 0xff0000 & (int)(((0xff0000 & color1) * (1 - t))
		+ (int)((0xff0000 & color2) * t));
	color += 0xff00 & ((int)((0xff00 & color1) * (1 - t))
		+ (int)((0xff00 & color2) * t));
	color += 0xff & ((int)((0xff & color1) * (1 - t))
		+ (int)((0xff & color2) * t));
	return (color);
}

void	*ft_mand_th(void *arg)
{
	t_env_th	*tmp;
	int			start;
	int			end;
	t_mand		c;

	tmp = (t_env_th*)arg;
	start = ((WIN_L * WIN_H) * tmp->part / THREADS) - 1;
	end = ((WIN_L * WIN_H) * (tmp->part + 1) / THREADS);
	while (++start < end)
	{
		c.x = (float)(start % WIN_L - WIN_L / 2 + tmp->env->center.x *
				tmp->env->zoom) / (tmp->env->zoom * (WIN_L / 4));
		c.y = (float)(floor(start / WIN_L) - WIN_H / 2 + tmp->env->center.y
				* tmp->env->zoom) / (tmp->env->zoom * (WIN_H / 4));
		c.iter = -1;
		c = ft_mand_th_iter(ft_cmpl_create_alg(0, 0), c);
		if (c.iter < ITERATIONS)
		{
			c.iter += - log(log(c.x * c.x + c.y * c.y) / (2 * log(2))) / log(2);
			tmp->env->simg[start] = ft_interpol(
				tmp->env->color[(int)floor(c.iter) % (NB_COL * 2) ],
				tmp->env->color[((int)floor(c.iter) + 1) % (NB_COL * 2)],
				c.iter - floor(c.iter));
		}
		else 
		tmp->env->simg[start] = 0;
	}
	return (NULL);
}

void	ft_mandel_mult(t_env *env)
{
	pthread_t		thread[THREADS];
	t_env_th		env_i[THREADS];
	int				i;

	i = 0;
	while (i < THREADS)
	{
		env_i[i].part = i;
		env_i[i].env = env;
		pthread_create(&thread[i], NULL, ft_mand_th, &env_i[i]);
		++i;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread[i++], NULL);
}
