/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfontain <hfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:02:35 by hfontain          #+#    #+#             */
/*   Updated: 2018/04/17 18:57:52 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	check_second(char second, int *i, char *cmd)
{
	*i = *i + 1;
	while (cmd[*i] && cmd[*i] != second)
	{
		if (cmd[*i] == '\\')
		{
			*i = *i + 1;
			if (cmd[*i] == '\0')
				continue ;
			*i = *i + 1;
			continue ;
		}
		*i = *i + 1;
	}
	if (cmd[*i] == '\0')
		return (1);
	return (0);
}

static int	quote(char *cmd, int *i)
{
	char	tabl[5];
	int		var;

	tabl[1] = '"';
	tabl[2] = '\'';
	tabl[3] = '`';
	tabl[4] = '\0';
	var = 1;
	while (tabl[var])
	{
		if (cmd[*i] == tabl[var])
		{
			if ((check_second(tabl[var], i, cmd)) != 0)
				return (var);
		}
		var++;
	}
	return (0);
}

static int bracket(char *cmd, int *i)
{
	char	tabl[5];
	int		var;
	char	second;

	tabl[1] = '{';
	tabl[2] = '[';
	tabl[3] = '(';
	tabl[4] = '\0';
	var = 1;
	while (tabl[var])
	{
		if (cmd[*i] == tabl[var])
		{
			if (var == 1)
				second = '}';
			else if (var == 2)
				second = ']';
			else
				second = ')';
			if ((check_second(second, i, cmd)) != 0)
				return (var);
		}
		var++;
	}
	return (0);
}

static char	*check_correct_2(int i, char *cmd)
{
	int		o;
	int		stock;
	int		beforestock;

	if (cmd[i] && (cmd[i] == '|' || cmd[i] == '\\' || cmd[i] == '&'))
	{
		stock = cmd[i];
		if (i == 0)
			beforestock = '\0';
		else
			beforestock = cmd[i - 1];
		o = i;
		o++;
		while (cmd[o] && (cmd[o] == ' ' || cmd[o] == '\n'))
			o++;
		if (cmd[o] == '\0')
		{
			if (stock == '|')
				return ("cmd> ");
			else if (stock == '\\')
				return ("cmd");
			else if (stock == '&' && beforestock && beforestock == '&')
				return ("cmd> ");
		}
	}
	return (NULL);
}

char		*check_correct(char *cmd)
{
	int		i;
	int		stock;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
		{
			if (cmd[++i] == '\0')
				return ("cmd> ");
			i++;
			continue ;
		}
		if ((stock = quote(cmd, &i)) != 0)
		{
			if (stock == 1)
				return ("d_quote> ");
			if (stock == 2)
				return ("s_quote> ");
			if (stock == 3)
				return ("b_quote> ");
		}
		if (check_correct_2(i, cmd) != NULL)
			return (check_correct_2(i, cmd));
		if ((stock = bracket(cmd, &i)) != 0)
		{
			if (stock == 1)
				return ("need_}> ");
			if (stock == 2)
				return ("need_]> ");
			if (stock == 3)
				return ("need_)> ");
		}
		if (check_correct_2(i, cmd) != NULL)
			return (check_correct_2(i, cmd));
		i++;
	}
	return (NULL);
}
