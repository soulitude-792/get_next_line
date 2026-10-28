/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imigdady <imigdady@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:19:29 by imigdady          #+#    #+#             */
/*   Updated: 2026/10/27 14:21:48 by imigdady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *fill_leftover(char **stash)
{
	char	*leftover_string;
	int	i;
	int	j;

	i = 0;
	while(((*stash)[i] !='\n' && (*stash)[i] != '\0'))
		i++;
	if((*stash)[i] == '\0')
		return (NULL);
	i++;
	j = 0;
	while((*stash)[i + j] !='\0')
		j++;
	leftover_string = (char *)malloc(j + 1);
	if (!leftover_string)
		return(NULL);
	copy_leftover_chars(stash, leftover_string, i);
	free(*stash);
	return (leftover_string);
}

char *extract_after_newline(char **stash)
{
	char	*extracted_string;
	char	*leftover_string;
	int	i;
	int	k;

	i = 0;
	while((*stash)[i] != '\n')
		i++;
	extracted_string = (char *)malloc(i + 2);
	if(!extracted_string)
		return (NULL);
	k = 0;
	while(k <= i)
	{
		extracted_string[k] = (*stash)[k];
		k++;
	}
	extracted_string[k] = '\0';
	if((*stash)[i + 1] == '\0')
		return(free_stash_and_return(stash, extracted_string));
	leftover_string = fill_leftover(stash);
	*stash = leftover_string;
	return (extracted_string);
}

char *extract_line(char **stash)
{
	char	*extracted_string;

	if(ft_strchr(*stash,'\n') == NULL)
	{
		extracted_string = *stash;
		*stash = NULL;
		return (extracted_string);
	}
	else
		extracted_string = extract_after_newline(stash);
	return (extracted_string);
}

int	check_stash_empty(char **stash)
{
	if(!*stash || (*stash)[0] == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (1);
	}
	return (0);
}

char *get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	ssize_t		read_bytes;
	char		*temp_string;

	while (ft_strchr(stash, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_stash_and_return(&stash, NULL));
		if (read_bytes == 0)
			break;
		buffer[read_bytes] = '\0';
		temp_string = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp_string;
	}
	if (check_stash_empty(&stash))
		return (NULL);
	return (extract_line(&stash));
}
