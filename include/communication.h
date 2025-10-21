/**
 * @file communication.h
 * @brief Interface du module de communication.
 *
 * ## Utilisation simple :
 *
 * 1. **Initialiser le contexte de communication**
 *    Avant toute réception, créer un objet `CommunicationContext_t`
 *    puis appeler `Communication_Init()` pour le réinitialiser.
 *
 *    @code
 *    CommunicationContext_t context;
 *    Communication_Init(&context);
 *    @endcode
 *
 * 2. **Réception des caractères**
 *    À chaque caractère reçu (ex. depuis un port série ou le clavier),
 *    appeler `Communication_ReceiveChar()`.  
 *    Lorsqu’un caractère de fin de ligne ('\n') est reçu,
 *    le message complet est automatiquement décodé.
 *
 *    @code
 *    const char *msg = "FORWARD\n";
 *    for (size_t i = 0; msg[i] != '\0'; i++)
 *    {
 *        Communication_ReceiveChar(&context, msg[i]);
 *    }
 *    @endcode
 *
 * Le module se charge ensuite de :
 *  - décoder la commande reçue ;
 *  - envoyer un accusé de réception (ACK) ou un message d’erreur ;
 *  - réinitialiser automatiquement le contexte pour la prochaine trame.
 */



#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/* Taille maximale du buffer de réception */
#define BUFFER_SIZE 128U
#define DEBUG_PRINTF 
#define FORWARD_DEFAULT 10
#define TURN_DEFAULT 10

#include <stdint.h>   /* pour uint8_t, uint16_t, etc. */
#include <stddef.h>   /* pour size_t */

/* États de la machine à états */
typedef enum
{
    STATE_IDLE = 0,
    STATE_RECEIVING
} CommunicationState_t;

/* Structure de communication */
typedef struct
{
    CommunicationState_t state;
    char buffer[BUFFER_SIZE];
    uint8_t index;
} CommunicationContext_t;

typedef struct
{
    char mode[BUFFER_SIZE];
    float value;
} Order_t;

/* Fonctions publiques */
void Communication_Init(CommunicationContext_t *context);
Order_t Communication_ReceiveChar(CommunicationContext_t *context, char caractere);
Order_t Communication_DecodeMessage(const char *message);
void Communication_SendACK(void);
void Communication_SendError(const char *error_msg);

#endif /* COMMUNICATION_H */
