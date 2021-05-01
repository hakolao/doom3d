/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector4_cross.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 01:08:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Cross product of two vector4s
*/

void	ml_vector4_cross(t_vec4 v1, t_vec4 v2, t_vec4 res)
{
	res[0] = v1[1] * v2[2] - v2[1] * v1[2];
	res[1] = v1[2] * v2[0] - v2[2] * v1[0];
	res[2] = v1[0] * v2[1] - v2[0] * v1[1];
	res[4] = 1;
}
