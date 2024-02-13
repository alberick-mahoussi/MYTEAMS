/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** to_create_response
*/

#include "client.h"

void to_create_response(client_t *client)
{
    write(client->perso.sockfd, client->response,
    compt_size(client->response));
}
