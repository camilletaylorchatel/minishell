#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Gestionnaire pour SIGINT (Ctrl+C)
void sigint_handler(int signum) {
    (void)signum;
    // Imprimer une nouvelle ligne
    printf("\n");
    // Indiquer à readline que nous sommes sur une nouvelle ligne
    rl_on_new_line();
    // Redisplay le prompt
    rl_redisplay();
}

// Gestionnaire pour SIGQUIT (Ctrl+\)
void sigquit_handler(int signum) {
    ;
    //(void)signum;
    // Ne rien faire
}

// fct gestionnaires de signaux
void setup_signal_handlers() {
    struct sigaction sa_int, sa_quit;

    // Configurer SIGINT (Ctrl+C)
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART; // Redémarrer les appels interrompus
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    // Configurer SIGQUIT (Ctrl+\)
    sa_quit.sa_handler = sigquit_handler;
    sa_quit.sa_flags = SA_RESTART;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int main() {
    // Call fct
    setup_signal_handlers();

    while (1) {
        // Lire la commande utilisateur avec readline
        char *input = readline("minishell$ ");
        if (input == NULL) {
            // Si readline retourne NULL, cela signifie que EOF a été atteint (Ctrl+D)
            break;
        }

        // Si l'utilisateur a tapé une commande, l'ajouter à l'historique
        if (*input) {
            add_history(input);
            //reste du code
        }

        free(input);
    }

    return 0;
}
