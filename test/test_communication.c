#include "../include/communication.h"
#include <stdio.h>
#include <string.h>

#define HISTORY_SIZE 50

int main(void)
{
    CommunicationContext_t context;
    Communication_Init(&context);

    char c = '\0';
    char line[BUFFER_SIZE] = {0};
    size_t line_index = 0U;
    char history[HISTORY_SIZE][BUFFER_SIZE] = {{0}};
    size_t hist_index = 0U;

    printf("=== Test interactif Communication ===\n");
    printf("Tapez vos commandes (Enter pour valider, 'exit' pour quitter)\n");

    while (1)
    {
        printf("> ");
        line_index = 0U;
        (void)memset(line, 0, sizeof(line));

        /* Lecture d'une ligne complète */
        while (1)
        {
            c = (char)getchar();
            if (c == EOF)
            {
                return 0;
            }
            if ((c == '\n') || (c == '\r'))
            {
                break; /* fin de ligne */
            }
            if (line_index < (BUFFER_SIZE - 1U))
            {
                line[line_index++] = c;
            }
        }
        line[line_index] = '\0';

        /* Quitter si utilisateur tape exit */
        if (strcmp(line, "exit") == 0)
        {
            printf("Sortie du test interactif.\n");
            break;
        }

        /* Sauvegarde dans l'historique */
        if (hist_index < HISTORY_SIZE)
        {
            strncpy(history[hist_index], line, BUFFER_SIZE - 1U);
            history[hist_index][BUFFER_SIZE - 1U] = '\0';
            hist_index++;
        }

        /* Envoi caractère par caractère au module */
        for (size_t i = 0U; i < strlen(line); i++)
        {
            Communication_ReceiveChar(&context, line[i]);
        }
        /* Envoi du '\n' final pour déclencher la fin de trame */
        Communication_ReceiveChar(&context, '\n');

        printf("\n");
    }

    /* Affichage de l'historique */
    printf("=== Historique des commandes ===\n");
    for (size_t i = 0U; i < hist_index; i++)
    {
        printf("%zu: %s\n", i + 1U, history[i]);
    }

    return 0;
}
