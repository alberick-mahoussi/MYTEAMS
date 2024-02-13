/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-laetitia.bousch
** File description:
** client
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
    #define MAX_LENGTH 4096
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define _GNU_SOURCE

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/stat.h>
    #include <netinet/in.h>
    #include <stdio.h>
    #include <errno.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <ctype.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <signal.h>
    #include <uuid/uuid.h>

enum Read {
    Start,
    Read,
    Finish,
};

typedef struct check_s {
    int a;
    int b;
    int c;
} check_t;

typedef struct str_to_word_array_s {
    bool statusVirgule;
    int status;
    size_t i;
} str_to_word_array_t;

typedef struct position_s {
    size_t chanel;
    size_t thread;
    size_t team;
} position_t;

typedef struct buffer_s {
    u_int8_t *octets;
    size_t capacity;
    size_t usedSize;
    enum Read finishRead;
} buffer_t;

typedef struct perso_s {
    size_t sockfd;
    size_t port;
    struct sockaddr_in addr;
    u_int8_t *ip;
    u_int8_t *username;
    bool isConnected;
} perso_t;

typedef struct buffered_s {
    buffer_t bufferRead;
    buffer_t bufferWrite;
} buffered_t;

typedef struct msg_s {
    u_int8_t *uuid_sender;
    u_int8_t **msg_body;
    time_t timeMsg;
} msg_t;

typedef struct message_s {
    u_int8_t *msg;
    u_int8_t *uuid_;
} message_t;

typedef struct thread_s {
    message_t *msg;
    u_int8_t *uuid_;
    u_int8_t *titleThread;
    u_int8_t *descriptionThread;
    time_t time;
    size_t nbrMessage;
} thread_t;

typedef struct chanel_s {
    thread_t *thread;
    u_int8_t *uuid_;
    u_int8_t *usernameChanel;
    u_int8_t *descriptionChanel;
    size_t nbrThread;
} chanel_t;

typedef struct team_s {
    chanel_t *chanel;
    u_int8_t *uuid_;
    u_int8_t *usernameTeam;
    u_int8_t *descriptionTeam;
    size_t nbrChanel;
} team_t;

enum context {
    NO_USE,
    USE_TEAM,
    USE_CHANNEL,
    USE_THREAD,
};

typedef struct use_s {
    int context;
    u_int8_t *thread;
    u_int8_t *chanel;
    u_int8_t *team;
} use_t;

typedef struct client_s {
    int cControl;
    perso_t perso;
    use_t use;
    position_t position;
    msg_t *msg;
    size_t conv;
    size_t nbrTeam;
    buffered_t buffered;
    u_int8_t *response;
    u_int8_t *uuid;
    team_t *team;
} client_t;

typedef struct client_teams_s {
    const u_int8_t *comd;
    void (*handler)(client_t *client, u_int8_t **command);
} client_teams_t;

void funct_login(client_t *client, u_int8_t **command);
void funct_help(client_t *client, u_int8_t **command);
void funct_users(client_t *client, u_int8_t **command);
void funct_logout(client_t *client, u_int8_t **command);
void funct_user(client_t *client, u_int8_t **command);
void funct_send(client_t *client, u_int8_t **command);
void funct_messages(client_t *client, u_int8_t **command);
void funct_use(client_t *client, u_int8_t **command);
void funct_create(client_t *client, u_int8_t **command);
void funct_unsubscribe(client_t *client, u_int8_t **command);
void funct_subscribe(client_t *client, u_int8_t **command);
void funct_subscribed(client_t *client, u_int8_t **command);
void funct_list(client_t *client, u_int8_t **command);

void funct_response_login(client_t *client, u_int8_t **command);
void funct_response_users(client_t *client, u_int8_t **command);
void funct_response_user(client_t *client, u_int8_t **command);
void funct_response_send(client_t *client, u_int8_t **command);
void funct_response_messages(client_t *client, u_int8_t **command);
void funct_response_team(client_t *client, u_int8_t **command);
void funct_response_chanel(client_t *client, u_int8_t **command);
void funct_response_thread(client_t *client, u_int8_t **command);
void funct_response_msg(client_t *client, u_int8_t **command);
void funct_response_logout(client_t *client, u_int8_t **command);
void funct_response_unsubscribe(client_t *client, u_int8_t **command);
void funct_response_subscribe(client_t *client, u_int8_t **command);
void funct_response_subscribed(client_t *client, u_int8_t **command);
void funct_response_print_teams(client_t *client, u_int8_t **command);
void funct_response_print_chanel(client_t *client, u_int8_t **command);
void funct_response_print_threads(client_t *client, u_int8_t **command);
void funct_response_print_replies(client_t *client, u_int8_t **command);

