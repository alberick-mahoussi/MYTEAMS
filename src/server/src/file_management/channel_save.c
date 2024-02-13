/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** channel_save
*/

#include "my_teams.h"

int save_channel(u_int8_t *uuid, u_int8_t *desc,
    u_int8_t *name)
{
    FILE *file = fopen("src/server/log/channels.txt", "a+");

    if (file == NULL)
        return (-1);
    fprintf(file, "%s %s %s\n", name, uuid, desc);
    fclose(file);
    return (0);
}
