/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paribeir <paribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:24:23 by paribeir          #+#    #+#             */
/*   Updated: 2024/10/02 14:32:39 by paribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle zero case
char	*handle_zero_case(void)
{
	char	*str;

	str = (char *)ft_calloc(2, 1);
	if (str == NULL) 
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	str[0] = '0';
	return (str);
}

//calculate the length of the string required to store the number
int	calculate_length(unsigned long number)
{
	unsigned long	temp;
	int				len;

	len = 0;
	temp = number;
	while (temp > 0) 
	{
		temp /= 10;
		len++;
	}
	return (len);
}

//convert nbr to string
void	convert_to_string(char *str, unsigned long number, int len)
{
	char	*end;

	end = str + len;
	*end = '\0';
	while (number > 0) 
	{
		*(--end) = (number % 10) + '0';
		number /= 10;
	}
}

char	*ptr_to_str(unsigned long number)
{
	char	*str;
	int		len;

	if (number == 0) 
		return (handle_zero_case());
	len = calculate_length(number);
	str = (char *)ft_calloc(len + 1, 1);
	if (str == NULL) 
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	convert_to_string(str, number, len);
	return (str);
}

char	*hex_to_dec(void *ptr)
{
	unsigned long	value;
	char			*str;
	char			*number;

	value = (unsigned long)ptr;
	number = ptr_to_str(value);
	if (!number)
		return (NULL);
	str = ft_strjoin("here_doc_temp_", number);
	free(number);
	if (!str)
		return (NULL);
	return (str);
}
