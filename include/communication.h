#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/* Taille maximale du buffer de réception */
#define BUFFER_SIZE 128U

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

/* Fonctions publiques */
void Communication_Init(CommunicationContext_t *context);
void Communication_ReceiveChar(CommunicationContext_t *context, char caractere);
void Communication_DecodeMessage(const char *message);
void Communication_SendACK(void);
void Communication_SendError(const char *error_msg);

#endif /* COMMUNICATION_H */
