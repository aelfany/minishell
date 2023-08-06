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
    int     count;
    char    *token;
	int     heredoc;
    struct s_cmd *next;
} t_cmd;

typedef struct s_creat
{
    char    *cmd;
    char    *token;
    char    **opt;
    int     pipe;
    struct s_creat *next;
} t_creat;

// #define DQ
// #define SQ
// #define RDOUT
// #define RDIN
// #define EX
// #define PP






// char	*ft_strdup(const char *s1)
// {
// 	int		a;
// 	int		res;
// 	char	*cpy;

// 	a = 0;
// 	res = strlen(s1) + 1;
// 	cpy = (char *)malloc(res * sizeof(char));
// 	if (!cpy)
// 		return (0);
// 	while (s1[a])
// 	{
// 		cpy[a] = s1[a];
// 		a++;
// 	}
// 	cpy[a] = '\0';
// 	return (cpy);
// }

// void insert_opt(t_cmd **root, char *str)
// {
//     int a;
//     int b;

//     a = 0;
//     b = -1;
//     char **save;
//     (*root) -> count++;
//     while((*root) -> opt[a])
//         a++;
//     save = malloc((a+1) * sizeof(char *));
//     a = -1;
//     while((*root) -> opt[++a])
//         save[a] = (*root)-> opt[a];
//     save[a] = NULL;
//     (*root) -> opt = malloc((a+2) * sizeof(char *));
//     (*root) -> opt[(*root) -> count] = ft_strdup(str);
//     (*root) -> opt[(*root) -> count+1] = NULL;
//     a = -1;
//     while(save[++a])
//         (*root)-> opt[a] = save[a];
// }
// void insert_opt(t_cmd **root, t_creat *x)
// {
    
// }

// void	insert(t_cmd **root, char *item, char *str)
// {
// 	t_cmd	*temp;
// 	t_cmd	*ptr;
// 	temp = malloc(sizeof(t_cmd));
// 	if (!temp)
// 		exit(0);
//     temp -> opt = malloc(2 * sizeof(char *));
//     temp -> opt[0] = ft_strdup(item); 
//     temp -> opt[1] = NULL; 
// 	temp -> token = str;
//     temp -> count = 0;
// 	temp -> next = NULL;
// 	if (*root == NULL)
// 		*root = temp;
// 	else
// 	{
// 		ptr = *root;
// 		while (ptr-> next != NULL)
// 			ptr = ptr->next;
// 		ptr -> next = temp;
// 	}
// }






int main()
{
    char *str;
    t_creat *res;
    int a = 0;
    while(1)
    {
        str =  readline("> ");
        res = read_string(str);
        while(res)
        {
            printf("type[%s] %s\n", res -> token, res -> cmd);
            res = res -> next;
        }
        //     a = 0;
        //     while(res -> opt[a])
        //     {
                // a++;
        //     }
    }
}
