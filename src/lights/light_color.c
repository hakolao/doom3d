/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:52:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 13:56:25 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

uint32_t	get_light_emit_color(t_3d_object *light_obj)
{
	t_light_type	light_type;

	if (light_obj->type == object_type_light)
	{
		light_type = light_obj->params_type;
		if (light_type == light_type_yellow)
			return (L3D_COLOR_YELLOW);
		if (light_type == light_type_white)
			return (L3D_COLOR_WHITE);
		else if (light_type == light_type_red)
			return (L3D_COLOR_RED);
		else if (light_type == light_type_green)
			return (L3D_COLOR_GREEN);
		else if (light_type == light_type_blue)
			return (L3D_COLOR_BLUE);
		else if (light_type == light_type_cyan)
			return (L3D_COLOR_CYAN);
		else if (light_type == light_type_explosion)
			return (L3D_COLOR_EXPLOSION);
		return (L3D_COLOR_YELLOW);
	}
	else
		return (L3D_COLOR_EXPLOSION);
}

t_shading_opts	get_light_shading(t_light_type light_type)
{
	if (light_type == light_type_white)
		return (e_shading_white);
	if (light_type == light_type_yellow)
		return (e_shading_yellow);
	else if (light_type == light_type_red)
		return (e_shading_red);
	else if (light_type == light_type_green)
		return (e_shading_green);
	else if (light_type == light_type_cyan)
		return (e_shading_cyan);
	return (e_shading_yellow);
}
