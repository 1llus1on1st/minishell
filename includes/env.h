/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:03:14 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/26 18:30:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_shell t_shell;

int		env_key_len(char *entry);
int		env_count(char **env);
int		env_find_index(t_shell *shell, char *key);
char	*gc_strdup_env(t_shell *shell, char *str);
int		env_set_entry(t_shell *shell, char *entry);
int		env_unset_key(t_shell *shell, char *key);

#endif