/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** clearBufferOfNOctets
*/

#include "my_teams.h"

void to_clear_buffer_of_n_octets(buffer_t *buffer, size_t n)
{
    size_t new_used_size = buffer->usedSize - n;
    u_int8_t *tmp_buffer = malloc(sizeof(u_int8_t) * new_used_size);

    if (tmp_buffer == NULL) {
        return;
    }
    memcpy(tmp_buffer, &buffer->octets[n], new_used_size);
    to_clear(buffer);
    buffer->usedSize = new_used_size;
    buffer->octets = malloc(sizeof(u_int8_t) * new_used_size);
    if (buffer->octets == NULL) {
        return;
    }
    memcpy(buffer->octets, tmp_buffer, new_used_size);
}

void to_clear(buffer_t *buffer)
{
    free(buffer->octets);
    buffer->usedSize = 0;
}
