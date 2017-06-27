#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"
#include "cgc_cgc_types.h"

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

void cgc_send_string(int fd, char *str) {
    cgc_size_t size = 0;
    if (str != NULL) {
        size = cgc_strlen(str);
    }

    cgc_transmit_all(fd, (char *) &size, sizeof(size));
    if (size > 0) {
        cgc_transmit_all(fd, str, size);
    }
}

void cgc_config_service(int service_id) {
    char buf[INPUT_SIZE];
    int err;

    if (services[service_id].has_config) {
        cgc_memset(buf, 0, sizeof(buf));
        cgc_printf(STDOUT, "How do you want to configure '%s'?\n", services[service_id].name);

        err = cgc_read_until(STDIN, buf, sizeof(buf), '\n');
        if (err < 0)
            cgc__terminate(3);

        services[service_id].config = cgc_strdup(buf);
    }
}

void cgc_send_config(int service_id) {
    if (services[service_id].has_config) {
        cgc_transmit_str(services[service_id].read_fd - 1, services[service_id].config);
        cgc_transmit_str(services[service_id].read_fd - 1, "\n");
    }
}

void cgc_send_service_fd(int service_id, int new_stdin, int new_stdout) {
    cgc_printf(STDOUT, "Setting %s to read from %u and write to %u (via %u)\n", services[service_id].name, new_stdin, new_stdout, services[service_id].read_fd - 1);
    
    if (cgc_transmit_all(services[service_id].read_fd - 1, (char *)&new_stdout, sizeof(new_stdout)) == 0)
        return;

    if (cgc_transmit_all(services[service_id].read_fd - 1, (char *)&new_stdin, sizeof(new_stdin)) == 0)
        return;
}

int cgc_get_service_by_position(int position) {
    int i;
    for (i = 0; services[i].name != NULL; i++) {
        if (services[i].configured && services[i].order == position)
            return i;
    }

    return -1;
}

void cgc_handle_configs(int enabled_count) {
    int i;
    /* handle each of the configurations */
    for (i = 0; i < enabled_count; i++) {
        int current_service = cgc_get_service_by_position(i);
        cgc_config_service(current_service);
    }

    for (i = 0; i < enabled_count; i++) {
        int current_service = cgc_get_service_by_position(i);
        cgc_send_config(current_service);
    }
}

void cgc_setup(void) {
    int i;
    for (i = 0; services[i].name != NULL; i++) {
        services[i].read_fd = (i * 2) + 4;
        services[i].orig_fd = services[i].read_fd;
    }
}

int cgc_print_available() {
    int i;
    cgc_printf(STDOUT, "available functions include:\n");
    for (i = 0; services[i].name != NULL; i++) {
        cgc_printf(STDOUT, "%u: %s\n", i, services[i].name);
    }

    return i;
}

void cgc_print_pipeline(int enabled_count) {
    /* show the pipeline */
    cgc_printf(STDOUT, "function pipeline:");
    for (int i = 0; i < enabled_count; i++) {
        int current_service = cgc_get_service_by_position(i);
        cgc_printf(STDOUT, " %s", services[current_service].name);
    }
    cgc_printf(STDOUT, "\n");
}

void cgc_terminate_service(int id) {
    if (services[id].has_config) {
        cgc_transmit_str(services[id].read_fd - 1, "\n"); // services[service_id].config);
//        send_string(services[id].read_fd - 1, "x\n");
    }
    
    cgc_send_service_fd(id, 0xFFFF, 0xFFFF);
}

void cgc_exit(int ret_code) {
    int i;
    for (i = 0; services[i].name != NULL; i++) {
        cgc_terminate_service(i);
    }

    cgc__terminate(ret_code);
}

int cgc_enable_services(int service_count) {
    char buf[INPUT_SIZE];
    int err;
    int current_id = 0;
    int i;
    int j;

    for (i = 0; i < service_count; i++) {

        cgc_printf(STDOUT, "Which function do you wish to include?  Available: [");
        for (j = 0; j < service_count; j++) {
            if (services[j].configured == 0)
                cgc_printf(STDOUT, "%u", j);
        }

        cgc_printf(STDOUT, "] (Enter an empty line to stop configuration)\n");

        cgc_memset(buf, 0, sizeof(buf));
        err = cgc_read_until(STDIN, buf, sizeof(buf), '\n');
        if (buf[0] == 0)
            break;

        if (buf[0] >= '0' && buf[0] <= '9') {
            current_id = buf[0] - '0';
        } else {
            cgc_printf(STDOUT, "Invalid function! %u\n", buf[0]);
            cgc_exit(3);
        }

        if (services[current_id].configured) {
            cgc_printf(STDOUT, "this function is already included in the pipeline!\n");
            cgc_exit(4);
        }

        services[current_id].configured = 1;
        services[current_id].order = i;
    }
    return i;
}

/* handle sending the output ports to each of the executables */
void cgc_setup_output(int enabled_count) {
    int i;
    for (i = 0; i < enabled_count; i++) {
        int current_service = cgc_get_service_by_position(i);
        int next_service = cgc_get_service_by_position(i + 1);
        int input_fd = STDIN;
        int output_fd = STDOUT;

        if (current_service == -1)
            cgc__terminate(5);

        if (next_service >= 0) {
            output_fd = services[next_service].read_fd - 1;
        }
           
        if (i > 0) {
            input_fd = services[current_service].read_fd;
        }

        cgc_send_service_fd(current_service, input_fd, output_fd);
    }
}

void cgc_terminate_unused(int service_count) {
    int i;
    /* cause the servicse that are not to be setup to cgc_exit */
    for (i = 0; i < service_count; i++) {
        if (services[i].configured == 0) {
            cgc_terminate_service(i);
        }
    }
}

int main(int cgc_argc, char *cgc_argv[]) {
    int service_count;
    int enabled_count;

    cgc_setup();
    cgc_printf(STDOUT, "Function pipelines made easy!\n");
    service_count = cgc_print_available();
    enabled_count = cgc_enable_services(service_count);

    if (enabled_count == 0) {
        cgc_printf(STDOUT, "no functions configured.\n");
        cgc_exit(5);
    }

    cgc_terminate_unused(service_count);
    cgc_print_pipeline(enabled_count);
    cgc_handle_configs(enabled_count);
    cgc_setup_output(enabled_count);

    return 1;
}
