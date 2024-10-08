/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:07 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:47:19 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The parser analyzes the tokens
to form syntactically valid commands.
It further processes the tokens
to create a ready-to-use linked list of commands.*/
t_cmd_list	*parse_tokens(t_token **token, t_cmd *cmd_data)
{
	t_token		*current;
	t_cmd_list	*head;

	head = NULL;
	current = token_fusion(*token);
	if (!current)
		return (NULL);
	while (current)
	{
		reorder_tokens(current, &head, REDIR_IN, cmd_data);
		while (current && current->type != PIPE && current->type != OPERATOR)
			current = current->next;
		if (current)
		{
			node_add_back(&head, create_cmd_node(current));
			current = current->next;
		}
	}
	free_tokens(token);
	return (head);
}

void	reorder_tokens(t_token *token, t_cmd_list **head, t_token_subtype type, \
t_cmd *cmd_data)
{
	t_cmd_list	*node;
	t_token		*current;

	current = token;
	while (current && current->type > PIPE)
	{
		(void) type;
		if (!current->str[0] && \
		!(current->subtype == SQUOTE || current->subtype == DQUOTE))
			cmd_data->exit_code = 0;
		else if (current->subtype != ARGUMENT && \
		current->subtype != DQUOTE && current->subtype != SQUOTE)
		{
			node = create_cmd_node(current);
			if (!node)
				break ;
			node_add_back(head, node);
		}
		current = current->next;
	}
}

/*free the initial linked list of tokens*/
void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*temp;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->str)
		{
			free(temp->str);
			temp->str = NULL;
		}
		free(temp);
	}
	*head = NULL;
}

void	node_add_back(t_cmd_list **head, t_cmd_list *new_node)
{
	t_cmd_list	*temp;

	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

//get and assign arguments, delete argument tokens
void	add_arguments(t_token *token, t_cmd_list **node)
{
	int		nbr_args;
	t_token	*current;

	current = NULL;
	nbr_args = 0;
	if (token->type == IO_FILE)
	{
		add_arguments_redirect(token, node);
		return ;
	}
	else if (token->next)
		nbr_args = count_args(token);
	alloc_args(token, current, node, nbr_args);
}
