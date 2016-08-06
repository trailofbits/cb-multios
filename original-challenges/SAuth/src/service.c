#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PACKET_SIZE 35000
#define NUM_CREDS 16
#define MIN_PASSWD 8

struct server;

typedef unsigned char byte;
typedef byte boolean;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int (*service_handler_t) (struct server *, byte);

typedef struct {
    char *username;
    char *password;
} cred_t;

typedef struct server {
    cred_t credentials[NUM_CREDS];
    byte packet[PACKET_SIZE];
    unsigned int packet_idx, packet_len;
    unsigned int packet_seq;

    service_handler_t service_handler;
    boolean is_auth;
} server_t;

enum {
    MSG_DISCONNECT = 100,
    MSG_IGNORE,
    MSG_UNRECOGNIZED,
    MSG_SERVICE_REQUEST,
    MSG_SERVICE_ACCEPT,
    MSG_USERAUTH_REQUEST = 110,
    MSG_USERAUTH_FAILURE,
    MSG_USERAUTH_SUCCESS,
    MSG_USERAUTH_BANNER,
    MSG_USERAUTH_PASSWD_CHANGEREQ = 120,
};

static size_t mystrndup(const char *str, size_t n, char **out)
{
    char *result;

    if (strlen(str) < n)
        n = strlen(str);

    if (n == 0 || (result = malloc(n + 1)) == NULL)
        return 0;

    memcpy(result, str, n);
    result[n] = 0;
    *out = result;

    return str[n] == 0 ? n+1 : n;
}

static void init_creds(server_t *server, const char *secrets)
{
    size_t i, n, count = 0;

    for (i = 0; i < NUM_CREDS; i++)
    {
        char *s;
        while ((n = mystrndup(&secrets[count], 8, &s)) == 0) count++;
        count += n;
        server->credentials[i].username = s;

        while ((n = mystrndup(&secrets[count], 8, &s)) == 0) count++;
        count += n;
        server->credentials[i].password = s;
    }
}

static uint32 recv_bytes(server_t *server, uint32 count)
{
    /* align to 8-byte boundary */
    if (count & 7)
        count = (count + 7) & ~7;

    if ((count + server->packet_len) > PACKET_SIZE)
        return 0;
    if (count > PACKET_SIZE)
        return 0;

    if (fread((char *)&server->packet[server->packet_len], count, stdin) != count)
        return 0;

    server->packet_len += count;

    return count;
}

static void clear_packet(server_t *server)
{
    server->packet_idx = 0;
    server->packet_len = 0;
}

static void init_packet(server_t *server)
{
    clear_packet(server);

    /* reserve space for the header */
    server->packet_idx += 5;
    server->packet_len += 5;
}

static int get_byte(server_t *server, byte *out)
{
    if (server->packet_idx + 1 > server->packet_len)
        return 0;

    *out = server->packet[server->packet_idx++];
    return 1;
}

static int get_boolean(server_t *server, boolean *out)
{
    return get_byte(server, out);
}

static int get_uint32(server_t *server, uint32 *out)
{
    uint32 result = 0;

    if (server->packet_idx + 4 > server->packet_len)
        return 0;

    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    *out = result;
    return 1;
}

static int get_uint64(server_t *server, uint64 *out)
{
    uint64 result = 0;

    if (server->packet_idx + 8 > server->packet_len)
        return 0;

    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    result <<= 8;
    result |= server->packet[server->packet_idx++];
    *out = result;
    return 1;
}

static int write_byte(server_t *server, byte b)
{
    if (server->packet_len + 1 > PACKET_SIZE)
        return 0;

    server->packet[server->packet_idx++] = b;
    if (server->packet_idx > server->packet_len)
        server->packet_len = server->packet_idx;
    return 1;
}

static int write_boolean(server_t *server, boolean b)
{
    return write_byte(server, b);
}

static int write_uint32(server_t *server, uint32 x)
{
    if (server->packet_len + 4 > PACKET_SIZE)
        return 0;

    server->packet[server->packet_idx++] = x >> 24;
    server->packet[server->packet_idx++] = x >> 16;
    server->packet[server->packet_idx++] = x >> 8;
    server->packet[server->packet_idx++] = x;
    if (server->packet_idx > server->packet_len)
        server->packet_len = server->packet_idx;
    return 1;
}

