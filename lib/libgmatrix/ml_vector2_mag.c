/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector2_mag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 01:07:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Length of a vector2 (magnitude)
*/

float	ml_vector2_mag(t_vec2 v)
{
	size_t	i;
	float	res;

	i = -1;
	res = 0;
	while (++i < 2)
		res += v[i] * v[i];
	return (sqrt(res));
}
