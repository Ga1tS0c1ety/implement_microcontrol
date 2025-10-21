#include "../include/communication.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

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
Order_t Communication_ReceiveChar(CommunicationContext_t *context, char caractere)
{
    Order_t ordre;
    if (context == NULL)
    {
        Communication_SendError("Null context");
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
            if ((caractere == '\n') && (context->index < (BUFFER_SIZE - 1U)))
            {
                context->buffer[context->index] = '\0'; /* Fin de trame */
                ordre = Communication_DecodeMessage(context->buffer);
                context->state = STATE_IDLE;
                context->index = 0U;
                return ordre;
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

/* Fonction utilitaire */ //utilisation d'un garde fou
static bool string_starts_with(const char *str, const char *prefix)
{
    size_t i = 0U;
    if ((str == NULL) || (prefix == NULL))
    {
        return false;
    }

    while (prefix[i] != '\0')
    {
        if (str[i] != prefix[i])
        {
            return false;
        }
        i++;
    }
    return true;
}

/* Décodage d'une trame complète simple */
Order_t Communication_DecodeMessage(const char *message)
{
    Order_t ordre;
    char *endptr;
    if (message == NULL)
    {
        Communication_SendError("Null message");

    }

    /* Commandes avec paramètres */
    if (string_starts_with(message, "FORWARD "))
    {

        #ifdef DEBUG_PRINTF
        printf("Commande FORWARD avec paramètre : %s\n", message + 8);
        #endif
        
        snprintf(ordre.mode,BUFFER_SIZE, "FORWARD");
        

        ordre.value = strtof(message + 8, &endptr);  // pointe après "SPEED="
    
    // Vérification que toute la chaîne après '=' est un nombre valide
    if (*endptr != '\0') {
        Communication_SendError("Attention : caractères non numériques après le nombre.\n");
    }
    else{
        Communication_SendACK();
        return ordre;
    }

    }
    else if (string_starts_with(message, "TURN "))
    {
        #ifdef DEBUG_PRINTF
        printf("Commande TURN avec paramètre : %s\n", message + 5);
        #endif


        snprintf(ordre.mode,BUFFER_SIZE, "TURN");
        char *ptr = message + 4; // après "TURN"
        while (*ptr == ' ') ptr++; // saute les espaces
        ordre.value = strtof(ptr, &endptr);
        
        printf("test pour TURN_PARAM : %.2f, %s \n", ordre.value,ptr);
    // Vérification que toute la chaîne après '=' est un nombre valide
    if (*endptr != '\0') {
        Communication_SendError("Attention : caractères non numériques après le nombre.\n");
    }
    else{
        Communication_SendACK();
        return ordre;
    }

    }
    /* Commandes simples */
    else if (string_starts_with(message, "FORWARD"))
    {
        #ifdef DEBUG_PRINTF
        printf("Commande FORWARD simple\n");
        #endif

        snprintf(ordre.mode,BUFFER_SIZE, "FORWARD");
    

        ordre.value = FORWARD_DEFAULT;
    
    // Vérification que toute la chaîne après '=' est un nombre valide

        Communication_SendACK();
        return ordre;

    }
    else if (string_starts_with(message, "STOP"))
    {
        #ifdef DEBUG_PRINTF
        printf("Commande STOP\n");
        #endif

        snprintf(ordre.mode,BUFFER_SIZE, "STOP");
    

        
    
    // Vérification que toute la chaîne après '=' est un nombre valide
    
        Communication_SendACK();
        return ordre;        

    }
    else if (string_starts_with(message, "TURN"))
    {
        #ifdef DEBUG_PRINTF
        printf("Commande TURN simple\n");
        #endif
        
        snprintf(ordre.mode,BUFFER_SIZE, "TURN");
    

        ordre.value = TURN_DEFAULT;
    
    // Vérification que toute la chaîne après '=' est un nombre valide

        Communication_SendACK();
        return ordre;

    }
    /* Affectation de paramètres */
    else if (string_starts_with(message, "SPEED="))
    {
        #ifdef DEBUG_PRINTF
        printf("Affectation vitesse linéaire : %s\n", message + 6);
        #endif
        
        snprintf(ordre.mode,BUFFER_SIZE, "SPEED");
    

        ordre.value = strtof(message + 6, &endptr);  // pointe après "SPEED="
    
    // Vérification que toute la chaîne après '=' est un nombre valide
    if (*endptr != '\0') {
        Communication_SendError("Attention : caractères non numériques après le nombre.\n");
    }
    else{
        Communication_SendACK();
        return ordre;
    }


        
    }
    else if (string_starts_with(message, "ANGLE_SPEED="))
    {
        #ifdef DEBUG_PRINTF
        printf("Affectation vitesse angulaire : %s\n", message + 12);
        #endif

        snprintf(ordre.mode,BUFFER_SIZE, "ANGLE_SPEED");
    

        ordre.value = strtof(message + 12, &endptr);  // pointe après "SPEED="
    
    // Vérification que toute la chaîne après '=' est un nombre valide
    if (*endptr != '\0') {
        Communication_SendError("Attention : caractères non numériques après le nombre.\n");
    }
    else{
        Communication_SendACK();
        return ordre;
    }
        

    }
    else if (strchr(message, '=') != NULL)
    {
        #ifdef DEBUG_PRINTF
        printf("Affectation de paramètre : %s\n", message);
        #endif
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
        #ifdef DEBUG_PRINTF
        printf("ERR: %s\n", error_msg);
        #endif
    }
}




