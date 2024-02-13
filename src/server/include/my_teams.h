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

typedef struct sock_s {
    int sockfd;
    struct sockaddr_in addr;
} sock_t;

void to_connection_sock_t(sock_t *sock, int port);
//void to_deconnection_sock_t(sock_t *sock);
//void to_read_sock_t(sock_t *sock);
//void to_write_sock_t(sock_t *sock);

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

typedef struct position_s {
    size_t chanel;
    size_t thread;
    size_t team;
    size_t teamUuid;
} position_t;

typedef struct buffer_s {
    u_int8_t *octets;
    size_t capacity;
    size_t usedSize;
    bool used;
    enum Read finishRead;
} buffer_t;

typedef struct msg_s {
    u_int8_t *uuid_sender;
    u_int8_t **msg_body;
    time_t *time_sent;
    size_t nbrMsg;
} msg_t;

typedef struct message_s {
    u_int8_t *msg;
    u_int8_t *uuid_;
    u_int8_t *uuid_use;
    time_t time;
} message_t;

typedef struct thread_s {
    message_t *msg;
    time_t time;
    u_int8_t *uuid_;
    u_int8_t *titleThread;
    u_int8_t *descriptionThread;
    u_int8_t *uuid_use;
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
    bool subscribe;
} team_t;

typedef struct client_s {
    buffer_t buffer;
    sock_t *sockConnect;
    msg_t *conv;
    team_t *team;
    u_int8_t **command;
    u_int8_t *username;
    u_int8_t *uuid;
    u_int8_t *ip;
    size_t nbrConv;
    size_t nbrTeam;
    bool login;
    position_t position;
} client_t;

void to_change_capacity(buffer_t *buffer, size_t new_capacity);
void to_clear_buffer_of_n_octets(buffer_t *buffer, size_t n);
void to_clear(buffer_t *buffer);
u_int8_t *to_read(buffer_t *buffer);
void to_write(buffer_t *buffer, u_int8_t *new_octets, size_t n);
size_t to_find_one_octets(buffer_t *buffer, u_int8_t octets);
u_int8_t *to_peek(buffer_t *buffer);

typedef struct buffered_socket_s {
    buffer_t bufferRead;
    buffer_t bufferWrite;
    sock_t sock;
} buffered_socket_t;

typedef struct server_s {
    buffered_socket_t **bufferedSocket;
    sock_t callBackSock;
    position_t position;
    client_t *client;
    size_t nbrClient;
    u_int8_t **command;
    team_t *team;
    size_t nbrTeam;
    size_t nbrConnectionBufferSocket;
} server_t;

void free_struct(server_t *server);
void free_all_struct(server_t *server, fd_set *set);
int handle_client(server_t *server, int port);
void read_new_command(server_t *server, fd_set *set);
int to_init_fd_set(fd_set *set, server_t *server);
int to_connection_fd_set(fd_set *set, server_t *server);
void to_create_new_client(server_t *server,
buffered_socket_t *bufferedSocket, u_int8_t **param);
void to_connection_new_buffered_socket(int new_fd,
                    buffered_socket_t *bufferedSocket, sock_t *sock);
void to_verification_command(buffered_socket_t *bufferedSocket,
                fd_set *set, client_t *client, server_t *server);
u_int8_t *to_clean_command(u_int8_t *command);
u_int8_t **str_to_word_array(u_int8_t *str, u_int8_t sep);
void init_server(server_t *server, int port);
client_t *to_check_client_use(server_t *server,
                buffered_socket_t *bufferedSocket);
size_t to_compt_n(u_int8_t *command);
size_t nb_ligne(u_int8_t **str);
size_t nb_convo(msg_t *str);
void to_check_realloc_struct_client(void *response);
void init_funct_send(buffered_socket_t *bufferedSocket, u_int8_t **param);

typedef struct teams_s {
    const char *comd;
    void (*handler)(u_int8_t **param, server_t *server,
    buffered_socket_t *bufferedSocket);
} teams_t;

