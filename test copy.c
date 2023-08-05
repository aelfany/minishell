#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
    char    *cmd;
    char    *token;
    // char    **cmd;
	int pipe;
    struct s_cmd *next;
} t_cmd;
// char *take_every_char(char *str, int start, int end) //end included & start encluded
// {
//     char *cpy;
//     char *word;
//     int flag;
//     int a;

//     flag = 0;
//     a = 0;
//     (void)start;
//     (void)end;
//     while (str[a])
//     {
//         if (str[a] == '\'' || str[a] == '"')
//         {
//             if (str[a] == '\'')
//                 flag = 1;
//             if (str[a] == '"')
//                 flag = 2;
//             a++;
//             break ;
//         }
//         a++;
//     }
//     printf("%d\n", a);
//     printf("%s\n", str+a);
//     word = _remallc(str, *str);
//     while (*str != '|' && *str && *str != '"')
//     {
//         if (ft_isascii(*str))
//             word = _remallc(word, *str);
//         str++;
//     }
//     return word;
// }



char	*ft_strcpy(char *dest, char *src)
{
	int	a;

	a = 0;
	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

int flag_fun(char *str, char x)
{
    while (*str)
    {
        if (*str == x)
            return (1);
        str++;
    }
    return (0);
}

int find_index_last_quot(char *str)
{
    int a;

    a = strlen(str) - 1;
    if (str[0] == 34 || str[0] == 39 && str[1] == 0)
        return 1;
    while (str[a] && a)
    {
        if (str[a] == 34 || str[a] == 39)
            return (a);
        a--;
    }
    return (0);
}

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	    return (1);
	return (0);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
char *_remallc(char *str, char c)
{
    char *save;
    int a;
    
    a = 0;
    save = malloc(strlen(str)+1);
    while(str[a])
    {
        save[a] = str[a];
        a++;
    }
    save[a] = 0;
    str = malloc((strlen(str)+2) * sizeof(char));
    str[strlen(save)] = c;
    str[strlen(save)+1] = 0;
    a = 0;
    while (save[a])
    {
        str[a] = save[a];
        a++;
    }
    free(save);
    return (str);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int counter_quots(char *str)
{
    int singl_quot;
    int double_quot;

    singl_quot = 0;
    double_quot = 0;
    while (*str)
    {
        if (*str == '"')
            double_quot++;
        if (*str == '\'')
            singl_quot++;
        str++;
    }
    if (singl_quot % 2 != 0 || double_quot % 2 != 0)
        return (1);
    return (0);
}
int skip_w_space(char *str)
{
    int a;

    a = 0;
    while (str[a] == '\t' || str[a] == '\n' ||  str[a] == '\v' 
        ||  str[a] == '\f' || str[a] == '\r' || str[a] == ' ')
    {
        a++;
    }
    return (a);
}

void	insert(t_cmd **root, char *item, char *str)
{
	t_cmd	*temp;
	t_cmd	*ptr;

    (void)str;
	temp = malloc(sizeof(t_cmd));
	if (!temp)
		exit(0);
	temp -> cmd = item;
	temp -> next = NULL;
	if (*root == NULL)
		*root = temp;
	else
	{
		ptr = *root;
		while (ptr-> next != NULL)
			ptr = ptr->next;
		ptr -> next = temp;
	}
}
void who_first(char *str, int *x, t_cmd *res)
{
    int b = x[0];
    char flag;
    char *word;
    flag = 'x';
    if (str[b] == '"')
        flag = '"';
    else
        flag = '\'';
    word = malloc(2);
    word[0] = 0;
    b++;
    while (str[b] != flag && str[b])
    {
        if (ft_isascii(str[b]))
            word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    insert(&res, word, "DQ");
}
// int ft_isspace(char c, int *x)
// {
//     if (c == '\t' || c == '\n' ||  c == '\v' 
//         ||  c == '\f' || c == '\r' || c == ' ')
//     {
        
//     }
// }
void take_string(char *str, int *x, t_cmd *res)
{
    int b = x[0];
    char flag;
    char *word;
    word = malloc(2);
    word[0] = 0;
    while (str[b] != '\'' && str[b] != '"' && str[b])
    {
        if (ft_isascii(str[b]))
            word = _remallc(word, str[b]);
        b++;
    }
    (*x) = b;
    insert(&res, word, "cmd");
}
t_cmd *read_string(char *str)
{
    t_cmd *res;
    char *ins;
    int x;

    x = skip_w_space(str);
    while (str[x])
    {
        if (!counter_quots(str) && (str[x] == '\'' || str[x] == '"'))
            who_first(str, &x, res);
        if (ft_isascii(str[x]) && (str[x] != '\'' || str[x] != '"'))
            take_string(str, &x, res);
        if (counter_quots(str)){
            puts("unclosed quots");
            break ;
        }
        x++;
    }
    return (res);
}

int main()
{
    char *str;
    t_cmd *res;
    while(1)
    {
        str =  readline("minishell\\> ");
        res = read_string(str);
        while(res)
        {
            printf("%s", res -> cmd);
            res = res -> next;
        }
        puts("\n");
        // break;
    }
}

// int main()
// {
//     char *str;
//     char *res;

//     while(1)
//     {
//         str =  readline("minishell\\> ");
//         if (!counter_quots(str))
//         {
//             res = who_first(str);
//             printf(" %s\n", res);
//         }
//         if (counter_quots(str))
//             puts("unclosed quots");
//     }
// }
