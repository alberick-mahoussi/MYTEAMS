/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** main
*/

#include "my_teams.h"

int main(int ac, char **av)
{
    server_t server;

    if (ac != 2) {
        return 84;
    }
    if (handle_client(&server, atoi(av[1])) == -1) {
        return 84;
    }
    free_struct(&server);
    return 0;
}
