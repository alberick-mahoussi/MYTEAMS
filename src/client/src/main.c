/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-laetitia.bousch
** File description:
** main
*/

#include "client.h"

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        help();
        return (0);
    }
    if (ac == 3) {
        if (handle_client(av[1], atoi(av[2])) == 84)
            return 84;
    } else
        return (84);
    return (0);
}