static int write_uint64(server_t *server, uint64 x)
{
    if (server->packet_len + 8 > PACKET_SIZE)
        return 0;

    server->packet[server->packet_idx++] = x >> 56;
    server->packet[server->packet_idx++] = x >> 48;
    server->packet[server->packet_idx++] = x >> 40;
    server->packet[server->packet_idx++] = x >> 32;
    server->packet[server->packet_idx++] = x >> 24;
    server->packet[server->packet_idx++] = x >> 16;
    server->packet[server->packet_idx++] = x >> 8;
    server->packet[server->packet_idx++] = x;
    if (server->packet_idx > server->packet_len)
        server->packet_len = server->packet_idx;
    return 1;
}

static int write_string(server_t *server, const char *s, uint32 length)
{
    if (!write_uint32(server, length))
        return 0;

    if (server->packet_len + length > PACKET_SIZE)
        return 0;

    memcpy(&server->packet[server->packet_idx], s, length);
    server->packet_idx += length;
    if (server->packet_idx > server->packet_len)
        server->packet_len = server->packet_idx;
    return 1;
}

static int safe_memcpy(server_t *server, char *dst, unsigned short n)
{
    /* prevent reading past end of buffer */
    if (server->packet_idx + n > PACKET_SIZE)
        n = PACKET_SIZE - server->packet_idx;
    memcpy(dst, &server->packet[server->packet_idx], n);
    server->packet_idx += n;
    return 1;
}

static int safe_strdup(server_t *server, char **out, unsigned short n)
{
    char *result;

    result = malloc(n + 1);
    if (result == NULL)
        return 0;

    if (!safe_memcpy(server, result, n))
    {
        free(result);
        return 0;
    }
    result[n] = 0;

    *out = result;
    return 1;
}

static int get_string(server_t *server, char *out, size_t n)
{
    uint32 length;

    if (!get_uint32(server, &length))
        return 0;

    if (length + 1 > n)
        return 0;

    if (server->packet_idx + length > server->packet_len)
        return 0;

#ifdef PATCHED_1
    if (length > server->packet_len)
        return 0;
#endif

    if (safe_memcpy(server, out, length))
    {
        out[length] = 0;
        return 1;
    }

    return 0;
}

static int get_string_alloc(server_t *server, char **out)
{
    uint32 length;

    if (!get_uint32(server, &length))
        return 0;

    if (server->packet_idx + length > server->packet_len)
        return 0;

#ifdef PATCHED_1
    if (length > server->packet_len)
        return 0;
#endif

    return safe_strdup(server, out, length);
}

static uint32 recv_packet(server_t *server)
{
    uint32 packet_len;
    byte padding_len;

    clear_packet(server);

    if (!recv_bytes(server, 8))
        return 0;

    if (!get_uint32(server, &packet_len))
        return 0;
    if (!get_byte(server, &padding_len))
        return 0;

    if (packet_len < 1 || padding_len + 1 > packet_len)
        return 0;

    if (packet_len > 4 && !recv_bytes(server, packet_len - 4))
        return 0;

    packet_len--; /* remove padding length byte */
    /* remove padding bytes */
    server->packet_len -= padding_len;
    return server->packet_len - server->packet_idx;
}

static int send_packet(server_t *server)
{
    size_t bytes;
    byte padding_len;

    if (server->packet_len > 32768)
        return 0;

    /* initialize padding_len */
    padding_len = 8 - (server->packet_len % 8);

    /* append padding */
    random(&server->packet[server->packet_len], padding_len, &bytes);
    server->packet_len += padding_len;

    /* fix header */
    server->packet_idx = 0;
    write_uint32(server, server->packet_len - 4);
    write_byte(server, padding_len);

    fwrite((char *)server->packet, server->packet_len, stdout);
    return 1;
}

static int send_unrecognized(server_t *server)
{
    init_packet(server);
    write_byte(server, MSG_UNRECOGNIZED);
    write_uint32(server, server->packet_seq - 1);
    return send_packet(server);
}

static int send_disconnect(server_t *server)
{
    init_packet(server);
    write_byte(server, MSG_DISCONNECT);
    return send_packet(server);
}

