/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** thread_save
*/

#include "my_teams.h"

int save_thread(u_int8_t *uuid, u_int8_t *desc,
    u_int8_t *name)
{
    FILE *file = fopen("src/server/log/threads.txt", "a+");

    if (file == NULL)
        return (-1);
    fprintf(file, "%s %s %s\n", name, uuid, desc);
    fclose(file);
    return (0);
}

int reply_save(u_int8_t *uuid_reply, u_int8_t *comment)
{
    FILE *file = fopen("src/server/log/reply.txt", "a+");

    if (file == NULL) {
        return (-1);
    }
    fprintf(file, "%s %s\n", uuid_reply, comment);
    return (0);
}
