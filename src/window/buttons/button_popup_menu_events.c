/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_popup_menu_events.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:05:06 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 17:50:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	button_popup_menu_events_handle(t_button_menu *button_menu,
			t_mouse mouse, SDL_Event event)
{
	button_group_events_handle(button_menu->menu, mouse, event);
	if (!(mouse.x >= button_menu->pos[0] &&
		mouse.x < button_menu->pos[0] + button_menu->background.w &&
		mouse.y >= button_menu->pos[1] &&
		mouse.y < button_menu->pos[1] + button_menu->background.h) &&
		(mouse.state & SDL_BUTTON_LMASK))
		button_menu->is_open = false;
}