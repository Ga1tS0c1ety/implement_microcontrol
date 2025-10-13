#include "../include/communication.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Initialisation du contexte */
void Communication_Init(CommunicationContext_t *context)
{
    if (context != NULL)
    {
        context->state = STATE_IDLE;
        context->index = 0U;
        (void)memset(context->buffer, 0, sizeof(context->buffer));
    }
}

/* Fonction appelée à chaque caractère reçu */
void Communication_ReceiveChar(CommunicationContext_t *context, char caractere)
{
    if (context == NULL)
    {
        return;
    }

    switch (context->state)
    {
        case STATE_IDLE:
        {
            /* Tout message débute par une lettre (commande ASCII) */
            if ((caractere >= 'A') && (caractere <= 'Z'))
            {
                context->index = 0U;
                context->buffer[context->index++] = caractere;
                context->state = STATE_RECEIVING;
            }
            break;
        }

        case STATE_RECEIVING:
        {
            if (caractere == '\n')
            {
                context->buffer[context->index] = '\0'; /* Fin de trame */
                Communication_DecodeMessage(context->buffer);
                context->state = STATE_IDLE;
                context->index = 0U;
            }
            else
            {
                if (context->index < (BUFFER_SIZE - 1U))
                {
                    context->buffer[context->index++] = caractere;
                }
                else
                {
                    Communication_SendError("Overflow");
                    context->state = STATE_IDLE;
                    context->index = 0U;
                }
            }
            break;
        }

        default:
        {
            /* État inconnu — réinitialisation */
            context->state = STATE_IDLE;
            context->index = 0U;
            break;
        }
    }
}

/* Fonction utilitaire */
static int string_starts_with(const char *str, const char *prefix)
{
    size_t i = 0U;
    if ((str == NULL) || (prefix == NULL))
    {
        return 0;
    }

    while (prefix[i] != '\0')
    {
        if (str[i] != prefix[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

/* Décodage d'une trame complète simple */
void Communication_DecodeMessage(const char *message)
{
    if (message == NULL)
    {
        Communication_SendError("Null message");
        return;
    }

    /* Commandes avec paramètres */
    if (string_starts_with(message, "FORWARD "))
    {
        printf("Commande FORWARD avec paramètre : %s\n", message + 8);
        Communication_SendACK();
    }
    else if (string_starts_with(message, "TURN "))
    {
        printf("Commande TURN avec paramètre : %s\n", message + 5);
        Communication_SendACK();
    }
    /* Commandes simples */
    else if (string_starts_with(message, "FORWARD"))
    {
        printf("Commande FORWARD simple\n");
        Communication_SendACK();
    }
    else if (string_starts_with(message, "STOP"))
    {
        printf("Commande STOP\n");
        Communication_SendACK();
    }
    else if (string_starts_with(message, "TURN"))
    {
        printf("Commande TURN simple\n");
        Communication_SendACK();
    }
    /* Affectation de paramètres */
    else if (string_starts_with(message, "SPEED="))
    {
        printf("Affectation vitesse linéaire : %s\n", message + 6);
        Communication_SendACK();
    }
    else if (string_starts_with(message, "ANGLE_SPEED="))
    {
        printf("Affectation vitesse angulaire : %s\n", message + 12);
        Communication_SendACK();
    }
    else if (strchr(message, '=') != NULL)
    {
        printf("Affectation de paramètre : %s\n", message);
        Communication_SendACK();
    }
    else
    {
        Communication_SendError("Commande inconnue");
    }
}



/* Envoi d’un ACK */
void Communication_SendACK(void)
{
    printf("ACK\n");
}

/* Envoi d’un message d’erreur */
void Communication_SendError(const char *error_msg)
{
    if (error_msg != NULL)
    {
        printf("ERR: %s\n", error_msg);
    }
}
