/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** handle_client_bis
*/

#include "client.h"

static int is_valid_opt(u_int8_t **command, client_teams_t const *arg,
            size_t i, client_t *client)
{
    if (strcmp((const char *)command[0], arg->comd) == 0) {
        COMMAND_GESTION[i].handler(client, command);
        return 1;
    }
    return 0;
}

void to_check_command_exist(u_int8_t **command,
                    client_t *client)
{
    int value = 0;

    for (size_t i = 0; i < ARRAY_SIZE(COMMAND_GESTION); i++) {
        if (value != 1) {
            value = is_valid_opt(command,
            &COMMAND_GESTION[i], i, client);
        }
    }
    if (value == 0) {
        printf("500 Unknow command.\r\n");
    }
}
