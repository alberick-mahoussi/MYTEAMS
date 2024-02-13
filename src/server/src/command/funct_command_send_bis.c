/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_send_bis
*/

#include "my_teams.h"
#include "logging_server.h"

void init_funct_send(buffered_socket_t *bufferedSocket, u_int8_t **param)
{
    bufferedSocket->bufferWrite.usedSize = to_compt_n(param[0]) + 1;
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    (to_compt_n(param[0]) + 2) * sizeof(u_int8_t));
    to_check_realloc(bufferedSocket->bufferWrite.octets);
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[0]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
}
