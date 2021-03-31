/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:35:21 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/31 00:23:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_3d_object	*place_npc_object_in_scene(t_doom3d *app, t_npc *npc, t_vec3 pos)
{
	t_3d_object *obj;

	place_scene_object(app,
		(const char*[3]){npc->model_key, npc->texture_key, npc->normal_map_key},
		pos);
	obj = app->active_scene->objects[app->active_scene->last_object_index];
	obj->type = object_type_npc;
	l3d_3d_object_scale(obj, npc->model_scale, npc->model_scale, npc->model_scale);
	npc->parent = obj;
	l3d_3d_object_set_params(obj, npc, sizeof(t_npc), npc->type);
	if (npc->type == npc_type_default || npc->type == npc_type_ranged)
		l3d_3d_object_rotate(obj, 0, 180, 180);//hardcoded for specific model
	l3d_3d_object_rotate(obj, 0, npc->angle, 0);
	return (obj);
}

void				parse_npc_type(t_doom3d *app, t_npc *npc, int type)
{
	if (type == npc_type_default)
	{
		npc_default(app, npc, NULL);
		if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;
		}
	}
	if (type == npc_type_ranged)
	{
		npc_ranged(app, npc, NULL);
		if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;
		}
	}
	if (type == npc_type_elevator)
	{
		npc_elevator(app, npc, NULL);
	}
}

/*
** spawn on position facing direction with given model
*/

t_3d_object			*npc_spawn(t_doom3d *app, t_vec3 pos, float angle, int type)
{
	t_npc		npc;
	t_3d_object	*obj;

	ft_memset(&npc, 0, sizeof(t_npc));
	npc.angle = angle;
	parse_npc_type(app, &npc, type);
	obj = place_npc_object_in_scene(app, &npc, pos);
	return (obj);
}
