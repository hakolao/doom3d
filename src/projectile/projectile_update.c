/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/30 21:57:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		transform_explosion_plane(t_doom3d *app,
					t_projectile *projectile, t_3d_object *explosion_effect)
{
	float			scale;

	if (!explosion_effect)
		return ;
	scale = projectile->radius /
		(ml_vector3_mag(explosion_effect->aabb.size) * 2.0);
	l3d_3d_object_scale(explosion_effect, scale, scale, scale);
	l3d_3d_object_rotate(explosion_effect, app->player.rot_x,
		-app->player.rot_y, 90);
}

static void		init_explosions(t_doom3d *app, t_3d_object **explosions,
										t_3d_object *model, t_vec3 pos)
{
	int32_t	i;

	explosions[0] = place_procedural_temp_object(app, model,
		(const char*[2]){"assets/textures/explosion1.bmp", NULL},
		pos, (int32_t[2]){100, 0});
	explosions[1] = place_procedural_temp_object(app, model,
		(const char*[2]){"assets/textures/explosion2.bmp", NULL},
		pos, (int32_t[2]){100, 100});
	explosions[2] = place_procedural_temp_object(app, model,
		(const char*[2]){"assets/textures/explosion3.bmp", NULL},
		pos, (int32_t[2]){100, 200});
	explosions[3] = place_procedural_temp_object(app, model,
		(const char*[2]){"assets/textures/explosion4.bmp", NULL},
		pos, (int32_t[2]){100, 300});
	explosions[4] = place_temp_object(app,
		(const char*[2]){"assets/models/light_sphere.obj", NULL},
		pos, (int32_t[2]){300, 0});
	i = -1;
	while (++i < 4)
		explosions[4]->material->shading_opts |= e_shading_luminous;
	l3d_3d_object_scale(explosions[4], 0.3, 0.3, 0.3);
	l3d_object_set_shading_opts(explosions[4],
		e_shading_invisible);
	l3d_3d_object_set_params(explosions[4], NULL, 0, light_type_explosion);
	explosions[4]->type = object_type_light;
}

void			projectile_explode_effect(t_doom3d *app,
					t_3d_object *projectile_obj)
{
	t_3d_object		*explosions[5];
	t_3d_object		*model;
	int32_t			i;
	t_vec3			add;
	t_vec3			pos;

	ml_vector3_mul(((t_projectile*)projectile_obj->params)->dir,
		-1 * 0.2 * app->unit_size, add);
	ml_vector3_add(projectile_obj->position, add, pos);
	model = l3d_plane_create(NULL, NULL);
	init_explosions(app, explosions, model, pos);
	l3d_3d_object_destroy(model);
	i = -1;
	while (++i < 4)
		transform_explosion_plane(app, projectile_obj->params,
			explosions[i]);
	push_custom_event(app,
		event_effect_play, (void*)sf_explsion2, s_ini(0, 1, st_game,
		distance_vol(0.7, sound_mag(app->player.pos, projectile_obj->position),
									50000)));
}

void			projectile_on_hit(t_doom3d *app,
					t_3d_object *projectile_obj, t_3d_object *hit_obj)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	if (hit_obj && hit_obj->type == object_type_npc)
	{
		ml_vector3_sub(hit_obj->aabb.center, projectile_obj->aabb.center, dist);
		if ((mag = ml_vector3_mag(dist)) < projectile->radius)
		{
			damage = projectile->damage * (1 - (mag / projectile->radius));
			npc_trigger_onhit(app, hit_obj, damage);
		}
	}
	ml_vector3_sub(projectile_obj->aabb.center, app->player.aabb.center, dist);
	if ((mag = ml_vector3_mag(dist)) < projectile->radius)
	{
		damage = projectile->damage * (1 - (mag / projectile->radius));
		player_onhit(app, damage);
	}
}

void			projectile_update(t_doom3d *app, t_3d_object *projectile_obj)
{
	t_projectile	*projectile;
	t_vec3			add;

	projectile = projectile_obj->params;
	ml_vector3_mul(projectile->dir,
		projectile->speed * app->info.delta_time * CONST_SPEED, add);
	l3d_3d_object_translate(projectile_obj, add[0], add[1], add[2]);
	projectile->traveled += ml_vector3_mag(add);
	if (projectile_obj && projectile->traveled > projectile->range)
	{
		push_custom_event(app, event_object_delete,
			projectile_obj, NULL);
		return ;
	}
	projectile_handle_collision(app, projectile_obj);
}
