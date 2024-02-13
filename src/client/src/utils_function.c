/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** utils_function
*/

#include "client.h"

void free_config(client_t *client)
{
    free_struct(client);
    close(client->perso.sockfd);
    free(client);
}

void free_double_array(u_int8_t **cmd)
{
    for (int u = 0; cmd[u] != NULL; u++) {
        free(cmd[u]);
    }
    free(cmd);
}

int count_nb_quotes(char *cmd)
{
    int nb = 0;
    int i = 0;

    for (i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == '"')
            nb += 1;
    return nb;
}

int strlen_2d(char **tab)
{
    int i = 0;

    while (tab[i] != NULL) {
        i += 1;
    }
    return i;
}
