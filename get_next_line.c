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

char *ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*newstr;

	if(!s1)
	{
		s1 = malloc(1);
		if(!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if(!s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	newstr = (char *)malloc((len1 + len2 + 1));
	if(!newstr)
		return (NULL);
	i = 0;
	while(i < len1)
	{
		newstr[i] = s1[i];
		i++;
	}
	i = 0;
	while(i < len2)
	{
		newstr[i + len1] = s2[i];
		i++;
	}
	newstr[i + len1] = '\0';
	free(s1);
	return (newstr);
}

char *ft_strchr(char *str, char c)
{
	if(!str)
		return (NULL);
	while (*str)
	{
		if(*str == c)
			return (str);
		str++;
	}
	if(c == '\0')
		return (str);
	return (NULL);
}

char *extract_line(char *stash)
{
	int	i;
	int	k;
	char	*splitted_stash;
	char	*extra_string;

	i = 0;
	while(stash[i] != '\0' && stash[i] != '\n')
		i++;
	splitted_stash = (char *)malloc(i + 2);
	k = 0;
	while(k <= i)
	{
		splitted_stash[k] = stash[k];
		k++;
	}
	splitted_stash[k] = '\0';
	while(stash[i] != '\0')
		i++;
	extra_string = (char *)malloc(i - k);
	k = 0;
	while(k < i)
	{
		extra_string[k] = stash[k];
		k++;
	}
	free(stash);
	stash = extra_string;
	return (splitted_stash);
}

char *get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	ssize_t		read_bytes;
	char		*temp_string;
	char		*extracted_line;

	while(ft_strchr(stash, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if(read_bytes < 0)
		{
			free (stash);
			stash = NULL;
			return (NULL);
		}
		if(read_bytes == 0)
			break;
		buffer[read_bytes] = '\0';
		temp_string = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp_string;
	}
	extracted_line = extract_line(stash);
	return (extracted_line);

}	
