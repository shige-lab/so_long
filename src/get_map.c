/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:10:10 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/12 18:23:07 by tshigena         ###   ########.fr       */
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
			game->map.num_s_position += 1;
			if (game->map.num_s_position > 1)
				return (FALSE);
		}
		if (*row == 'E')
			game->map.num_exit += 1;
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
	if (!game->map.num_collectible || !game->map.num_exit
		|| !game->map.num_s_position)
		return (FALSE);
	return (TRUE);
}

void	get_map_data(int fd, t_game *game)
{
	t_list	*current;
	t_list	head;

	game->map.height = 0;
	errno = 0;
	head.next = NULL;
	current = &head;
	while (1)
	{
		current->next = ft_lstnew(get_next_line(fd));
		if ((!current->next || !current->next->content) && errno)
			error_exit_with_lstclear(head.next, strerror(errno));
		current = current->next;
		if (current->content == NULL)
			break ;
		game->map.height++;
	}
	if (head.next->content == NULL || get_map_info(head.next, game) == FALSE)
		error_exit_with_lstclear(head.next, "invalid map");
	move_list_to_double_pointer(game, head.next);
}
