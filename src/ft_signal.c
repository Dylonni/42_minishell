/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <psan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:53:30 by daumis            #+#    #+#             */
/*   Updated: 2023/09/26 18:10:23 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Function that handles one of the SIGQUIT type of signal (Ctrl + \\)
The signal is ignored if nothing is running.
If a process is running, it quits and shows a prompt to the user*/
void	ft_signal_backslash(int sig)
{
	struct sigaction	sigact;

	ft_memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler = SIG_IGN;
	sigact.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sigact.sa_mask) == -1
		|| sigaction(sig, &sigact, NULL) == -1)
		return (g_error = 1, perror("sigaction"));
	g_error = 131;
}

/*Signal handler called before forking.
Handles SIGINT and SIGQUIT signals inside child processes*/
void	ft_signal_exec(void)
{
	struct sigaction	sigact_c;
	struct sigaction	sigact_b;

	ft_memset(&sigact_c, 0, sizeof(sigact_c));
	sigact_c.sa_handler = &ft_signal_c_exec;
	sigact_c.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sigact_c.sa_mask) == -1
		|| sigaction(SIGINT, &sigact_c, NULL) == -1)
		return (g_error = 1, perror("sigaction"));
	ft_memset(&sigact_b, 0, sizeof(sigact_b));
	sigact_b.sa_handler = &ft_signal_backslash;
	sigact_b.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sigact_b.sa_mask) == -1
		|| sigaction(SIGQUIT, &sigact_b, NULL) == -1)
		return (g_error = 1, perror("sigaction"));
}

/*This function defines the signal handlers when the program first launches*/
void	ft_signal_main(void)
{
	signal(SIGINT, ft_signal_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_signal_hrdc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_c_hrdc);
}

int	event(void)
{
	return (0);
}
