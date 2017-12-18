/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow_mandel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:25:04 by esuits            #+#    #+#             */
/*   Updated: 2017/12/18 22:29:25 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

t_cmpl	ft_cmpl_pow(t_cmpl z, int a)
{
	double tmpx;
	double tmpy;
	double tmp;

	tmpx = z.x;
	tmpy = z.y;
	if (a == 0)
		return (ft_cmpl_create_alg(1, 0));
	while (a > 1)
	{
		tmp = z.x * tmpx - tmpy * z.y;
		z.y = tmpx * z.y + z.x * tmpy;
		z.x = tmp;
		a--;
	}
	return (z);
}

t_mand	ft_mand_pow(t_cmpl z, t_mand c, int i)
{
	t_cmpl tmp;

	tmp = ft_cmpl_create_alg(c.x, c.y);
	c.iter = 0;
	while (++c.iter < ITERATIONS)
	{
		if (z.x * z.x + z.y * z.y > 4)
			return (c);
		z = ft_cmpl_add(ft_cmpl_pow(z, i), tmp);
	}
	return (c);
}

void	*ft_mand_pow_th(void *arg)
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
		c = ft_mand_pow(zo, c, tmp->env->pow);
		tmp->env->simg[start] = 0;
		if (c.iter != ITERATIONS)
		{
			c.iter = (int)floor(c.iter * (log(c.iter) / log(ITERATIONS)));
			tmp->env->simg[start] = tmp->env->color[(int)c.iter % (2 * NB_COL)];
		}
	}
	return (NULL);
}

void	ft_mand_pow_mult(t_env *env)
{
	pthread_t	thread[THREADS];
	t_env_th	env_i[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		env_i[i].part = i;
		env_i[i].env = env;
		if (pthread_create(&thread[i], NULL, ft_mand_pow_th, &env_i[i]))
			return ;
		++i;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread[i++], NULL);
}
