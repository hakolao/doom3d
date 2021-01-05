/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:09:52 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/05 18:51:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static char	*get_object_texture_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_textures, obj->id));
}

static char	*get_object_normal_map_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_normal_maps, obj->id));
}

static void	write_obj_content(int32_t fd, t_doom3d *app, t_3d_object *obj)
{
	int32_t			i;
	char			*texture_file;
	char			*normal_map_file;
	int32_t			len;
	int32_t			ret;

	// !Write the object as is (shallow, (has pointers))
	ret = write(fd, obj, sizeof(t_3d_object));
	// !Write the vertices
	i = -1;
	while (++i < (int32_t)obj->num_vertices)
		ret = write(fd, obj->vertices[i], sizeof(t_vertex));
	// !Write the triangles
	i = -1;
	while (++i < (int32_t)obj->num_triangles)
		ret = write(fd, &obj->triangles[i], sizeof(t_triangle));
	// !Write the texture & normal maps filenames, and the length of those strs
	texture_file = get_object_texture_filename(app->active_scene, obj);
	len = ft_strlen(texture_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, texture_file, len);
	normal_map_file = get_object_normal_map_filename(app->active_scene, obj);
	len = ft_strlen(normal_map_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, normal_map_file, len);
	// !Write the shading opts
	ret = write(fd, &obj->material->shading_opts, sizeof(uint32_t));
}


static void	write_npc_content(int32_t fd, t_npc *npc)
{
	int32_t			ret;

	ret = write(fd, &npc->type, sizeof(t_npc_type));
	ret = write(fd, &npc->id, sizeof(uint32_t));
	ret = write(fd, &npc->obj->id, sizeof(uint32_t));
	ret = write(fd, npc->pos, sizeof(t_vec3));
	ret = write(fd, &npc->angle, sizeof(float));
}

static void	write_map(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		ret;
	t_list		*node;
	t_npc		*npc;

	ret = write(fd, "MAP\0", 4);
	ret = write(fd, &app->active_scene->num_objects, sizeof(uint32_t));
	ret = write(fd, &app->active_scene->num_npcs, sizeof(uint32_t));
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
			write_obj_content(fd, app, app->active_scene->objects[i]);
	i = 0;
	node = app->active_scene->npc_list;
	while (node && i < (int32_t)app->active_scene->num_npcs)
	{
		npc = (t_npc*)node->content;
		write_npc_content(fd, npc);
		node = node->next;
		i++;
	}
}

void		save_map(t_doom3d *app)
{
	int32_t			fd;
	char			filename[128];

	ft_sprintf(filename, "assets/map_data/%s",
		app->editor.editor_filename, app->editor.editor_filename);
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		exit(EXIT_FAILURE);
	write_map(fd, app);
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		exit(EXIT_FAILURE);
}
