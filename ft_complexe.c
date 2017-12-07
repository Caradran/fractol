/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complexe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:04:22 by esuits            #+#    #+#             */
/*   Updated: 2017/12/06 17:58:48 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

t_cmpl		ft_cmpl_mult(t_cmpl a, t_cmpl b)
{
	t_cmpl	res;

	res.x = (a.x * b.x - a.y * b.y);
	res.y = (a.x * b.y + a.y * b.x);
	return (res);
}

t_cmpl		ft_cmpl_mod(t_cmpl z)
{
	t_cmpl res;

	res.y = 0;
	res.x = hypot(z.x, z.y);
	return (res);
}

t_cmpl		ft_cmpl_add(t_cmpl a, t_cmpl b)
{
	t_cmpl res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_cmpl		ft_cmpl_create_alg(double x, double y)
{
	t_cmpl res;

	res.x = x;
	res.y = y;
	return (res);
}

t_cmpl		ft_cmpl_create_geo(double r, double th)
{
	t_cmpl res;

	res.x = r * cos(th);
	res.y = r * sin(th);
	return (res);
}
