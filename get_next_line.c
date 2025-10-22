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
        return(NULL);
    }
    i++;
   final=len-i;
    new=malloc(final+1);
    if(!new){
        free(*store);
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
void readjoin(int fd ,char **store)
{
    char *buff =malloc(BUFFER_SIZE+1);
    char *holder;
    int n=1;
    if(!buff)
    return;
    while(!ft_strchr(*store, '\n') && n > 0)
    {
     n=read (fd, buff, BUFFER_SIZE);
        if(n < 0)
        {
            free(buff);
            free(*store);
            *store=NULL;
            return;
        }
        buff[n] = '\0';
        holder=ft_strjoin(*store,buff);
            free(*store);
           *store=holder;
        }
        free(buff);
    }
    
char *get_next_line(int fd)
{
    static char *store;
    char *line;
    if(fd <0 || BUFFER_SIZE<=0)
        return(NULL);
    if(!store)
        store=ft_strdup("");
        readjoin(fd,&store);
        if(!store || !*store)
            return (NULL);
        line=linef(&store);
        store=update(&store);
        return(line);
}
int	main(void){
	int fd = open("txt.txt", O_RDONLY);
	char *line ;
	while ((line = get_next_line(fd)) != NULL){
	printf("%s", line);
	free(line);
    }}