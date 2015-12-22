/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:00:27 by jpiniau           #+#    #+#             */
/*   Updated: 2015/12/22 15:17:47 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void		ft_center_iso(int i, t_env env, t_point *p)
{
	static int ii;

	if (i == 1 && ii != 1)
	{
		ii = 1;
		p->x += (env.size_mat.height * TLE * 3);
	}
	else if (i == 0 && ii == 1)
	{
		ii = 0;
		p->x = 0;
	}
}

static int		ft_z(int z, int c)
{
	float	new_z;
	float	tmp;

	tmp = 0.0;
	if (c == 125 && z == 1)
		return (-1);
	if (c == 126 && z == -1)
		return (1);
	if ((c == 126 && z >= 0) || (c == 125 && z < 0))
		tmp = z * 1.5;
	else if ((c == 126 && z <= 0) || (c == 125 && z > 0))
		tmp = z / 1.5;
	if (tmp > 0)
		new_z = tmp - (int)tmp;
	else
		new_z = -tmp + (int)tmp;
	if (new_z >= 0.5 && tmp > 0)
		new_z = (int)tmp + 1;
	else if (new_z >= 0.5 && tmp < 0)
		new_z = (int)tmp - 1;
	else
		new_z = (int)tmp;
	return ((int)new_z);
}

static void		apply(t_env save, t_point p, int i, int m)
{
	transform(save.matrix.def, save.size_mat.height, p, &save);
	mlx_destroy_image(save.mlx, save.im);
	save.im = mlx_new_image(save.mlx, WIN_HEIGHT, WIN_WIDTH);
	fdf(save, i, m);
}

static t_point	switch_case(int action, t_point p, int *i, int *m)
{
	static int	x;
	static int	ii;

	x = *i == 1 && ii != 1 ? p.x : x;
	ii = ii != 1 && *i == 1 ? 1 : ii;
	p.y = action == S && p.y <= 10000 ? p.y + 10 : p.y;
	p.y = action == W && p.y >= -10000 ? p.y - 10 : p.y;
	p.x = action == D && p.x <= 10000 ? p.x + 10 : p.x;
	p.x = action == A && p.x >= -10000 ? p.x - 10 : p.x;
	p.zo = (action == Z && p.zo > -9) ? p.zo - 1 : p.zo;
	p.zo = (action == X && p.zo < 12) ? p.zo + 1 : p.zo;
	p.z = (action == 126 && p.z < 7) ? ft_z(p.z, action) : p.z;
	p.z = (action == 125 && p.z > -7) ? ft_z(p.z, action) : p.z;
	*i = action == P ? 0 : *i;
	*i = action == I ? 1 : *i;
	if (*m == 0)
		*m = action == M ? 1 : *m;
	else
		*m = action == M ? 0 : *m;
	if (action == R)
		p.x = *i == 1 ? x : 0;
	return (p);
}

void			action(t_env env, int action)
{
	static t_env	save;
	static t_point	p;
	static int		appel;
	static int		i;
	static int		m;

	if (appel != 1 || action == R)
	{
		p.x = 0;
		p.y = 0;
		p.z = 1;
		p.zo = 0;
		if (action != R)
			appel = 1;
	}
	if (action == 666)
		save = env;
	else
	{
		p = switch_case(action, p, &i, &m);
		ft_center_iso(i, env, &p);
		apply(save, p, i, m);
	}
}
