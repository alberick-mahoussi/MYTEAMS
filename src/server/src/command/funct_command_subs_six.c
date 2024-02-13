/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_subs_six
*/

#include "my_teams.h"
#include "logging_server.h"

void init_reponse_unkonw_subscribe(buffered_socket_t *bufferedSocket,
                            u_int8_t *param, client_t *client)
{
    bufferedSocket->bufferWrite.usedSize = (to_compt_n(param) + 18);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "SUBSCRIBE\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "UNKNOW\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd,
    bufferedSocket->bufferWrite.octets, bufferedSocket->bufferWrite.usedSize);
}
