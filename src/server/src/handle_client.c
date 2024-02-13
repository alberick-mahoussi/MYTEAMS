/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** handleClient
*/

#include "my_teams.h"

static void handle_client_bis(size_t i, server_t *server, fd_set *set)
{
    if (server->bufferedSocket[i]->bufferRead.finishRead == Finish &&
    server->bufferedSocket[i]->bufferRead.used == false) {
        to_verification_command(server->bufferedSocket[i], set,
                                server->client, server);
    }
}

int handle_client(server_t *server, int port)
{
    fd_set set;

    init_server(server, port);
    while (1) {
        to_init_fd_set(&set, server);
        to_connection_fd_set(&set, server);
        read_new_command(server, &set);
        for (size_t i = 0; i < server->nbrConnectionBufferSocket; i++) {
            handle_client_bis(i, server, &set);
        }
    }
    free_all_struct(server, &set);
    return 0;
}
