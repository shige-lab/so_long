/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:10:10 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/07 15:30:17 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static t_bool	check_middle_row(char *row, size_t width, t_game *game)
{
	if (row[0] != '1' || row[width - 1] != '1')
		return (FALSE);
	while (*row)
	{
		if (ft_strchr("10CPE\n", *row) == NULL)
			return (FALSE);
		if (*row == 'C')
			game->map.num_collectible += 1;
		if (*row == 'P')
		{
			game->map.num_exit += 1;
			if (game->map.num_exit > 1)
				return (1);
		}
		if (*row == 'E')
			game->map.num_s_position += 1;
		row++;
	}
	return (TRUE);
}

static t_bool	check_edge_row(char *row)
{
	while (*row)
	{
		if (*row != '1' && *row != '\n')
			return (FALSE);
		row++;
	}
	return (TRUE);
}

static size_t	map_row_len(const char *row)
{
	size_t	i;

	i = 0;
	while (*row != '\0')
	{
		if (ft_strchr("10CPE", *row))
			i++;
		row++;
	}
	return (i);
}

static t_bool	get_map_info(t_list *map, t_game *game)
{
	size_t	i;

	i = 0;
	game->map.width = map_row_len(map->content);
	while (map->content != NULL)
	{
		if (i != 0 && game->map.width != map_row_len(map->content))
			return (FALSE);
		if (i == 0 || i + 1 == game->map.height)
		{
			if (check_edge_row(map->content) == FALSE)
				return (FALSE);
		}
		else
		{
			if (check_middle_row(map->content, game->map.width, game) == FALSE)
				return (FALSE);
		}
		i++;
		map = map->next;
	}
	return (TRUE);
}

void	get_map_data(int fd, t_game *game)
{
	t_list	*map;
	t_list	*tmp;

	game->map.height = 0;
	tmp = ft_lstnew(get_next_line(fd));
	map = tmp;
	while (tmp->content != NULL)
	{
		game->map.height++;
		tmp->next = ft_lstnew(get_next_line(fd));
		tmp = tmp->next;
	}
	if (get_map_info(map, game) == FALSE)
	{
		ft_lstclear(&map, free);
		error_exit("invalid map");
	}
	move_list_to_double_pointer(game, map);
}
