/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:19:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 19:36:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		scene_texture_files_set_sub1(t_asset_files *data)
{
	data->texture_files[data->num_textures++] =
		"assets/textures/door_metal_h.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/door_metal_v.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/wall_metal_panel.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_redsand.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/shotgun_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/pistol_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/rpg_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion1.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion2.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion3.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion4.bmp";
	data->texture_files[data->num_textures++] = "assets/textures/blood.bmp";
}

static void		scene_texture_files_set_sub2(t_asset_files *data)
{
	data->texture_files[data->num_textures++] = NPC_MONSTER01_TEXTURE;
	data->texture_files[data->num_textures++] = NPC_MONSTER01A_TEXTURE;
	data->texture_files[data->num_textures++] = NPC_MONSTER01B_TEXTURE;
	data->texture_files[data->num_textures++] =
		"assets/textures/monster_02/monster02_diffuse.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/npc_projectile_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_corner_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_corner_inner.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_corner_outer.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_straight_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_straight_wall.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_t_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_x_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/keypad_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/medkit_texture.bmp";
}

void			scene_texture_files_set(t_asset_files *data)
{
	data->texture_files[data->num_textures++] =
		"assets/textures/lava.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/rock.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/crate.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_dirt.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal_2048.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal2_2048.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal3.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal4.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal4_box.bmp";
	scene_texture_files_set_sub1(data);
	scene_texture_files_set_sub2(data);
}