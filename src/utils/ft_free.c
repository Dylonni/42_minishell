/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daumis <daumis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:52:26 by daumis            #+#    #+#             */
/*   Updated: 2023/09/19 12:02:38 by daumis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_throw_err(char *err, int err_code)
{
	if (err_code == 1)
		ft_printf(2, "%s: command not found\n", err);
	if (err_code == 2)
		ft_printf(2, "%s: No such file or directory\n", err);
	if (err_code == 3)
		ft_printf(2, "%sminishell: exit: too many arguments\n", err);
	if (err_code == 4)
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", err);
	if (err_code == 5)
		ft_printf(2, "minishell: unset: %s: invalid option\n", err);
	if (err_code == 6)
		ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", err);
	if (err_code == 7)
		(ft_printf(2, "minishell: warning: here-document delimited by"),
			ft_printf(2, " end-of-file (wanted `%s')\n", err));
	if (err_code == 8)
		ft_printf(2, "%s: Is a directory\n", err);
	if (err_code == 9)
		ft_printf(2, "syntax error near unexpected token `%s'\n", err);
	if (err_code == 10)
		ft_printf(2, "minishell: exit: %s: numeric argument required\n", err);
}

void	ft_free_shell(t_sh *shell)
{
	ft_varclear(shell->env_cpy);
	ft_varclear(shell->exp_cpy);
	ft_cmdclear(shell->cmds);
	ft_free_env(shell->env);
	free(shell);
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	ft_free_exec(t_exec *exec)
{
	int	i;

	i = 0;
	free(exec->pathname);
	if (!exec->paths)
		return ;
	while (exec->paths[i])
	{
		free(exec->paths[i]);
		i++;
	}
	free(exec->paths);
}

void	ft_varclear(t_var **lst)
{
	t_var	**lst_init;
	t_var	*tmp;

	if (!lst)
		return ;
	lst_init = lst;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*lst_init = NULL;
	free(lst);
}
