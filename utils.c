/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:52:41 by dlanotte          #+#    #+#             */
/*   Updated: 2021/07/02 17:37:35 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init(t_term *term, char **env)
{
	char	*level;

	level = getenv("SHLVL");
	level[0]++;
	setenv("SHLVL", level, 1);
	term->type = getenv("TERM");
	tcgetattr(0, &term->dconf);
	ft_memcpy(&term->cconf, &term->dconf, sizeof(struct termios));
	term->cconf.c_lflag &= ~(ECHO | ICANON);
	term->cursor = 0;
	term->env = table_dup(env);
	open_history(term);
}

static void	intHandler(int signal)
{
	//char	*tmp;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		graphic_hub(2, find_path());
		free(g_term->input);
		g_term->input = ft_strdup("");
		g_term->cursor = 0;
		g_term->last_status = 1;
	}
}

void	ft_signal_manager(void)
{
	signal(SIGINT, intHandler);
	signal(SIGQUIT, intHandler);
}
