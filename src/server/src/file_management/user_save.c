/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-alberick.mahoussi
** File description:
** user_save
*/

#include "my_teams.h"

int save_client(u_int8_t *uuid, u_int8_t *username)
{
    FILE *file = fopen("src/server/log/user.txt", "a+");
    if (file == NULL)
        return (-1);
    fprintf(file, "%s %s 1\n", username, uuid);
    fclose(file);
    return (0);
}

void write_file(u_int8_t *buffer, client_t *client,
    FILE *tmp_file)
{
    u_int8_t **two_d = str_to_word_array(buffer, ' ');
    u_int8_t *name = client->username;
    u_int8_t *uuid = client->uuid;

    if (strcmp((char *)two_d[0], (char *)name) == 0) {
        fprintf(tmp_file, "%s %s 0\n", name, uuid);
    } else {
        fprintf(tmp_file, "%s", buffer);
    }
    for (int i = 0; two_d[i] != NULL; i++)
        free(two_d[i]);
    free(two_d);
}

int change_status(client_t *client)
{
    FILE *file = fopen("src/server/log/user.txt", "r");
    FILE *tmp_file = fopen("src/server/log/tmp.txt", "w+");
    size_t len = 0;
    ssize_t read;
    u_int8_t *buffer = malloc(sizeof(u_int8_t) * 1024);

    if (file == NULL || tmp_file == NULL || buffer == NULL)
        return (-1);
    while ((read = getline(&buffer, &len, file)) != 1) {
        write_file(buffer, client, tmp_file);
    }
    fclose(tmp_file);
    fclose(file);
    remove("src/server/log/user.txt");
    rename("src/server/log/tmp.txt", "src/server/log/user.txt");
    free(buffer);
    return 0;
}
