/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:04:40 by salzghou          #+#    #+#             */
/*   Updated: 2025/10/23 16:53:32 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char *update(char **store)
{
    char *new;
    int i=0;
    int len;
    int final;
    len=ft_strlen(*store);
    while((*store)[i] && (*store)[i]!='\n')
    i++;
    if(!((*store)[i]))
    {
        free(*store);
        *store = NULL;
        return(NULL);
    }
    if((*store)[i]=='\n')
    i++;
   final=len-i;
    new=malloc(final+1);
    if(!new){
        free(*store);
        *store=NULL;
    return(NULL);}
    ft_memcpy(new, *store + i,final);
    new[final]='\0'; 
   
    free(*store);
    return(new);
}



char *linef(char **store)
{
    int i;
    char *line;
    i=0;
    while((*store)[i] && (*store)[i]!='\n')
    i++;
    line=malloc(i+2);
    if(!line)
        return(NULL);
    ft_memcpy(line,*store,i);
    if((*store)[i]=='\n')
    {
        line[i]='\n';
        i++;
    }
    line[i]='\0';
    return(line);
}
int readjoin(int fd ,char **store)
{
    char *buff =malloc(BUFFER_SIZE+1);
    char *holder;
    int n=1;
    if(!buff)
    return 1;
    while(*store && !ft_strchr(*store, '\n') && n > 0)
    {
     n=read (fd, buff, BUFFER_SIZE);
       
        if(n < 0)
        {
            free(buff);
            return 1;
        }
        
        buff[n] = '\0';
        holder=ft_strjoin(*store,buff);
            free(*store);
           *store=holder;
        }
        free(buff);
        if (holder[0] == '\0')
            return 1;
        return 0;
    }
    
char *get_next_line(int fd)
{
    static char *store;
    char *line;
    int flag;
    if(fd <0 || BUFFER_SIZE<=0)
        return(NULL);
    if(!store)
        store=ft_strdup("");
    flag =readjoin(fd,&store);
    if(!store || !*store || flag == 1)
    {
        free(store);
        store=NULL;
            return (NULL);
    }
        line=linef(&store);
        if(!line )
        {
            free(store);
            store=NULL;
            return(NULL);
        }
        store=update(&store);
        return(line);
}
// int	main(void){
// 	int fd = open("txt.txt", O_RDONLY);
// 	char *line = NULL;
// 	while ((line = get_next_line(fd)) != NULL){
// 	printf("%s", line);
// 	free(line);
//     }
// close(fd);
// }
