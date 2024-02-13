/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** help
*/

#include "client.h"

void help(void)
{
    printf("Usage: ./myteams_cli ip port\n\t");
    printf("ip\tis the server ip address on which the server socket listens");
    printf("\n\tport\tis the port number on which the server socket listen\n");
}

void funct_help(client_t *client, u_int8_t **command)
{
    printf("USAGE:\n\t/help display help\n\
        /login [\"username\"]: set the user_name used by client\n\
        /logout: disconnect the client from the server\n");
}
