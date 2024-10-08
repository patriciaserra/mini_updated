/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:11:46 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 15:20:03 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*** Macros ***/
//IFS stands for Internal Field Separator
# define IFS		" \t\n"
# define SPECIAL_CHARS	"|<>"

/*** enum ***/
typedef enum s_token_type {
	OPERATOR = 101,
	PIPE = 102,
	CMD_WORD = 103,
	IO_FILE = 104,
}	t_token_type;

typedef enum s_token_subtype
{
	ARGUMENT,
	AND_IF,
	BINARY,
	DQUOTE,
	OR_IF,
	T_PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	SQUOTE,
	BLTIN,
	BLTIN_ECHO,
	BLTIN_CD,
	BLTIN_PWD,
	BLTIN_EXPORT,
	BLTIN_UNSET,
	BLTIN_ENV,
	BLTIN_EXIT
}	t_token_subtype;

/*** Linked list - Tokens ***/
typedef struct s_token {
	t_token_type	type;
	t_token_subtype	subtype;
	char			*str;
	int				length;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*** Functions ***/
//tokenizer.c
t_token	*tokenizer(char *input, t_cmd *cmd_data);
t_token	*process_tokens(char *input, t_token *head, t_cmd *cmd_data);

//tokenizer_process_tokens.c
int		token_small(char *input, t_token *token, t_cmd *cmd_data);
int		token_big(char *start, t_token *token);
void	add_token(char *start, t_token **head, t_token *token);

//tokenizer_utils.c
t_token	*create_token(void);
void	token_add_back(t_token **head, t_token *new_node);
char	*hex_to_dec(void *ptr);
char	*ptr_to_str(unsigned long number);
int		add_subtype(char q, char *input);
int		token_check_syntax(t_token **head);

#endif
