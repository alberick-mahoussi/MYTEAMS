/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** findOneOctets
*/

#include "../include/my_teams.h"

size_t to_find_one_octets(buffer_t *buffer, u_int8_t octets)
{
    size_t n = 0;

    for (; n < buffer->usedSize; n += 1) {
        if (buffer->octets[n] == octets) {
            return n;
        }
    }
    return 0;
}
