/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multith.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 22:28:56 by esuits            #+#    #+#             */
/*   Updated: 2017/12/13 21:17:43 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

t_mand	ft_mand_th_iter(t_cmpl z, t_mand c)
{
	double tmp;

	c.iter = 0;
	while (++c.iter < ITERATIONS)
	{
		if (z.x * z.x + z.y * z.y > 4)
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
		c.x = (float)(start % WIN_L - WIN_L / 2 + tmp->env->center.x)
			/ (tmp->env->zoom * (WIN_L / 4));
		c.y = (float)(floor(start / WIN_L) - WIN_H / 2 + tmp->env->center.y)
			/ (tmp->env->zoom * (WIN_H / 4));
		c.iter = 0;
		c = ft_mand_th_iter(ft_cmpl_create_alg(0, 0), c);
		if (c.iter == ITERATIONS)
			tmp->env->simg[start] = 0;
		else
		{
			c.iter = (int)floor(c.iter * (log(c.iter) / log (ITERATIONS)));
			tmp->env->simg[start ] = tmp->env->color[(int)c.iter % (2 * NB_COL)];
/*			c.iter = c.iter + (log(log(ITERATIONS * ITERATIONS)) -
							log(log(c.x * c.x + c.y * c.y))) / log(2);*/
			tmp->env->simg[start] = tmp->env->color[(int)floor(c.iter) % NB_COL * 2];
		}
	}
	return (NULL);
}

/*
void	ft_coloration(t_env *env)
{
	double hue;
	int		i;
	long int tot;
	int		j;
	int		hist[ITERATIONS * 100];

	i = -1;
	tot = 0;
	ft_bzero((void*)hist, 100 * ITERATIONS * 4);
	while (++i < WIN_L * WIN_H)
		if (env->simg[i] < 100 * ITERATIONS)
		{
			tot += env->simg[i];
			hist[env->simg[i]] += 1;
		}
	i = -1;
	while (++i < WIN_L * WIN_H)
	{
		if (env->simg[i] < 100 * ITERATIONS)
		{
			hue = 0.0;
			j = -1;
			while (++j <= env->simg[i])
				hue += sqrt(env->zoom) * 100 * hist[j] / (double)tot;
			env->simg[i] = ft_interpol(
					env->color[(int)floor(hue * NB_COL * 2)],
					env->color[(int)(floor(hue * NB_COL * 2) + 1 ) % (NB_COL * 2)],
					hue - floor(hue));
		}
		else
			env->simg[i] = 0;
	}
}*/

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
