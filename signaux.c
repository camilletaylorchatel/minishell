#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum) 
{
    (void)signum;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("",0);
    rl_redisplay();
}

void setup_signal_handlers() 
{
    struct sigaction sa_int, sa_quit;

    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART; 
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = SA_RESTART;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int main() 
{
    setup_signal_handlers();

    while (1) 
    {
        char *input = readline("minishell$ ");
        if (input == NULL) 
        {
            printf("exit\n");
            break;
        }

        if (*input) 
            add_history(input);

        free(input);
    }
    return 0;
}
