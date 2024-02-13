/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** readAndWriteBuffer
*/

#include "my_teams.h"

size_t to_find_command(buffer_t *buffer)
{
    size_t n = 0;

    for (; buffer->octets[n] != '\0'; n++);
    return n;
}

u_int8_t *to_read(buffer_t *buffer)
{
    size_t n = to_find_command(buffer);
    u_int8_t *tmp_command = malloc(sizeof(u_int8_t) * (n + 1));

    if (tmp_command == NULL || n == 0) {
        return NULL;
    }
    memcpy(tmp_command, buffer->octets, n);
    to_clear_buffer_of_n_octets(buffer, n);
    tmp_command[n] = '\0';
    return tmp_command;
}

void to_write(buffer_t *buffer, u_int8_t *new_octets, size_t n)
{
    if ((buffer->usedSize + n) > buffer->capacity) {
        return;
    }
    buffer->octets = realloc(buffer->octets, n * sizeof(u_int8_t));
    to_check_realloc(buffer->octets);
    memcpy(&buffer->octets[n], new_octets, n);
}

u_int8_t *to_peek(buffer_t *buffer)
{
    size_t n = to_find_command(buffer);
    u_int8_t *tmp_command = malloc(sizeof(u_int8_t) * (n + 1));

    if (tmp_command == NULL || n == 0) {
        return NULL;
    }
    memcpy(tmp_command, buffer->octets, n);
    to_clear_buffer_of_n_octets(buffer, n);
    tmp_command[n] = '\0';
    return tmp_command;
}
