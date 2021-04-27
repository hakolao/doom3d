/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:48:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 01:12:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		delete_objects_set_for_deletion(t_doom3d *app)
{
	int32_t		i;
	int32_t		del_index;
	uint32_t	id;
	char		obj_type[128];
	t_3d_object	**objects;

	objects = app->active_scene->objects;
	l3d_temp_objects_destroy_if_expired(&app->active_scene->temp_objects);
	i = -1;
	while (++i < (int32_t)app->active_scene->num_deleted)
	{
		del_index = app->active_scene->deleted_object_i[i];
		if (objects[del_index] != NULL)
		{
			id = objects[del_index]->id;
			object_type_to_str(objects[del_index], obj_type);
			if (objects[del_index]->type == object_type_npc)
			{
				npc_destroy(objects[del_index]);
				if (app->is_debug)
					LOG_DEBUG("Deleted object %s, id %u that may have 3D animations", obj_type, id);
			}
			else
			{
				l3d_3d_object_destroy(objects[del_index]);
				if (app->is_debug)
					LOG_DEBUG("Deleted object %s, id %u", obj_type, id);
			}
			objects[del_index] = NULL;
		}
	}
}

static t_bool	should_update_npc_state(t_doom3d *app)
{
	static uint32_t	old_time;
	uint32_t		new_time;
	t_bool			update_npcs;

	new_time = SDL_GetTicks();
	if (!old_time)
		old_time = 0;
	app->active_scene->npc_update_timer += new_time - old_time;
	update_npcs = false;
	if (app->active_scene->npc_update_timer > 250)
	{
		app->active_scene->npc_update_timer -= 250;
		update_npcs = true;
		old_time = new_time;
	}
	return (update_npcs);
}

static void		finish_level(t_doom3d *app)
{
	app->current_level++;
	if (app->current_level < app->num_levels)
	{
		notify_user(app, (t_notification){
			.message = "New level",
			.type = notification_type_story, .time = 6000});
		push_custom_event(app, event_scene_reload, NULL, NULL);
	}
	else
	{
		app->current_level = 0;
		push_custom_event(app, event_scene_change,
			(void*)scene_id_main_menu, NULL);
		notify_user(app, (t_notification){
			.message = "Game over",
			.type = notification_type_story, .time = 6000});
	}
}

static t_bool	has_forces(t_3d_object *obj)
{
	return (obj->type == object_type_npc);
}

static void		update_object_by_type(t_doom3d *app, t_3d_object *obj,
					t_bool is_npc_update)
{
	if (has_forces(obj))
	{
		update_object_physics_state(app, obj);
		update_object_forces(app, obj);
	}
	if (obj->type == object_type_npc)
	{
		if (((t_npc*)obj->params)->animation_3d != NULL)
		{
			// ft_printf("here\n");
			// l3d_3d_object_rotate(obj, 0.0, 1.0, 0.0);
			anim_3d_frame_update(app, ((t_npc*)obj->params)->animation_3d);
		}
		if (is_npc_update && ((t_npc*)obj->params)->state != state_death_anim)
		{
			npc_update_state(app, obj);
		}
		if (((t_npc*)obj->params)->state != state_death_anim)
			npc_execute_behavior(app, obj);
	}
	else if (obj->type == object_type_projectile)
		projectile_update(app, obj);
	else if (obj->type == object_type_trigger)
	{
		if (l3d_aabb_collides(&app->player.aabb, &obj->aabb))
		{
			if (obj->params_type == trigger_player_end)
			{
				LOG_INFO("Hit End Trigger, finish level");
				finish_level(app);
			}
			else if (obj->params_type == trigger_weapon_drop_shotgun ||
					obj->params_type == trigger_weapon_drop_pistol ||
					obj->params_type == trigger_weapon_drop_rpg ||
					obj->params_type == trigger_item_jetpack)
				inventory_pickup_weapon_object(app, obj);
			else if (obj->params_type == trigger_item_key)
				inventory_pickup_key(app, obj);
			else if (obj->params_type == trigger_item_medkit)
				inventory_pickup_medkit(app, obj);
		}
	}
}

/*
** Updates objects every frame. In addition applies gravity / physics
** to objects & player. Handles object deletion
** Also keeps scene structures up to date (triangle tree)
*/

void			update_objects(t_doom3d *app)
{
	int32_t			i;
	t_bool			is_npc_update;
	t_3d_object		*obj;

	if (!(app->active_scene->scene_id == scene_id_main_game ||
		app->active_scene->scene_id == scene_id_editor3d))
		return ;
	if (app->active_scene->scene_id == scene_id_main_game)
		extend_all_objects_shading_opts(app, e_shading_depth);
	if (app->active_scene->scene_id == scene_id_editor3d)
		update_editor_light_sources(app);
	else if (!app->active_scene->is_paused &&
		app->active_scene->scene_id == scene_id_main_game)
	{
		is_npc_update = should_update_npc_state(app);
		i = -1;
		while (++i < (int32_t)(app->active_scene->num_objects +
			app->active_scene->num_deleted))
		{
			obj = app->active_scene->objects[i];
			if (!obj)
				continue ;
			update_object_by_type(app, obj, is_npc_update);
			update_light_sources(app, obj);
		}
		l3d_temp_objects_update_time(&app->active_scene->temp_objects,
			app->info.delta_time);
	}
	delete_objects_set_for_deletion(app);
	active_scene_update_after_objects(app->active_scene);
}