static int send_service_accept(server_t *server, const char *service_name)
{
    init_packet(server);
    write_byte(server, MSG_SERVICE_ACCEPT);
    write_string(server, service_name, strlen(service_name));
    return send_packet(server);
}

static int send_userauth_failure(server_t *server)
{
    init_packet(server);
    write_byte(server, MSG_USERAUTH_FAILURE);
    write_string(server, "password", 8);
    write_boolean(server, 0);
    return send_packet(server);
}

static int send_userauth_success(server_t *server)
{
    init_packet(server);
    write_byte(server, MSG_USERAUTH_SUCCESS);
    return send_packet(server);
}

static int send_userauth_changereq(server_t *server, const char *prompt)
{
    init_packet(server);
    write_byte(server, MSG_USERAUTH_PASSWD_CHANGEREQ);
    write_string(server, prompt, strlen(prompt));
    return send_packet(server);
}

static int userauth_password(server_t *server, const char *username, const char *service_name)
{
    int res = 0, i;
    char *password = NULL, *new_password = NULL;
    cred_t *cred = NULL;
    boolean mode, success = 0;

    if (!get_boolean(server, &mode))
        return 0;

    if (!get_string_alloc(server, &password))
        goto done;

    if (mode && !get_string_alloc(server, &new_password))
        goto done;

    /* lookup user */
    for (i = 0; i < NUM_CREDS; i++)
        if (strcmp(username, server->credentials[i].username) == 0)
            cred = &server->credentials[i];

    fprintf(stderr, "Found user %x (username=%s)\n", cred, username);

    /* compare user's password (order matters to prevent timing attack) */
    success = strcmp(password, cred == NULL ? "fakepassword" : cred->password) == 0 && cred != NULL;

    /* if successful, check if new_password is compliant and change it */
    if (success && new_password)
    {
        if (strlen(new_password) < MIN_PASSWD)
            res = send_userauth_changereq(server, "Too short");
        else
        {
            free(cred->password);
            cred->password = new_password;
            new_password = NULL;

            res = send_userauth_success(server);
            server->is_auth = 1;
        }
    }
    else if (success)
    {
        res = send_userauth_success(server);
        server->is_auth = 1;
    }
    else
    {
        res = send_userauth_failure(server);
    }

done:
    free(password);
    free(new_password);
    return res;
}

static int userauth_handler(server_t *server, byte type)
{
    int res = 0;
    char *username = NULL, *service_name = NULL, *auth_name = NULL;

    if (type != MSG_USERAUTH_REQUEST)
        return send_unrecognized(server);

    if (!get_string_alloc(server, &username))
        goto done;

    if (!get_string_alloc(server, &service_name))
        goto done;

    if (!get_string_alloc(server, &auth_name))
        goto done;

    if (strcmp(auth_name, "password") == 0)
        res = userauth_password(server, username, service_name);
    else
        res = send_userauth_failure(server);

done:
    free(username);
    free(service_name);
    free(auth_name);
    return res;
}

static int handle_service_request(server_t *server)
{
    char service_name[256];

    if (!get_string(server, service_name, sizeof(service_name)))
        return 0;

    if (strcmp(service_name, "userauth") == 0)
    {
        server->service_handler = userauth_handler;
        return send_service_accept(server, "userauth");
    }

    return 0;
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    void *secret_page = (void *)secret_page_i;
    server_t server;

    memset(&server, 0, sizeof(server));
    init_creds(&server, secret_page);

    while (1)
    {
        byte msg;
        uint32 n = recv_packet(&server);
        if (n == 0)
            break;

        server.packet_seq++;

        if (!get_byte(&server, &msg))
            break;
        if (msg == MSG_DISCONNECT)
        {
            break;
        }
        else if (msg == MSG_IGNORE)
        {
            continue;
        }
        else if (msg == MSG_SERVICE_REQUEST)
        {
            if (!handle_service_request(&server))
                break;
        }
        else if (server.service_handler)
        {
            if (!server.service_handler(&server, msg))
                break;
        }
        else
        {
            send_unrecognized(&server);
        }
    }

    send_disconnect(&server);
    return 0;
}
