/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urbilya@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:56:42 by nalysann          #+#    #+#             */
/*   Updated: 2021/09/10 10:56:44 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

#include "ft_stdio.h"
#include "ft_stdlib.h"

#include "minitalk.h"

static void	send_char(char c, pid_t pid)
{
	int	pos;

	pos = 0;
	while (pos < BYTE_SIZE)
	{
		usleep(T_SLEEP);
		if (c & (1 << pos++))
		{
			if (kill(pid, SIGUSR1) < 0)
				ft_perror(CLIENT, E_KILL_FAIL);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				ft_perror(CLIENT, E_KILL_FAIL);
		}
	}
}

static void	send_string(const char *str, pid_t pid)
{
	while (*str)
		send_char(*str++, pid);
	send_char('\n', pid);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		ft_error2(CLIENT, INV_ARGC_MSG, E_INV_ARGC);
	send_string(argv[2], ft_atoi(argv[1]));
}
