/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** utils_funct
*/

#include "my_teams.h"

size_t to_compt_n(u_int8_t *command)
{
    size_t n = 0;

    for (; command[n] != '\0'; n++);
    return n;
}

size_t nb_ligne(u_int8_t **str)
{
    size_t j = 0;

    for (; str[j] != NULL; j++);
    return j;
}

size_t nb_convo(msg_t *str)
{
    size_t j = 0;

    for (; str[j].uuid_sender != NULL; j++);
    return j;
}

void to_check_realloc_struct_client(void *response)
{
    if (response == NULL)
        perror("error realloc");
}
