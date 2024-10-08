/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:49:00 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:03:09 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_setup(t_token *token, char **final_str)
{
	*final_str = ft_strdup("");
	quotes_remove(&token->next);
	return (hex_to_dec(token));
}

int	update_final_str(char **final_str, char *read_str, char *filename)
{
	char	*temp_str;

	temp_str = ft_strjoin(*final_str, read_str);
	if (!temp_str)
	{
		cleanup_memory(*final_str, read_str, filename);
		return (0);
	}
	free(*final_str);
	*final_str = temp_str;
	return (1);
}

void	cleanup_memory(char *final_str, char *read_str, char *filename)
{
	if (final_str)
		free(final_str);
	if (read_str)
		free(read_str);
	if (filename)
		free(filename);
}

int	process_heredoc_loop(t_token *token, t_cmd *cmd_data, \
char **final_str, char *filename)
{
	char	*read_str;

	heredoc_signals_set();
	read_str = readline(PURPLE "😈 > " NS);
	if (g_signum == SIGINT)
		return (free(token->next->str), exe_signals_processing(), \
		cleanup_memory(*final_str, NULL, NULL), cmd_data->exit_code = 130, 1);
	while (read_str && g_signum != SIGINT)
	{
		if (handle_heredoc_delimiter(token, read_str, *final_str, filename))
			return (exe_signals_processing(), 1);
		read_str = process_heredoc_line(read_str, token, cmd_data);
		if (!update_final_str(final_str, read_str, filename))
			return (0);
		free(read_str);
		read_str = readline(PURPLE "😈 > " NS);
	}
	if (g_signum == SIGINT)
		return (exe_signals_processing(), free(token->next->str), \
		cleanup_memory(*final_str, NULL, NULL), cmd_data->exit_code = 130, 1);
	else if (!read_str)
		handle_heredoc_delimiter(token, read_str, *final_str, filename);
	return (exe_signals_processing(), 1);
}

char	*heredoc_handler(t_token *token, t_cmd *cmd_data)
{
	char	*final_str;
	char	*filename;

	filename = heredoc_setup(token, &final_str);
	if (!final_str || !filename)
		return (cleanup_memory(final_str, NULL, filename), NULL);
	if (!process_heredoc_loop(token, cmd_data, &final_str, filename))
		return (cleanup_memory(final_str, NULL, filename), NULL);
	return (filename);
}
