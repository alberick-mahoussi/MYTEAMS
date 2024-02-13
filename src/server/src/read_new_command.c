/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** read_new_command
*/

#include "my_teams.h"

static void read_new_command_bis(size_t i, server_t *server)
{
    ssize_t rd;

    if ((rd = read(server->bufferedSocket[i]->sock.sockfd,
    server->bufferedSocket[i]->bufferRead.octets, 256)) == -1) {
        perror("error read");
    }
    server->bufferedSocket[i]->bufferRead.usedSize += rd;
    if (rd < 256 && server->bufferedSocket[i]->bufferRead.usedSize > 0) {
        server->bufferedSocket[i]->bufferRead.finishRead = Finish;
        server->bufferedSocket[i]->bufferRead.octets
        [server->bufferedSocket[i]->bufferRead.usedSize] = '\0';
        server->bufferedSocket[i]->bufferRead.used = false;
    }
}

void read_new_command(server_t *server, fd_set *set)
{
    for (size_t i = 0; i < server->nbrConnectionBufferSocket; ++i) {
        if (FD_ISSET(server->bufferedSocket[i]->sock.sockfd, set)) {
            server->bufferedSocket[i]->bufferRead.finishRead = Read;
            server->bufferedSocket[i]->bufferRead.octets =
            realloc(server->bufferedSocket[i]->bufferRead.octets, 256 *
            sizeof(u_int8_t));
            to_check_realloc(server->bufferedSocket[i]->bufferRead.octets);
            read_new_command_bis(i, server);
        }
    }
}
