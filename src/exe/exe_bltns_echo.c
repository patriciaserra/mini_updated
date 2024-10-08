/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:02:37 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 15:46:50 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_echo_set_n_flag(char **args, int *n_flag, int *start)
{
	int	i;

	i = 1;
	if (*args)
	{
		if (args[0][0] == '-' && args[0][1] == 'n')
		{
			while (args[0][++i] == 'n')
				continue ;
			if (args[0][i] == '\0')
				*n_flag = 1;
			else
				*start = 0;
		}
		else
			*start = 0;
	}
}

void	exe_bltns_echo(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	**args;
	int		n_flag;
	int		start;

	cmd_data->exit_code = 0;
	(void) cmd_data;
	args = cmd_list_item->arguments;
	n_flag = 0;
	start = 1;
	exe_bltns_echo_set_n_flag(args, &n_flag, &start);
	while (args[0] && args[start])
	{
		if ((n_flag == 0 && start > 0) || (n_flag == 1 && start > 1))
			printf(" ");
		printf("%s", args[start++]);
	}
	if (n_flag == 0)
		printf("\n");
}
