/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_read_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:56:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:57:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

int32_t			read_obj_texture(t_3d_object *obj,
					t_doom3d *app, char *contents)
{
	int32_t		len;
	int32_t		offset;
	char		buf[128];
	const char	*filename;

	ft_memcpy(&len, contents, sizeof(uint32_t));
	offset = sizeof(uint32_t);
	ft_memset(buf, 0, sizeof(buf));
	ft_memcpy(buf, contents + offset, len);
	offset += len;
	filename = texture_file_key(buf, app);
	obj->material->texture = hash_map_get(app->active_scene->textures,
		(int64_t)filename);
	if (filename)
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filename);
	return (offset);
}

int32_t			read_obj_normal_map(t_3d_object *obj,
					t_doom3d *app, char *contents)
{
	int32_t		len;
	int32_t		offset;
	char		buf[128];
	const char	*filename;

	ft_memcpy(&len, contents, sizeof(uint32_t));
	offset = sizeof(uint32_t);
	ft_memset(buf, 0, sizeof(buf));
	ft_memcpy(buf, contents + offset, len);
	offset += len;
	filename = normal_map_file_key(buf, app);
	obj->material->normal_map = hash_map_get(app->active_scene->normal_maps,
		(int64_t)filename);
	if (filename)
		hash_map_add(app->active_scene->object_normal_maps, obj->id,
			(void*)filename);
	return (offset);
}

float			pitch_from_rotation_matrix(t_mat4 rotation)
{
	float	pitch1;
	float	pitch2;

	if (rotation[0][2] != 1 && rotation[0][2] != -1)
	{
		pitch1 = -1 * asin(rotation[0][2]);
		pitch2 = M_PI - pitch1;
		if (rotation[0][0] < 0 || rotation[2][2] < 0)
			return (pitch2);
		else
			return (pitch1);
	}
	return (rotation[0][2] > 0 ? -M_PI / 2.0 : M_PI / 2.0);
}