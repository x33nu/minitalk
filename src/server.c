/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urbilya@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:56:49 by nalysann          #+#    #+#             */
/*   Updated: 2021/09/10 10:56:51 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <unistd.h>

#include "ft_stdio.h"

#include "minitalk.h"

static void	handler(int signal)
{
	static unsigned char	byte = 0;
	static int				shift = 0;

	if (signal == SIGUSR1)
		byte |= 1 << shift;
	if (++shift == BYTE_SIZE)
	{
		write(STDOUT_FILENO, &byte, sizeof(byte));
		byte = 0;
		shift = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server pid is %d\n", getpid());
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
		ft_perror(SERVER, E_SIGACT_FAIL);
	while (1)
		pause();
}
