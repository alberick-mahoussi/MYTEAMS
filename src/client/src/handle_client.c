/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** client_cli
*/

#include "client.h"

void to_read_server(client_t *client, fd_set *set)
{
    int rd = read(client->perso.sockfd,
                    client->buffered.bufferRead.octets, 256);

    client->buffered.bufferRead.finishRead = Read;
    if (rd == -1) {
        (client->perso.isConnected == true) ? funct_logout(client, NULL) : 0;
        (rd == 0) ? close(client->perso.sockfd), exit(0) : 0;
        perror("error read");
    }
    client->buffered.bufferRead.usedSize += rd;
    if (rd < 256 && client->buffered.bufferRead.usedSize > 0) {
        client->buffered.bufferRead.finishRead = Finish;
        client->buffered.bufferRead.octets
        [client->buffered.bufferRead.usedSize] = '\0';
    }
}

u_int8_t *get_command(int file_dp)
{
    size_t line = 0;
    u_int8_t *cmd = malloc(sizeof(u_int8_t) * MAX_LENGTH);
    ssize_t rd = 0;

    if (cmd == NULL) {
        return NULL;
    }
    rd = read(file_dp, cmd, MAX_LENGTH);
    if (rd == -1) {
        return NULL;
    }
    cmd[rd] = '\0';
    return (cmd);
}

int clock_client(fd_set *set, client_t *client)
{
    while (client->cControl == 1) {
        init_set(set, client);
        if (select(FD_SETSIZE, set, NULL, NULL, NULL) < 0) {
            return -1;
        } if (FD_ISSET(STDIN_FILENO, set)) {
            to_read_input(client, set);
        } if (FD_ISSET(client->perso.sockfd, set)) {
            client->buffered.bufferRead.octets =
            realloc(client->buffered.bufferRead.octets, 256 *
            sizeof(u_int8_t));
            to_read_server(client, set);
            to_check_finish_read_command(client, set);
        }
    }
    free_config(client);
    return (0);
}

int handle_client(char *ip, int port)
{
    client_t *client = malloc(sizeof(client_t));
    fd_set set;

    if (client == NULL) {
        return (-1);
    }
    if (client_init(client, ip, port) == -1) {
        perror("error to connect");
    }
    clock_client(&set, client);
    return (0);
}
