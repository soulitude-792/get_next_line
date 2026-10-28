/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imigdady <imigdady@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:19:21 by imigdady          #+#    #+#             */
/*   Updated: 2026/10/27 13:19:22 by imigdady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *free_stash_and_return(char **stash, char *extracted_string)
{
        free(*stash);
        *stash = NULL;
        return (extracted_string);
}
void    copy_strings(char *newstr, char *s1, char *s2)
{
        size_t i;
        size_t j;

        i = 0;
        while(s1[i])
        {
                newstr[i] = s1[i];
                i++;
        }
        j = 0;
        while(s2[j])
                newstr[i++] = s2[j++];
        newstr[i] = '\0';
}

char *ft_strjoin(char *s1, char *s2)
{
        char    *newstr;
        size_t  len1;
        size_t  len2;

        if(!s1)
        {
                s1 = malloc(1);
                if(!s1)
                        return (NULL);
                s1[0] = '\0';
        }
        if(!s2)
                return (NULL);
        len1 = ft_strchr(s1, '\0') - s1;
        len2 = ft_strchr(s2, '\0') - s2;
        newstr = (char *)malloc(len1 + len2 + 1);
        if(!newstr)
                return (NULL);
        copy_strings(newstr, s1, s2);
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

void    copy_leftover_chars(char **stash, char *leftover, int i)
{
        int     k;

        k = 0;
        while ((*stash)[i] != '\0')
        {
                leftover[k] = (*stash)[i];
                k++;
                i++;
        }
        leftover[k] = '\0';
}
