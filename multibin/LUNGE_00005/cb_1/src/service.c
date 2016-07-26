#include "cgc_libc.h"
#include "cgc_malloc.h"
#include "cgc_types.h"

#define INPUT_SIZE 50

struct service {
    char *name;
    char *config;
    int read_fd;
    int orig_fd;
    int has_config;
    int input_fd;
    int output_fd;
    int configured;
    int order;
};

struct service services[] = {
    {
        .name = "contains",
        .has_config = 1,
    },
    {
        .name = "word-count",
    },
    {
        .name = "does-not-contain",
        .has_config = 1,
    },
    {
        .name = "compress",
    },
    {
        .name = "decompress",
    },
    {}
};

void send_string(int fd, char *str) {
    size_t size = 0;
    if (str != NULL) {
        size = strlen(str);
    }

    transmit_all(fd, (char *) &size, sizeof(size));
    if (size > 0) {
        transmit_all(fd, str, size);
    }
}

void config_service(int service_id) {
    char buf[INPUT_SIZE];
    int err;

    if (services[service_id].has_config) {
        memset(buf, 0, sizeof(buf));
        printf(STDOUT, "How do you want to configure '%s'?\n", services[service_id].name);

        err = read_until(STDIN, buf, sizeof(buf), '\n');
        if (err < 0)
            _terminate(3);

        services[service_id].config = strdup(buf);
    }
}

void send_config(int service_id) {
    if (services[service_id].has_config) {
        transmit_str(services[service_id].read_fd - 1, services[service_id].config);
        transmit_str(services[service_id].read_fd - 1, "\n");
    }
}

void send_service_fd(int service_id, int new_stdin, int new_stdout) {
    printf(STDOUT, "Setting %s to read from %u and write to %u (via %u)\n", services[service_id].name, new_stdin, new_stdout, services[service_id].read_fd - 1);
    
    if (transmit_all(services[service_id].read_fd - 1, (char *)&new_stdout, sizeof(new_stdout)) == 0)
        return;

    if (transmit_all(services[service_id].read_fd - 1, (char *)&new_stdin, sizeof(new_stdin)) == 0)
        return;
}

int get_service_by_position(int position) {
    int i;
    for (i = 0; services[i].name != NULL; i++) {
        if (services[i].configured && services[i].order == position)
            return i;
    }

    return -1;
}

void handle_configs(int enabled_count) {
    int i;
    /* handle each of the configurations */
    for (i = 0; i < enabled_count; i++) {
        int current_service = get_service_by_position(i);
        config_service(current_service);
    }

    for (i = 0; i < enabled_count; i++) {
        int current_service = get_service_by_position(i);
        send_config(current_service);
    }
}

void setup(void) {
    int i;
    for (i = 0; services[i].name != NULL; i++) {
        services[i].read_fd = (i * 2) + 4;
        services[i].orig_fd = services[i].read_fd;
    }
}

int print_available() {
    int i;
    printf(STDOUT, "available functions include:\n");
    for (i = 0; services[i].name != NULL; i++) {
        printf(STDOUT, "%u: %s\n", i, services[i].name);
    }

    return i;
}

void print_pipeline(int enabled_count) {
    /* show the pipeline */
    printf(STDOUT, "function pipeline:");
    for (int i = 0; i < enabled_count; i++) {
        int current_service = get_service_by_position(i);
        printf(STDOUT, " %s", services[current_service].name);
    }
    printf(STDOUT, "\n");
}

void terminate_service(int id) {
    if (services[id].has_config) {
        transmit_str(services[id].read_fd - 1, "\n"); // services[service_id].config);
//        send_string(services[id].read_fd - 1, "x\n");
    }
    
    send_service_fd(id, 0xFFFF, 0xFFFF);
}

void exit(int ret_code) {
    int i;
    for (i = 0; services[i].name != NULL; i++) {
        terminate_service(i);
    }

    _terminate(ret_code);
}

int enable_services(int service_count) {
    char buf[INPUT_SIZE];
    int err;
    int current_id = 0;
    int i;
    int j;

    for (i = 0; i < service_count; i++) {

        printf(STDOUT, "Which function do you wish to include?  Available: [");
        for (j = 0; j < service_count; j++) {
            if (services[j].configured == 0)
                printf(STDOUT, "%u", j);
        }

        printf(STDOUT, "] (Enter an empty line to stop configuration)\n");

        memset(buf, 0, sizeof(buf));
        err = read_until(STDIN, buf, sizeof(buf), '\n');
        if (buf[0] == 0)
            break;

        if (buf[0] >= '0' && buf[0] <= '9') {
            current_id = buf[0] - '0';
        } else {
            printf(STDOUT, "Invalid function! %u\n", buf[0]);
            exit(3);
        }

        if (services[current_id].configured) {
            printf(STDOUT, "this function is already included in the pipeline!\n");
            exit(4);
        }

        services[current_id].configured = 1;
        services[current_id].order = i;
    }
    return i;
}

/* handle sending the output ports to each of the executables */
void setup_output(int enabled_count) {
    int i;
    for (i = 0; i < enabled_count; i++) {
        int current_service = get_service_by_position(i);
        int next_service = get_service_by_position(i + 1);
        int input_fd = STDIN;
        int output_fd = STDOUT;

        if (current_service == -1)
            _terminate(5);

        if (next_service >= 0) {
            output_fd = services[next_service].read_fd - 1;
        }
           
        if (i > 0) {
            input_fd = services[current_service].read_fd;
        }

        send_service_fd(current_service, input_fd, output_fd);
    }
}

void terminate_unused(int service_count) {
    int i;
    /* cause the servicse that are not to be setup to exit */
    for (i = 0; i < service_count; i++) {
        if (services[i].configured == 0) {
            terminate_service(i);
        }
    }
}

int main(void) {
    int service_count;
    int enabled_count;

    setup();
    printf(STDOUT, "Function pipelines made easy!\n");
    service_count = print_available();
    enabled_count = enable_services(service_count);

    if (enabled_count == 0) {
        printf(STDOUT, "no functions configured.\n");
        exit(5);
    }

    terminate_unused(service_count);
    print_pipeline(enabled_count);
    handle_configs(enabled_count);
    setup_output(enabled_count);

    return 1;
}
