/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/16 18:35:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		forces_update_player(t_doom3d *app)
{
	player_move(app, move_upwards, app->player.velocity[1]);
	if (app->player.flying == true || player_is_grounded(app))
		app->player.velocity[1] = 0;
	else
		app->player.velocity[1] -= app->info.delta_time * CONST_SPEED;
}

void		forces_update_object(t_doom3d *app, t_3d_object *target)
{
	t_npc	*npc;

	npc = target->params;
	l3d_3d_object_translate(target,
		npc->velocity[0], npc->velocity[1], npc->velocity[2]);
	if (obj_is_grounded(app, target))
		npc->velocity[1] = 0;
	else
	{
		npc->velocity[1] += app->info.delta_time * CONST_SPEED;
	}
}
