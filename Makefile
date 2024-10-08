# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 15:45:03 by paribeir          #+#    #+#              #
#    Updated: 2024/10/02 17:24:26 by paribeir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -lreadline
CFLAGS = -Wall -Werror -Wextra
CC = cc
OPTIONS = -c -g

ifeq ($(shell uname -s), Darwin)
  LDFLAGS += -L/opt/homebrew/opt/readline/lib
  CPPFLAGS += -I/opt/homebrew/opt/readline/include
endif

#NAMES
NAME = minishell

#DIRECTORIES
OBJ_DIR = obj/
LIB_DIR = lib/
SRC_DIR = src/

#SOURCEFILES
SRC_MINISHELL = \
banner.c \
exe/exe_bin.c \
exe/exe_bin_args.c \
exe/exe_bin_get_bin_path.c \
exe/exe_bltns.c \
exe/exe_bltns_cd.c \
exe/exe_bltns_echo.c \
exe/exe_bltns_env.c \
exe/exe_bltns_exit.c \
exe/exe_bltns_export.c \
exe/exe_bltns_pwd.c \
exe/exe_bltns_unset.c \
exe/exe_cleanup.c \
exe/exe_cleanup_aftercmd.c \
exe/exe_cleanup_strarray.c \
exe/exe_directs_append.c \
exe/exe_directs_del_tmp_heredoc.c \
exe/exe_directs_here_doc.c \
exe/exe_directs_redir_in.c \
exe/exe_directs_redir_out.c \
exe/exe_env_get_var.c \
exe/exe_env_get_var_address.c \
exe/exe_env_cpy.c \
exe/exe_env_set_var.c \
exe/exe_err.c \
exe/exe_fd_checker.c \
exe/exe_get_exit_status.c \
exe/exe_increase_shlvl.c \
exe/exe_pipe_closing_child.c \
exe/exe_pipe_closing_parent.c \
exe/exe_set_in_out.c \
exe/exe_signals.c \
exe/exe_with_pipes.c \
exe/exe_without_pipes.c \
exe/exe.c \
main.c \
parsing/env_variables_get.c \
parsing/env_variables_utils.c \
parsing/env_variables.c \
parsing/expansions.c \
parsing/heredoc_signals.c \
parsing/heredoc_expansion.c \
parsing/heredoc_utils.c \
parsing/heredoc.c \
parsing/hex_to_str.c \
parsing/parser_args_utils.c \
parsing/parser_nodes_utils.c \
parsing/parser.c \
parsing/quotes_remove.c \
parsing/quotes.c \
parsing/tokenizer_process_tokens.c\
parsing/tokenizer_utils.c \
parsing/tokenizer.c

SRCS_MINISHELL = $(addprefix $(SRC_DIR), $(SRC_MINISHELL))

#OBJECTFILES
OBJ_MINISHELL = $(SRC_MINISHELL:.c=.o)
OBJS_MINISHELL = $(addprefix $(OBJ_DIR), $(OBJ_MINISHELL))

#HEADERFILES
INCS = -I inc/

all: $(NAME)

$(NAME): $(OBJS_MINISHELL)
	make -C $(LIB_DIR)libft
	$(CC) $(CFLAGS) $(OBJS_MINISHELL) $(LDFLAGS) $(FLAGS) $(LIB_DIR)libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) $(CPPFLAGS) $(OPTIONS) $< -o $@

clean:
	make clean -C $(LIB_DIR)libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
