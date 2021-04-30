/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_move_to_waypoint.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:07:07 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/30 13:47:08 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_get_dir_to_next_waypoint(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;
	t_vec3	diff;

	npc = obj->params;
	if (npc->patrol_path[0] == NULL)
		return ;
	if (npc->patrol_path[npc->patrol_path_index] == NULL)
		npc->patrol_path_index = 0;
	if (npc->type != npc_type_elevator)
	{
		if (!npc->attack_path[0])
		{
			npc_find_path(app, npc, obj->position, npc->patrol_path[npc->patrol_path_index]->position);
		}
		if (npc_get_dir_to_next_attack_waypoint(app, obj))
		{
			if (app->is_debug)
				LOG_DEBUG("Npc patrol path index %d", npc->patrol_path_index);
			npc->patrol_path_index++;
		}
	}
	else
	{
		if (npc->patrol_path_index != -1)
		{
			ml_vector3_sub(obj->position,
						npc->patrol_path[npc->patrol_path_index]->position, diff);
			ml_vector3_normalize(diff, npc->dir);
			ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
		}
		if (ml_vector3_mag(diff) < app->unit_size * 1.5)
		{
			npc->patrol_path_index++;
			if (npc->type == npc_type_elevator)
				npc->speed = 0;
		}
	}
	// ft_printf("object id %d dir set to {%f, %f, %f}\n", obj->id, npc->dir[0], npc->dir[1], npc->dir[2]); //test
	// ft_printf("object id %d patrol_path_index is %d\n", obj->id, npc->patrol_path_index); //test
	// ft_printf("object id %d is patrolling at {%f, %f, %f}\n", obj->id, obj->position[0], obj->position[1], obj->position[2]); //test
}

t_bool	npc_get_dir_to_next_attack_waypoint(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;
	t_vec3	diff;

	npc = obj->params;
	if (npc->attack_path[0] == NULL || npc->attack_path[npc->attack_path_index] == NULL)
	{
		npc->attack_path_index = 0;
		ft_memset(npc->attack_path, 0, sizeof(t_3d_object *) * MAX_PATH_NODE_NETWORK_SIZE);
		return (true);
	}
	ml_vector3_sub(obj->position,
					npc->attack_path[npc->attack_path_index]->position, diff);
	ml_vector3_normalize(diff, npc->dir);
	ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
	if (ml_vector3_mag(diff) < app->unit_size * 1.5)
		npc->attack_path_index++;
	return (false);
}

void	npc_move_step_to_waypoint(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;

	(void)app;
	npc = obj->params;
	if (obj->params_type == npc_type_elevator)
	{
		l3d_3d_object_translate(obj, npc->dir[0], npc->dir[1], npc->dir[2]);
		l3d_object_aabb_update(obj);
	}
	else
	{
		if (npc->animation_3d &&
			npc->animation_3d->current_clip != anim_3d_type_move)
			anim_3d_clip_loop(app, obj, anim_3d_type_move, 0);
		l3d_3d_object_translate(obj, npc->dir[0], 0, npc->dir[2]);
		l3d_object_aabb_update(obj);
	}
}
