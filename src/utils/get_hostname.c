/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 02:32:19 by sede-san          #+#    #+#             */
/*   Updated: 2025/08/01 13:13:54 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the system's hostname from the /etc/hostname file.
 *
 * This function opens the /etc/hostname file, reads the first line to obtain
 * the hostname, trims any trailing newline character, and returns the result
 * as a dynamically allocated string. The caller is responsible for freeing
 * the returned string.
 *
 * @return A pointer to the trimmed hostname string on success, or NULL on
 * failure.
 *
 * @note The returned string must be freed later to avoid leaks.
 */
char	*get_hostname(void)
{
	char	*hostname;
	char	*hostname_trimmed;
	int		hostname_file;

	hostname_file = open("/etc/hostname", O_RDONLY);
	if (hostname_file != -1)
	{
		hostname = get_next_line(hostname_file);
		close(hostname_file);
	}
	if (!hostname)
		hostname = NULL;
	hostname_trimmed = ft_strtrim(hostname, "\n");
	if (hostname)
		free(hostname);
	return (hostname_trimmed);
}
