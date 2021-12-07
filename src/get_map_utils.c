/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:25:14 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/07 15:30:08 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_list_to_double_pointer(t_game *game, t_list *map)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	game->map.map = (char **)ft_calloc(game->map.height + 1, sizeof(char *));
	if (game->map.map == NULL)
	{
		ft_lstclear(&map, free);
		error_exit("failed malloc");
	}
	tmp = map;
	while (i < game->map.height)
	{
		game->map.map[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&map, NULL);
}
