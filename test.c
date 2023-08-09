// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abelfany <abelfany@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/18 09:22:02 by abelfany          #+#    #+#             */
// /*   Updated: 2023/07/18 09:33:06 by abelfany         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"


// void handler(int x)
// {
//     (void)x;
//     printf("\n");
//     rl_forced_update_display(); // Update readline display
// }

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;
//     char *s;
//     char d[100];
//     signal(SIGINT, handler); // Set up the signal handler

//     while (1)
//     {
//  //       s = getcwd(d, sizeof(d));
//         char *line = readline("minishell\\> "); // Read input

//         if (line == NULL)
//             continue; // Ignore empty input

//         add_history(line); // Add input to history

//         // TODO: Process the input

//         free(line); // Free the allocated input string
//     }
// }
