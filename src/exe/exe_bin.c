/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:10:21 by jdach             #+#    #+#             */
/*   Updated: 2024/07/17 17:59:59 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_bin(t_cmd_list *cmd_list_item, t_cmd *cmd_env)
{
	char	*path;
	char	**args;
	int		pid;

	exe_get_in_out(cmd_list_item, cmd_env);
	path = exe_get_bin_path(cmd_list_item);
	args = exe_set_execve_args(cmd_list_item->arguments, cmd_list_item->binary);
	pid = fork();
	if (pid == 0)
		execve(path, args, NULL);
}