void funct_login(u_int8_t **param, server_t *server,
buffered_socket_t *bufferedSocket);
void funct_logout(u_int8_t **param, server_t *server,
buffered_socket_t *bufferedSocket);
void funct_user(u_int8_t **param, server_t *server,
buffered_socket_t *bufferedSocket);
void funct_users(u_int8_t **param, server_t *server,
buffered_socket_t *bufferedSocket);
void funct_send(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_messages(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_msg(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_thread(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_chanel(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_team(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_unsubscribe(u_int8_t **param, server_t *server,
                        buffered_socket_t *bufferedSocket);
void funct_subscribe(u_int8_t **param, server_t *server,
                    buffered_socket_t *bufferedSocket);
void funct_subscribed(u_int8_t **param, server_t *server,
                    buffered_socket_t *bufferedSocket);
void funct_list_teams(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_list_chanel(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_list_threads(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);
void funct_list_repply(u_int8_t **param, server_t *server,
                buffered_socket_t *bufferedSocket);

void funct_reponse_thread_create(buffered_socket_t *bufferedSocket,
                            u_int8_t **param, client_t *client,
                            server_t *server);
void funct_reponse_chanel_create(buffered_socket_t *bufferedSocket,
                            u_int8_t **param, server_t *server,
                            client_t *client);
chanel_t *init_new_chanel(chanel_t **chanel, size_t size);
bool to_check_chanel(server_t *server, u_int8_t *param);
bool to_check_chanel_client(client_t *client, u_int8_t *param);
bool to_check_reply(u_int8_t *uuidTeam, server_t *server);
bool to_check_reply_client(u_int8_t *uuidTeam, client_t *server);
void funct_create_server_team(client_t *client, server_t *server);
message_t *init_new_msg_subs(message_t **msg, size_t size);
thread_t *init_new_thread_subs(thread_t **thread, size_t size, time_t time);
chanel_t *init_new_chanel_subs(chanel_t **chanel, size_t size);
void init_new_team_subs(client_t *client);
bool to_check_team_subs(server_t *server, u_int8_t *param);
bool to_check_thread_server_bis(server_t *server, int *tmpNbr,
                    bool tmp, u_int8_t *uuid_);
void funct_chanel_bis(u_int8_t **param, chanel_t *chanel_client,
                buffered_socket_t *bufferedSocket, chanel_t *chanel);
void init_reponse_unkonw_subscribe(buffered_socket_t *bufferedSocket,
                            u_int8_t *param, client_t *client);
bool to_check_reply_bis(server_t *server, check_t *tmpNbr, bool tmp,
                        u_int8_t *uuidTeam);
int save_client(u_int8_t *uuid, u_int8_t *username);
int change_status(client_t *client);
int save_thread(u_int8_t *uuid, u_int8_t *desc,
    u_int8_t *name);
int save_teams(u_int8_t *uuid, u_int8_t *desc,
    u_int8_t *name);
int save_channel(u_int8_t *uuid, u_int8_t *desc,
    u_int8_t *name);

static const teams_t COMMAND_GESTION[] = {
    {"LOGIN", funct_login},
    {"LOGOUT", funct_logout},
    {"USERS", funct_users},
    {"USER", funct_user},
    {"SEND", funct_send},
    {"MESSAGES", funct_messages},
    {"TEAM", funct_team},
    {"CHANEL", funct_chanel},
    {"THREAD", funct_thread},
    {"MSG", funct_msg},
    {"SUBSCRIBE", funct_subscribe},
    {"SUBSCRIBED", funct_subscribed},
    {"UNSUBSCRIBE", funct_unsubscribe},
    {"LIST_TEAMS", funct_list_teams},
    {"LIST_CHANEL", funct_list_chanel},
    {"LIST_THREAD", funct_list_threads},
    {"LIST_REPLIES", funct_list_repply},
    //{"INFO", funct_info},
};

#endif /* !SERVER_H_ */
