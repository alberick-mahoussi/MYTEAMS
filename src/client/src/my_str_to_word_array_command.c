/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** my_str_to_word_array_command
*/

#include "client.h"

static size_t nb_ligne_str_to_word_array(u_int8_t *str, u_int8_t sep)
{
    size_t compt = 0;
    bool statusSep = false;
    bool s = false;
    size_t j = 0;

    while (str[j] != '\0') {
        if (str[j] == '"') {
            s = nb_bis(str, &j, s, &compt);
            continue;
        }
        if (str[j] == sep && statusSep == false && s == false) {
            statusSep = true;
            compt++;
        }
        j++;
    }
    compt++;
    return compt;
}

static size_t my_strlen_to_word_array_bis(u_int8_t *str, int *i)
{
    if (str[(*i) + 1] != '\0') {
        i++;
        return -1;
    }
    return 0;
}

static size_t my_strlen_to_word_array(u_int8_t *str, u_int8_t sep)
{
    str_to_word_array_t *compt = malloc(sizeof(str_to_word_array_t));

    compt->i = 0;
    compt->statusVirgule = false;
    compt->status = 0;
    while (str[compt->i] != '\0') {
        if (compt->status == -1)
            break;
        if (str[compt->i] == '"' && compt->statusVirgule == true) {
            compt->status = my_strlen_to_word_array_bis(str, &compt->i);
            compt->i++;
        } else {
            my_bis(compt, sep, str);
        }
    }
    return compt->i;
}

static u_int8_t *copy_char(u_int8_t *str, size_t stock,
                            u_int8_t *tmp, size_t post)
{
    for (int i = 0; i < stock; i++, post++) {
        tmp[i] = str[post];
    }
    return tmp;
}

u_int8_t **str_to_word_array_command(u_int8_t *str, u_int8_t sep)
{
    size_t compt_line = nb_ligne_str_to_word_array(str, sep);
    size_t l = 0;
    size_t i = 0;
    size_t stock = 0;
    u_int8_t **tmp = malloc(sizeof(u_int8_t *) * (compt_line + 1));

    for (size_t j = 0; j < compt_line; j++) {
        stock = my_strlen_to_word_array(&str[i], sep);
        tmp[j] = malloc(sizeof(u_int8_t) * (stock + 1));
        tmp[j] = copy_char(str, stock, tmp[j], i);
        i += stock;
        if (j < compt_line) {
            i++;
        }
        tmp[j][stock] = '\0';
    }
    tmp[compt_line] = NULL;
    return tmp;
}
