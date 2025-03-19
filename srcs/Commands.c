/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:32:52 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/19 14:38:26 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

static void	*freesplit(char **split, int fin)
{
	int	i;

	i = 0;
	while (i <= fin)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static int	prm_len(char const *str, char c)
{
	int	i;

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
	return (i + 1);
}

static void fill_param(int *len, char **split, const char *str, int i)
{
	while (*str == ' ' && *str)
		str++;
	*len = prm_len(str, ' ');
	if (*str && *str == '\'')
		split[i] = ft_substr(str +1, 0 ,*len -3);
	else
		split[i] = ft_substr(str, 0, *len - 1);
}

static int	count_p(char const *param, char c)
{
	int	count;

	count = 0;
	while (*param)
	{
		while (*param == c && *param)
			param++;
		if (*param == '\'')
		{
			param++;
			count++;
			while (*param != '\'' && *param)
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

char **Split_command(char const *input_str)
{
	int		count;
	int		i;
	int		len;
	char	**result;

	i = 0;
	if(!input_str)
		return(NULL);
	count = count_p(input_str, ' ');
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < count)
	{
		fill_param(&len, result, input_str, i);
		if (!result[i++])
			return (freesplit(result, count));
		input_str += len;
	}
	result[i] = 0;
	return (result);
}
