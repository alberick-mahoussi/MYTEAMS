/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** funct_command_tree
*/

#include "my_teams.h"
#include "logging_server.h"

void funct_subscribe_bis_bis(int i, int j, thread_t *thread, server_t *server)
{
    thread->titleThread = strdup(server->team[server->position.team].
    chanel[i].thread[j].titleThread);
    thread->descriptionThread = strdup(server->team[server->position.team].
    chanel[i].thread[j].descriptionThread);
    thread->uuid_ = strdup(server->team[server->position.team].chanel[i].
    thread[j].uuid_);
}

void funct_subscribe_bis(chanel_t *chanel, message_t *msg,
                            int i, server_t *server)
{
    thread_t *thread = NULL;

    for (int j = 0; j < server->team[server->position.team].
                                    chanel[i].nbrThread; j++) {
        thread = init_new_thread_subs(&chanel->thread, chanel->nbrThread,
        server->team[server->position.team].chanel[i].thread[j].time);
        funct_subscribe_bis_bis(i, j, thread, server);
        for (int k = 0; k < server->team[server->position.team].chanel[i].
                                                thread[j].nbrMessage; k++) {
            msg = init_new_msg_subs(&thread->msg, thread->nbrMessage);
            msg->msg = strdup(server->team[server->position.team].chanel[i].
            thread[j].msg[k].msg);
            msg->uuid_ = strdup(server->team[server->position.team].chanel[i].
            thread[j].msg[k].uuid_);
        }
        thread->nbrMessage += 1;
    }
}

void funct_subscribe_tree(chanel_t *chanel, server_t *server, client_t *client)
{
    thread_t *thread = NULL;
    message_t *msg = NULL;

    for (int i = 0; i < server->team[server->position.team].nbrChanel; i++) {
        chanel = init_new_chanel_subs(&client->team[client->nbrTeam].chanel,
        client->team[client->nbrTeam].nbrChanel);
        chanel->usernameChanel = strdup(server->team[server->position.team].
        chanel[i].usernameChanel);
        chanel->descriptionChanel = strdup(server->team[server->position.team].
        chanel[i].descriptionChanel);
        chanel->uuid_ = strdup(server->team[server->position.team].
        chanel[i].uuid_);
        funct_subscribe_bis(chanel, msg, i, server);
        chanel->nbrThread += 1;
    }
}

void print_funct_subscribe(buffered_socket_t *bufferedSocket, client_t *client
                            , u_int8_t **param)
{
    bufferedSocket->bufferWrite.usedSize = (to_compt_n(client->uuid)
    + to_compt_n(param[1]) + 12);
    bufferedSocket->bufferWrite.octets =
    realloc(bufferedSocket->bufferWrite.octets,
    bufferedSocket->bufferWrite.usedSize * sizeof(u_int8_t));
    bufferedSocket->bufferWrite.octets[0] = '\0';
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "SUBSCRIBE\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, client->uuid);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\n");
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, param[1]);
    bufferedSocket->bufferWrite.octets =
    strcat(bufferedSocket->bufferWrite.octets, "\0");
    write(client->sockConnect->sockfd,
    bufferedSocket->bufferWrite.octets, bufferedSocket->bufferWrite.usedSize);
    server_event_user_subscribed(param[1], client->uuid);
}

void funct_subscribe(u_int8_t **param, server_t *server,
                    buffered_socket_t *bufferedSocket)
{
    client_t *client = to_check_client_use(server, bufferedSocket);
    chanel_t *chanel = NULL;

    if (to_check_team_subs(server, param[1]) == false) {
        init_reponse_unkonw_subscribe(bufferedSocket, param[1], client);
        return;
    }
    init_new_team_subs(client);
    client->team[client->nbrTeam].usernameTeam =
    strdup(server->team[server->position.team].usernameTeam);
    client->team[client->nbrTeam].descriptionTeam =
    strdup(server->team[server->position.team].descriptionTeam);
    client->team[client->nbrTeam].uuid_ =
    strdup(server->team[server->position.team].uuid_);
    funct_subscribe_tree(chanel, server, client);
    print_funct_subscribe(bufferedSocket, client, param);
    client->nbrTeam += 1;
}
