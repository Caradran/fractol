/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 20:01:23 by esuits            #+#    #+#             */
/*   Updated: 2017/12/22 19:46:29 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

t_mand	ft_perpendic(t_cmpl z, t_mand c)
{
	double tmp;

	c.iter = 0;
	while (++c.iter < ITERATIONS)
	{
		if (z.x * z.x + z.y * z.y > 4)
			return (c);
		tmp = z.x;
		z.x = fabs(z.x * z.x - z.y * z.y + c.x);
		z.y = -2 * tmp * z.y + c.y;
	}
	return (c);
}

void	*ft_perpendic_th(void *arg)
{
	t_env_th	*tmp;
	t_cmpl		zo;
	int			start;
	int			end;
	t_mand		c;

	tmp = (t_env_th*)arg;
	zo = ft_cmpl_create_alg(0, 0);
	start = ((WIN_L * WIN_H) * tmp->part / THREADS) - 1;
	end = (WIN_L * WIN_H) * (tmp->part + 1) / THREADS;
	while (++start < end)
	{
		c.x = (double)(start % WIN_L - WIN_L / 2 + tmp->env->center.x)
			/ (tmp->env->zoom * (WIN_L / 4));
		c.y = (double)(floor(start / WIN_L) - WIN_H / 2 + tmp->env->center.y)
			/ (tmp->env->zoom * (WIN_H / 4));
		c = ft_perpendic(zo, c);
		tmp->env->simg[start] = 0;
		if (c.iter != ITERATIONS)
		{
			c.iter = (int)floor(c.iter * (log(c.iter) / log(ITERATIONS)));
			tmp->env->simg[start] = tmp->env->color[(int)c.iter % (2 * NB_COL)];
		}
	}
	return (NULL);
}

void	ft_perpendic_mult(t_env *env)
{
	pthread_t	thread[THREADS];
	t_env_th	env_i[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		env_i[i].part = i;
		env_i[i].env = env;
		if (pthread_create(&thread[i], NULL, ft_perpendic_th, &env_i[i]))
			return ;
		++i;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread[i++], NULL);
}

void	*ft_julia_perpendic_th(void *arg)
{
	t_env_th	*tmp;
	int			start;
	int			end;
	t_cmpl		z;
	t_mand		c;

	tmp = (t_env_th*)arg;
	start = ((WIN_L * WIN_H) * tmp->part / THREADS) - 1;
	end = ((WIN_L * WIN_H) * (tmp->part + 1) / THREADS);
	while (++start < end)
	{
		z.x = (double)(start % WIN_L - WIN_L / 2 + tmp->env->center.x)
			/ (tmp->env->zoom * (WIN_L / 4));
		z.y = (double)(start / WIN_L - WIN_H / 2 + tmp->env->center.y)
			/ (tmp->env->zoom * (WIN_H / 4));
		c = tmp->env->julia;
		c = ft_perpendic(z, c);
		tmp->env->simg[start] = 0;
		if (c.iter != ITERATIONS)
		{
			c.iter = (int)floor(c.iter * (log(c.iter) / log(ITERATIONS)));
			tmp->env->simg[start] = tmp->env->color[(int)c.iter % (2 * NB_COL)];
		}
	}
	return (NULL);
}

void	ft_julia_perpendic_mult(t_env *env)
{
	pthread_t	thread[THREADS];
	t_env_th	env_i[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		env_i[i].part = i;
		env_i[i].env = env;
		pthread_create(&thread[i], NULL, ft_julia_perpendic_th, &env_i[i]);
		++i;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread[i++], NULL);
}
