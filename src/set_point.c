/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/31 15:57:33 by jpiniau           #+#    #+#             */
/*   Updated: 2015/11/12 13:52:57 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	set_point(void)
{
	t_point p;

	p.x = 0;
	p.y = 0;
	p.z = 1;
	p.zo = 0;
	return (p);
}
