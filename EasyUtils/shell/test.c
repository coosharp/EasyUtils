#include <stdio.h>
#include <string.h>
#include "u_shell.h"

static int g_exit_requested = 0;

static void shell_print(const char * str)
{
        fputs(str, stdout);
        fflush(stdout);
}

static int cmd_hello(int argc, char ** argv)
{
        (void)argc;
        (void)argv;
        printf("hello from cmd_hello\n");
        return 0;
}

static int cmd_echo(int argc, char ** argv)
{
        for (int i = 1; i < argc; i++) {
                printf("%s%s", argv[i], (i + 1 < argc) ? " " : "\n");
        }
        return 0;
}

static int cmd_quit(int argc, char ** argv)
{
        (void)argc;
        (void)argv;
        g_exit_requested = 1;
        printf("bye\n");
        return 0;
}

int main(void)
{
        static const struct u_shell_cmd cmd_list[] = 
        {
                { cmd_hello, "hello", "print hello" },
                { cmd_echo,  "echo",  "print arguments" },
                { cmd_quit,  "quit",  "exit shell" }
        };
        char line[U_SHELL_MAX_CMD_LEN];

        u_shell_init(cmd_list, sizeof(cmd_list) / sizeof(cmd_list[0]), shell_print);

        while (!g_exit_requested) {
                if (fgets(line, sizeof(line), stdin) == NULL) {
                        break;
                }

                u_shell_loop(line, strlen(line));
        }

        return 0;
}
