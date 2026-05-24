/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:03:14 by mshargan          #+#    #+#             */
/*   Updated: 2026/05/24 19:14:02 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_shell t_shell;

int		init_env(t_shell *shell, char **envp);
char	*get_env_value(t_shell *shell, char *key);

#endif