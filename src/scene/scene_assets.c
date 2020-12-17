/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/17 17:09:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		scene_set_skybox_textures(t_scene *scene)
{
	scene->skybox_textures[0] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/front.bmp");
	scene->skybox_textures[1] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/left.bmp");
	scene->skybox_textures[2] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/top.bmp");
	scene->skybox_textures[3] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/back.bmp");
	scene->skybox_textures[4] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/right.bmp");
	scene->skybox_textures[5] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/bottom.bmp");
}

/*
** Loads assets by keys and files set in scene_data.c
** Hashmap = dictionary
*/

static void		assets_load(t_scene *scene, t_scene_files *data)
{
	int32_t		i;
	uint32_t	key;

	scene->models = hash_map_create(32);
	scene->textures = hash_map_create(32);
	scene->normal_maps = hash_map_create(32);
	i = -1;
	while (++i < (int32_t)data->num_assets_to_load)
	{
		key = data->asset_keys[i];
		if (data->texture_files[i] != NULL)
			hash_map_add(scene->textures, key,
				l3d_read_bmp_32bit_rgba_surface(data->texture_files[i]));
		if (data->normal_map_files[i] != NULL)
			hash_map_add(scene->normal_maps, key,
				l3d_read_bmp_32bit_rgba_surface(data->normal_map_files[i]));
		if (data->model_files[i] != NULL)
		{
			hash_map_add(scene->models, key,
				l3d_read_obj(data->model_files[i],
					hash_map_get(scene->textures, key),
					hash_map_get(scene->normal_maps, key)));
		}
	}
	scene_set_skybox_textures(scene);
}

static void		scene_texture_files_set(t_scene_files *data)
{
	data->texture_files[0] = "assets/textures/lava.bmp";
}

static void		scene_normal_files_set(t_scene_files *data)
{
	data->normal_map_files[0] = "assets/textures/lava_normal.bmp";
}

static void		scene_model_files_set(t_scene_files *data)
{
	data->model_files[0] = "assets/models/axismodels.obj";
}

void			scene_assets_load(t_scene *scene)
{
	t_scene_files	data;

	data.asset_keys[0] = 1;
	data.num_assets_to_load = 1;
	ft_memcpy(scene->asset_keys, data.asset_keys,
		sizeof(uint32_t) * data.num_assets_to_load);
	scene->num_loaded_assets = data.num_assets_to_load;
	scene_texture_files_set(&data);
	scene_normal_files_set(&data);
	scene_model_files_set(&data);
	assets_load(scene, &data);
}
