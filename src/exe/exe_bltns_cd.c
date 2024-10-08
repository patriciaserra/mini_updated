/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bltns_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdach <jdach@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:24:36 by jdach             #+#    #+#             */
/*   Updated: 2024/09/29 15:47:01 by jdach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_bltns_cd_get_target(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*target;
	char	**args;

	args = cmd_list_item->arguments;
	if (*args == NULL)
		target = exe_env_get_var("HOME", cmd_data);
	else if (args[0][0] == '-' && args[0][1] == '\0')
		target = exe_env_get_var("OLDPWD", cmd_data);
	else
		target = ft_strdup(args[0]);
	return (target);
}

int	exe_bltns_cd_check_input(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	if (cmd_list_item->arguments[1])
	{
		exe_err_long(NULL, ERR_CD_TOO_MANY_ARGS);
		cmd_data->exit_code = 1;
		return (1);
	}
	return (0);
}

void	exe_bltns_cd(t_cmd_list *cmd_list_item, t_cmd *cmd_data)
{
	char	*target;
	char	*var_val;
	char	pwd[PATH_MAX];

	cmd_data->exit_code = 0;
	if (exe_bltns_cd_check_input(cmd_list_item, cmd_data) == 1)
		return ;
	target = exe_bltns_cd_get_target(cmd_list_item, cmd_data);
	if (chdir(target) == 0)
	{
		free(target);
		var_val = exe_env_get_var("PWD", cmd_data);
		exe_env_set_var("OLDPWD", var_val, cmd_data);
		free(var_val);
		getcwd(pwd, sizeof(pwd));
		exe_env_set_var("PWD", pwd, cmd_data);
	}
	else
	{
		free(target);
		cmd_data->exit_code = 1;
		exe_err_long(NULL, ERR_CD_NO_SUCH_DIRECTORY);
	}
}