void create_teams(u_int8_t **command, size_t size, client_t *client);
void create_channel(u_int8_t **command, client_t *client);
void create_thread(u_int8_t **command, client_t *client);
void create_reply(u_int8_t **command, client_t *client);
bool to_find_reply(client_t *client);
void create_team_server(u_int8_t **command,
u_int8_t *uuid_, client_t *client);
void create_team_chanel(u_int8_t **command,
u_int8_t *uuid_, client_t *client, u_int8_t *uuid_team);
void create_team_thread(u_int8_t **command,
                u_int8_t *uuid_, client_t *client, time_t time);
void create_team_msg(client_t *client, u_int8_t **command,
u_int8_t *uuid_thread);

bool agree_uuid_team(team_t *team, u_int8_t *uuid_);
bool agree_uuid_chanel(chanel_t *chanel, u_int8_t *uuid_);
bool agree_uuid_thread(thread_t *thread, u_int8_t *uuid_);
u_int8_t **str_to_word_array(u_int8_t *str, u_int8_t sep);
void free_double_array(u_int8_t **cmd);
u_int8_t *to_clean_command(u_int8_t *command);
size_t clean_str_bis(size_t i, u_int8_t *command);
void free_struct(client_t *client);
u_int8_t *get_command(int file_dp);
void to_read_input(client_t *client, fd_set *set);
void to_clear(buffer_t *buffer);
void init_set(fd_set *set, client_t *client);
int client_init(client_t *client, char *ip, int port);
void to_check_finish_read_command(client_t *client, fd_set *set);
void to_check_command_exist(u_int8_t **command,
                    client_t *client);
int compt_command_subs(u_int8_t **command);
void free_config(client_t *client);
void help(void);
void free_struct(client_t *client);
int strlen_2d(char **tab);
int compt_size(u_int8_t *response);
void to_create_response(client_t *client);
int count_nb_quotes(char *cmd);
void free_double_array(u_int8_t **cmd);
bool to_check_arg(u_int8_t *command);
u_int8_t **str_to_word_array_command(u_int8_t *str, u_int8_t sep);
u_int8_t *clear_username_client(u_int8_t *username);
bool nb_bis(u_int8_t *str, int *j, bool statusVirgule, int *compt);
void my_bis(str_to_word_array_t *compt, u_int8_t sep, u_int8_t *str);

static const client_teams_t COMMAND_GESTION[] = {
    {"/login", funct_login},
    {"/logout", funct_logout},
    {"/users", funct_users},
    {"/user", funct_user},
    {"/help", funct_help},
    {"/send", funct_send},
    {"/messages", funct_messages},
    {"/subscribe", funct_subscribe},
    {"/subscribed", funct_subscribed},
    {"/unsubscribe", funct_unsubscribe},
    {"/use", funct_use},
    {"/create", funct_create},
    {"/list", funct_list},
    //{"/info", funct_info},
    {"LOGIN", funct_response_login},
    {"USERS", funct_response_users},
    {"USER", funct_response_user},
    {"SEND", funct_response_send},
    {"MESSAGES", funct_response_messages},
    {"SUBSCRIBE", funct_response_subscribe},
    {"SUBSCRIBED", funct_response_subscribed},
    {"UNSUBSCRIBE", funct_response_unsubscribe},
    {"TEAM", funct_response_team},
    {"LOGOUT", funct_response_logout},
    {"CHANEL", funct_response_chanel},
    {"THREAD", funct_response_thread},
    {"REPLY", funct_response_msg},
    {"LIST_TEAMS", funct_response_print_teams},
    {"LIST_CHANEL", funct_response_print_chanel},
    {"LIST_THREAD", funct_response_print_threads},
    {"LIST_REPLIES", funct_response_print_replies},
};

#endif /* !SERVER_H_ */
