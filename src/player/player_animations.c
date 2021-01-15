/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:35:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/12 21:42:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_surface			*get_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/shotgun_animation.bmp"));
	else if (app->player.equipped_weapon->id == weapon_glock)
		return (hash_map_get(app->active_scene->animation_textures,
			(int64_t)"assets/animations/glock_shoot_animation.bmp"));
	return (NULL);
}

static void			set_shotgun_default_anim(t_sprite_anim *anim)
{
	anim->frames[0].width = 480;
	anim->frames[0].height = 528;
	anim->frames[0].x_offset = 0;
	anim->frames[0].y_offset = 0;
	anim->num_frames = 1;
	anim->id = anim_shotgun_shoot;
	anim->interruptable = true;
	anim->frame_time = 100;
}

static void			set_shotgun_reload_anim(t_sprite_anim *anim)
{
	anim->current_frame = 0;
	anim->frames[0].width = 480;
	anim->frames[1].width = 480;
	anim->frames[2].width = 480;
	anim->frames[0].height = 528;
	anim->frames[1].height = 528;
	anim->frames[2].height = 528;
	anim->frames[0].x_offset = 480 * 4;
	anim->frames[1].x_offset = 480 * 5;
	anim->frames[2].x_offset = 480 * 6;
	anim->frames[0].y_offset = 0;
	anim->frames[1].y_offset = 0;
	anim->frames[2].y_offset = 0;
	anim->num_frames = 3;
	anim->id = anim_shotgun_reload;
	anim->interruptable = false;
	anim->frame_time = 100;
}

static void			set_shotgun_shoot_anim(t_sprite_anim *anim)
{
	anim->current_frame = 0;
	anim->frames[0].width = 480;
	anim->frames[1].width = 480;
	anim->frames[2].width = 480;
	anim->frames[3].width = 480;
	anim->frames[0].height = 528;
	anim->frames[1].height = 528;
	anim->frames[2].height = 528;
	anim->frames[3].height = 528;
	anim->frames[0].x_offset = 0;
	anim->frames[1].x_offset = 480 * 1;
	anim->frames[2].x_offset = 480 * 2;
	anim->frames[3].x_offset = 480 * 3;
	anim->frames[0].y_offset = 0;
	anim->frames[1].y_offset = 0;
	anim->frames[2].y_offset = 0;
	anim->frames[3].y_offset = 0;
	anim->num_frames = 4;
	anim->id = anim_shotgun_shoot;
	anim->interruptable = false;
	anim->frame_time = 100;
}

static void			set_glock_default_anim(t_sprite_anim *anim)
{
	anim->frames[0].width = 960;
	anim->frames[0].height = 540;
	anim->frames[0].x_offset = 0;
	anim->frames[0].y_offset = 0;
	anim->num_frames = 1;
	anim->id = anim_glock_default;
	anim->interruptable = true;
	anim->frame_time = 30;
}

static void			set_glock_reload_anim(t_sprite_anim *anim)
{
	anim->frames[0].width = 960;
	anim->frames[0].height = 540;
	anim->frames[0].x_offset = 0;
	anim->frames[0].y_offset = 0;
	anim->num_frames = 1;
	anim->id = anim_glock_shoot;
	anim->interruptable = false;
	anim->frame_time = 30;
}

static void			set_glock_shoot_anim(t_sprite_anim *anim)
{
	int32_t		i;

	anim->num_frames = 9;
	i = -1;
	while (++i < anim->num_frames)
	{
		anim->frames[i].width = 960;
		anim->frames[i].height = 540;
		anim->frames[i].x_offset = i * 960;
		anim->frames[i].y_offset = 0;
	}
	anim->id = anim_glock_reload;
	anim->interruptable = false;
	anim->frame_time = 30;
}

void	player_animations_init(t_doom3d *app)
{
	set_shotgun_default_anim(&app->animations[anim_shotgun_default]);
	set_shotgun_reload_anim(&app->animations[anim_shotgun_reload]);
	set_shotgun_shoot_anim(&app->animations[anim_shotgun_shoot]);
	set_glock_default_anim(&app->animations[anim_glock_default]);
	set_glock_reload_anim(&app->animations[anim_glock_reload]);
	set_glock_shoot_anim(&app->animations[anim_glock_shoot]);
}

static void				set_player_animation(t_doom3d *app, uint32_t animation_id)
{
	t_sprite_anim *curr_player_anim;

	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	if (!(curr_player_anim->is_finished || curr_player_anim->interruptable))
		return ;
	app->animations[app->player_hud.curr_animation].current_frame = 0;
	app->animations[app->player_hud.curr_animation].frame_time_left =
		app->animations[app->player_hud.curr_animation].frame_time;
	app->animations[app->player_hud.curr_animation].is_finished = false;
	app->player_hud.curr_animation = animation_id;
}

void					set_player_shoot_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_shoot);
	else if (app->player.equipped_weapon->id == weapon_glock)
		set_player_animation(app, anim_glock_shoot);
}

void					set_player_default_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_default);
	else if (app->player.equipped_weapon->id == weapon_glock)
		set_player_animation(app, anim_glock_default);
	else
		set_player_animation(app, anim_none);
}

void					set_player_reload_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_reload);
	else if (app->player.equipped_weapon->id == weapon_glock)
		set_player_animation(app, anim_glock_reload);
}

void	doom3d_player_animation_update(t_doom3d *app)
{
	t_sprite_anim *curr_player_anim;

	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	if (app->active_scene->scene_id != scene_id_main_game ||
		curr_player_anim->is_finished)
		return ;
	curr_player_anim->frame_time_left -= app->info.delta_time;
	if (curr_player_anim->frame_time_left <= 0)
	{
		curr_player_anim->frame_time_left = 0;
		curr_player_anim->current_frame++;
		curr_player_anim->frame_time_left =
			curr_player_anim->frame_time;
		if (curr_player_anim->current_frame >= curr_player_anim->num_frames)
		{
			curr_player_anim->is_finished = true;
			curr_player_anim->current_frame = 0;
		}
	}
}