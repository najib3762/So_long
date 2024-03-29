/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoussa <namoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:28:08 by namoussa          #+#    #+#             */
/*   Updated: 2024/03/07 19:22:54 by namoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/header_bonus.h"

int	ft_validate_file(char *file)
{
	char	*point;

	point = ft_strchr(file, '.');
	if (point == NULL)
		return (0);
	if ((ft_strcmp(".ber", point)) == 0)
		return (1);
	return (0);
}

void	ft_height(t_data *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error("Error\nFile openning\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		data->game->height += 1;
		free(line);
		line = NULL;
	}
	close(fd);
}

void	ft_map_2d(t_data *data, char *file)
{
	int		fd;
	char	*line;
	int		h;

	line = NULL;
	h = data->game->height;
	data->game->map = (char **)malloc(sizeof(char *) * (h + 1));
	if (data->game->map == NULL)
		print_error("Error\nMemory allocation failed\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error("Error\nFile openning\n");
	h = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		data->game->map[h] = ft_strdup(line);
		h++;
		free(line);
		line = NULL;
	}
	data->game->map[h] = NULL;
	close(fd);
}

int	ft_read_map(t_data *data, char *file)
{
	int	out;

	if (!(ft_validate_file(file)))
		print_error("Error\nInvalid file\n");
	ft_height(data, file);
	if (data->game->height == 0)
		print_error("Error\nMap is empty\n");
	ft_map_2d(data, file);
	out = ft_validate_map(data);
	if (out > 0)
		ft_display_error(out, data);
	data->player->pos_x = data->game->player_x * ASSET_SIZ;
	data->player->pos_y = data->game->player_y * ASSET_SIZ;
	return (0);
}
