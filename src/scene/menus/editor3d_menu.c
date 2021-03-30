/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:29 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/30 14:34:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void				editor_popup_menu_create(t_doom3d *app,
						t_editor_menu_index new_menu,
						t_vec2 pos)
{
	t_button_group	*button_menu;

	if (new_menu == editor_menu_objects)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.model_files,
			.num_buttons = app->active_scene->asset_files.num_models,
			.on_click = on_objects_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_textures)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.texture_files,
			.num_buttons = app->active_scene->asset_files.num_textures,
			.on_click = on_textures_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_normalmaps)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.normal_map_files,
			.num_buttons = app->active_scene->asset_files.num_normal_maps,
			.on_click = on_normmaps_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_prefabs)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.prefab_names,
			.num_buttons = app->active_scene->asset_files.num_prefabs,
			.on_click = on_prefab_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_npcs)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.npc_names,
			.num_buttons = app->active_scene->asset_files.num_npcs,
			.on_click = on_npc_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_triggers)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.trigger_names,
			.num_buttons = app->active_scene->asset_files.num_triggers,
			.on_click = on_trigger_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_lights)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[1]){"Light Source"},
			.num_buttons = 1,
			.on_click = on_light_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else
		return ;
	app->editor.editor_menu =
		button_popup_menu_create(button_menu, pos, 3,
			(uint32_t[2]){CLEAR_COLOR, 0xffffffff});
}

void				editor3d_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus =
		ft_calloc(sizeof(t_button_group*) * 3)), "Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[9]){
				"Exit",
				"Save",
				"Objects",
				"Textures",
				"NormMaps",
				"Prefabs",
				"Characters",
				"Triggers",
				"Lights"},
			.num_buttons = 9,
			.on_click = on_editor_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->menus[1] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[1]){
				"Delete"},
			.num_buttons = 1,
			.on_click = on_delete_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->menus[1]->is_active = false;
	app->active_scene->menus[2] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[1]){
				"New"},
			.num_buttons = 1,
			.on_click = on_new_level_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 3;
}
