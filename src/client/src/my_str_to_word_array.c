/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** my_str_to_word_array
*/

#include "client.h"

static size_t nb_ligne_str_to_word_array(u_int8_t *str, u_int8_t sep)
{
    size_t compt = 0;
    size_t j = 0;

    for (; str[j] == sep; j++);
    for (; str[j] != '\0'; j++) {
        if (str[j] == sep) {
            compt++;
        }
    }
    compt++;
    return compt;
}

static size_t my_strlen_to_word_array(u_int8_t *str, u_int8_t sep)
{
    size_t i = 0;

    for (; str[i] != sep && str[i] != '\0'; i++);
    return i;
}

static u_int8_t copy_char(u_int8_t str, u_int8_t sep, u_int8_t tmp)
{
    if (str != sep)
        tmp = str;
    return tmp;
}

u_int8_t **str_to_word_array(u_int8_t *str, u_int8_t sep)
{
    size_t compt_line = nb_ligne_str_to_word_array(str, sep);
    size_t l = 0;
    size_t i = 0;
    size_t stock = 0;
    u_int8_t **tmp = malloc(sizeof(u_int8_t *) * (compt_line + 1));

    for (size_t j = 0; j < compt_line; j++, i++) {
        stock = my_strlen_to_word_array(&str[i], sep);
        tmp[j] = malloc(sizeof(u_int8_t) * (stock + 1));
        for (l = 0; l < stock; l++, i++) {
            tmp[j][l] = copy_char(str[i], sep, tmp[j][l]);
        }
        tmp[j][stock] = '\0';
    }
    tmp[compt_line] = NULL;
    return tmp;
}
