/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:12:29 by esuits            #+#    #+#             */
/*   Updated: 2017/12/13 18:44:34 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

t_mand	ft_init_mand(double x, double y, double iter);

void	*ft_julia_th(void	*arg)
{
	t_env_th	*tmp;
	int			start;
	int			end;
	t_cmpl		z;
	t_mand		c;

	tmp = (t_env_th*)arg;
	start = ((WIN_L * WIN_H) * tmp->part / THREADS) - 1;
	end = ((WIN_L * WIN_H) * (tmp->part + 1) /THREADS);
	while (++start < end)
	{
		z.x = (float)(start % WIN_L - WIN_L / 2 + tmp->env->center.x)
			/ (tmp->env->zoom * (WIN_L / 4));
		z.y = (float)(start / WIN_H - WIN_H / 2 + tmp->env->center.y)
			/ (tmp->env->zoom * (WIN_H / 4));
		c = tmp->env->julia;
		c = ft_mand_th_iter(z, c);
		if (c.iter == ITERATIONS)
			tmp->env->simg[start] = 0;
		else
		{
			c.iter = (int)floor(c.iter * (log(c.iter) / log (ITERATIONS)));
			tmp->env->simg[start ] = tmp->env->color[(int)c.iter % (2 * NB_COL)];
		/*	c.iter = c.iter + (log(log(ITERATIONS)) -
					log(log(c.x * c.x * c.y + c.y))) / log(2);
			tmp->env->simg[start] = tmp->env->color[(int)floor(c.iter) % NB_COL * 2];*/
		}
	}
	return (NULL);
}

void ft_julia_mult(t_env *env)
{
	pthread_t	thread[THREADS];
	t_env_th	env_i[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		env_i[i].part = i;
		env_i[i].env = env;
		pthread_create(&thread[i], NULL, ft_julia_th, &env_i[i]);
		++i;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread[i++], NULL);
}
