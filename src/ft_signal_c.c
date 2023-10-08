/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:46:39 by psan              #+#    #+#             */
/*   Updated: 2023/09/26 18:06:28 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Function that handles the SIGINT type of signal (Ctrl + C)
Replaces the actual line with a new one*/
void	ft_signal_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_error = 130;
}

void	ft_signal_c_prnt(int sig)
{
	(void)sig;
	rl_on_new_line();
	g_error = 130;
}

/*Function that handles the SIGINT type of signal (Ctrl + C) within a child
process.
Cancels the running process and shows a new line with prompt*/
void	ft_signal_c_exec(int sig)
{
	struct sigaction	sigact;

	ft_memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler = &ft_signal_c_exec;
	sigact.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sigact.sa_mask) == -1
		|| sigaction(sig, &sigact, NULL) == -1)
		return (g_error = 1, perror("sigaction"));
	g_error = 130;
	rl_on_new_line();
	ft_printf(1, "\n");
}

void	ft_signal_c_hrdc(int sig)
{
	struct sigaction	sigact;

	ft_memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler = SIG_DFL;
	sigact.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sigact.sa_mask) == -1
		|| sigaction(sig, &sigact, NULL) == -1)
		return (g_error = 1, perror("sigaction"));
	rl_done = 1;
	g_error = -130;
}
