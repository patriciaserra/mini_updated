/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:14:00 by jdach             #+#    #+#             */
/*   Updated: 2024/10/02 16:14:58 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bltns_exe_check_arg(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*str;
	int		i;
	int		exit_code;

	str = cmd_list_item->arguments[0];
	i = -1;
	if (str != NULL)
	{
		while (str[++i] != '\0')
		{
			if ((str[i] < 48 || str[i] > 57) && (str[i] != 45 && str[i] != 43))
			{
				exe_err_long(NULL, ERR_EXIT_NO_NBR);
				exe_cleanup(cmd_data);
				exit(2);
			}
		}
		if (cmd_data->pipe_scenario == 0)
			ft_putstr_fd("exit\n", 2);
		exit_code = ft_atoi(cmd_list_item->arguments[0]);
		exe_cleanup(cmd_data);
		exit(exit_code);
	}
}

void	exe_bltns_exit(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	cmd_data->exit_code = 0;
	if (cmd_list_item->arguments[0] && cmd_list_item->arguments[1])
	{
		exe_err_long(NULL, ERR_TOO_MANY_ARGS);
		if (cmd_data->pipe_scenario == -1)
			ft_putstr_fd("exit\n", 2);
		exe_cleanup(cmd_data);
		exit(1);
	}
	exe_bltns_exe_check_arg(cmd_list_item, cmd_data);
	if (cmd_data->pipe_scenario == -1)
		ft_putstr_fd("exit\n", 2);
	exe_cleanup(cmd_data);
	exit(EXIT_SUCCESS);
}
