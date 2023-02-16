#include <stdio.h>
#include "queue.h"


int queue_size (queue_t *queue)
{
    int num = 1;
    queue_t *nextQueue;
    
    if (queue == NULL)
        return 0;
        
    nextQueue = queue->next;

    while(nextQueue != queue)
    {
        nextQueue = nextQueue->next;
        num++;
    }

    return num;
}


void queue_print (char *name, queue_t *queue, void print_elem (void*) )
{
    queue_t *element;
    element = queue;

    printf("%s: [", name);
    if (queue != NULL)
    {
        for (;;)
        {
            print_elem(element);
            printf(" ");
            element = element->next;
            if (element == queue->prev)
                break;
        }
    } 
    printf("]\n");
}


int queue_append (queue_t **queue, queue_t *elem)
{
    //checa se fila e elemento existem
    //checa se elemento não está em outra fila
    if (queue == NULL || elem == NULL || 
        elem->prev != NULL || elem->next != NULL)
        return -1;

    //caso fila esteja vazia
    if (*queue == NULL) 
    {
        *queue = elem;
        elem->prev = elem;
        elem->next = elem;
    }
    else
    {
        //guarda ponteiro do último elemento da fila
        queue_t *lastElement = (*queue)->prev;

        (*queue)->prev = elem;
        lastElement->next = elem;

        elem->prev = lastElement;
        elem->next = *queue;
    }

    return 0;
} 

int queue_remove (queue_t **queue, queue_t *elem)
{
    //checa se fila e elemento existem
    //checa se fila não está vazia
    if (queue == NULL || elem == NULL || elem->prev == NULL || elem->next == NULL ||
        (*queue)->prev == NULL || (*queue)->next == NULL)
        return -1;

    queue_t *elementIterated;
    elementIterated = *queue;

    for (;;)
    {
        if (elementIterated == elem)
        {
            //caso não seja o único elemento da fila
            if (elementIterated != elementIterated->next)
            {
                elementIterated->prev->next = elementIterated->next;
                elementIterated->next->prev = elementIterated->prev;
            }
            else
                *queue = NULL;

            //caso seja o primeiro elemento da fila
            if (elementIterated == *queue)
                *queue = elementIterated->next;
            
            elementIterated->prev = NULL;
            elementIterated->next = NULL;

            break;
        }
        if (elementIterated->next == *queue)
            return -1;
        elementIterated = elementIterated->next;
    }
            
    return 0;
}

