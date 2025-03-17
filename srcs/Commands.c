/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:32:52 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/17 17:51:39 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

static int	prm_len(char const *str, char c)
{
	int i;
	
	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		while (str[i] && str[i] != c)
			i++;
	}
	else
	{
		while (str[i] && str[i] != c)
			i++;
	}
	return (i+1);
}



static void	*freesplit(char **split, int fin)
{
	int i;
	
	i = 0;
	while (i <= fin)
	{
		free(split[i]);	
		i++;
	}
	free(split);
	return (NULL);
}
