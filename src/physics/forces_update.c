/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/28 18:50:55 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Calculates forces resulting in velocity. Deceleration for horizontal forces
** gravity for vertical. Also updates e.g npc's state regardind jump, fall or
** groundedness.
** The forces (velocity) are applied to player position in player_move.
*/

void	forces_update_player(t_doom3d *app)
{
	float		deceleration;

	if (app->player.physics_state != physics_state_not_applied)
	{
		if (app->player.physics_state == physics_state_grounded)
			app->player.velocity[1] = 0;
		else if ((app->player.physics_state == physics_state_not_grounded)
			&& app->player.velocity[1] < PLAYER_MAX_SPEED / 3)
			app->player.velocity[1] += CONST_GRAVITY / 4;
	}
	if (app->player.physics_state != physics_state_grounded
		&& app->player.physics_state != physics_state_not_applied)
		deceleration = 1.02;
	else
		deceleration = 1.8;
	ml_vector3_copy((t_vec3){app->player.velocity[0] / deceleration,
		app->player.velocity[1], app->player.velocity[2] / deceleration},
		app->player.velocity);
	if (app->player.physics_state == physics_state_not_applied)
		app->player.velocity[1] = app->player.velocity[1] / deceleration;
}

static void	forces_update_npc(t_3d_object *npc_object)
{
	t_npc		*npc;
	float		deceleration;

	npc = npc_object->params;
	if (npc->physics_state != physics_state_not_applied)
	{
		if (npc->physics_state == physics_state_grounded)
			npc->velocity[1] = 0;
		else if (npc->physics_state == physics_state_falling
			&& npc->velocity[1] < PLAYER_MAX_SPEED * 8)
			npc->velocity[1] += CONST_GRAVITY;
	}
	if (npc->physics_state != physics_state_grounded
		&& npc->physics_state != physics_state_not_applied)
		deceleration = 1.000;
	else
		deceleration = 1.8;
	ml_vector3_copy((t_vec3){npc->velocity[0] / deceleration,
		npc->velocity[1], npc->velocity[2] / deceleration},
		npc->velocity);
}

/*
** Calculates forces resulting in velocity. Deceleration for horizontal forces
** gravity for vertical. Also updates e.g npc's state regardind jump, fall or
** groundedness.
** The forces (velocity) are then applied on the position of the object.
*/

void	update_object_forces(t_doom3d *app, t_3d_object *obj)
{
	t_vec3			velocity;
	t_vec3			add;
	static uint64_t	dt_sum;

	if (obj->type == object_type_npc)
	{
		if (dt_sum > FORCES_UPDATE_MS)
		{
			forces_update_npc(obj);
			dt_sum = 0;
		}
		dt_sum += app->info.delta_time;
		ml_vector3_copy(((t_npc *)obj->params)->velocity, velocity);
		ml_vector3_mul(velocity, app->info.delta_time * CONST_SPEED, add);
		l3d_3d_object_translate(obj, add[0], add[1], add[2]);
	}
}

static void	nudge_object_up(t_doom3d *app, t_3d_object *obj)
{
	while (obj_is_grounded(app, obj))
		l3d_3d_object_translate(obj, 0, -25, 0);
	if (!obj_is_grounded(app, obj))
		l3d_3d_object_translate(obj, 0, 25, 0);
}

void	update_object_physics_state(t_doom3d *app, t_3d_object *obj)
{
	t_npc			*npc;
	t_bool			is_grounded;

	if (obj->type == object_type_npc
		&& ((t_npc *)(obj->params))->type != npc_type_elevator
		&& ((t_npc *)(obj->params))->type != npc_type_crate)
	{
		npc = obj->params;
		if (npc->velocity[1] < 0)
			npc->physics_state = physics_state_jumping;
		else
		{
			is_grounded = obj_is_grounded(app, obj);
			if (npc->velocity[1] >= 0 && !is_grounded)
				npc->physics_state = physics_state_falling;
			if (is_grounded && npc->physics_state != physics_state_jumping)
			{
				npc->physics_state = physics_state_grounded;
				nudge_object_up(app, obj);
			}
		}
	}
}
