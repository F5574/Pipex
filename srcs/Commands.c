/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gisrael <gisrael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:32:52 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/22 22:21:46 by gisrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

static void	*freesplit(char **split, int fin, int i)
{
	while (i <= fin)
		free(split[i++]);
	free(split);
	return (NULL);
}

static int	prm_len(char const *str, char c, int i)
{
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
	return (++i);
}

static void	fill_param(int *len, char **split, const char *str, int i)
{
	while (*str == ' ' && *str)
		str++;
	*len = prm_len(str, ' ', 0);
	if (*str && *str == '\'')
		split[i] = ft_substr(str +1, 0, *len - 3);
	else
		split[i] = ft_substr(str, 0, *len - 1);
}

static int	count_p(char const *param, char c, int count)
{
	while (*param)
	{
		while (*param == c && *param)
			param++;
		if (*param == '\'')
		{
			param++;
			count++;
			while (*param && *param != '\'')
				param++;
			while (*param != c && *param)
				param++;
		}
		if (*param != c && *param)
			count++;
		while (*param != c && *param)
			param++;
	}
	return (count);
}

char	**split_command(char const *inputstr, int i)
{
	int		count;
	int		len;
	char	**result;

	if (!inputstr)
		return (NULL);
	count = count_p(inputstr, ' ', 0);
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < count)
	{
		fill_param(&len, result, inputstr, i);
		if (!result[i++])
			return (freesplit(result, count, 0));
		inputstr += len;
	}
	result[i] = 0;
	return (result);
}
