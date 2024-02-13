/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** freeServer
*/

#include "my_teams.h"

void free_struct(server_t *server)
{
    free(server->bufferedSocket);
}

void free_all_struct(server_t *server, fd_set *set)
{
    return;
}
