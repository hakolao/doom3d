/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:51:46 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/13 13:03:56 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_shoot_ray(t_doom3d *app, t_vec3 origin, t_vec3 dir)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;
	t_vec3	dist;
	char	object_type[128];

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit);
		if (closest_triangle_hit != NULL)
		{
			ml_vector3_sub(closest_triangle_hit->hit_point, origin, dist);
			object_type_to_str(closest_triangle_hit->triangle->parent,
				object_type);
			ft_printf("Hit %s, at unit distance: %f, ", object_type,
				ml_vector3_mag(dist) / app->unit_size);
			ml_vector3_print(closest_triangle_hit->hit_point);
			if (ml_vector3_mag(dist) <= app->player.equipped_weapon->range)
				if (closest_triangle_hit->triangle->parent->type == object_type_npc)
					npc_trigger_onhit(app, closest_triangle_hit->triangle->parent,
									app->player.equipped_weapon->damage_per_hit);
		}
		l3d_delete_hits(&hits);
	}
}

static void		place_projectile_object_in_scene(t_doom3d *app,
					t_projectile *projectile, t_vec3 origin, t_vec3 rot)
{
	t_3d_object *obj;

	place_scene_object(app,
		(const char*[3]){projectile->model_key, projectile->texture_key,
					projectile->normal_map_key}, origin);
	obj = app->active_scene->objects[app->active_scene->last_object_index];
	obj->type = object_type_projectile;
	l3d_3d_object_set_params(obj, projectile, sizeof(t_projectile),
		projectile->type);
	l3d_3d_object_rotate(obj, rot[0], rot[1], rot[2]);
	l3d_3d_object_scale(obj, 0.1, 0.1, 0.1);
	ft_printf("Spawned projectile, id = |%d|\n",
		app->active_scene->objects[app->active_scene->last_object_index]->id); //test
}

void	player_shoot_projectile(t_doom3d *app, t_vec3 origin)
{
	t_projectile	projectile;
	t_vec3			rot;

	ft_memset(&projectile, 0, sizeof(t_projectile));
	ft_memcpy(&projectile,
		&app->projectile_data[app->player.equipped_weapon->projectile],
		sizeof(t_projectile));
	ml_vector3_copy(app->player.forward, projectile.dir);
	rot[0] = app->player.rot_x + 90;
	rot[1] = -app->player.rot_y;
	rot[2] = 90;
	ml_vector3_mul(projectile.dir, projectile.speed, projectile.dir);
	place_projectile_object_in_scene(app, &projectile, origin, rot);
}