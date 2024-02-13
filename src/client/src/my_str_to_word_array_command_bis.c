/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** my_str_to_word_array_bis
*/

#include "client.h"

bool nb_bis(u_int8_t *str, int *j, bool statusVirgule, int *compt)
{
    if (statusVirgule == true) {
        if (str[(*j) + 1] != '\0') {
            (*compt)++;
            (*j)++;
        }
        statusVirgule = false;
    } else {
        statusVirgule = true;
    }
    (*j)++;
    return statusVirgule;
}

void my_bis(str_to_word_array_t *compt, u_int8_t sep, u_int8_t *str)
{
    if (str[compt->i] == '"' && compt->statusVirgule == false) {
        compt->statusVirgule = true;
        compt->i++;
    }  else if (str[compt->i] == sep && compt->statusVirgule == false)
        compt->status = -1;
    else
        compt->i++;
}
