/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_directs_redir_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:16:55 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 21:39:29 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_directs_redir_in(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	int		fd;

	fd = open(cmd_list_item->arguments[0], O_RDONLY);
	if (fd == -1)
	{
		perror("Minishell");
		exe_directs_del_tmp_heredoc(cmd_list_item);
		cmd_data->stop_exe = 1;
		cmd_data->exit_code = 1;
		if (cmd_data->pipe_scenario == 1)
			exit (1);
		else
			return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
