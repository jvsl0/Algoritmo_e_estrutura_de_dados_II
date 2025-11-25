#include "spellbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Spellbook* create_spellbook() {
    Spellbook* book = (Spellbook*)malloc(sizeof(Spellbook));
    if (book == NULL) {
        printf("Erro de alocacao de memoria para o grimorio.\n");
        exit(EXIT_FAILURE);
    }
    book->head = NULL;
    return book;
}


void add_spell(Spellbook* book, int id, const char* name, int mana_cost) {
    if (book == NULL) return;

    
    SpellNode* newNode = (SpellNode*)malloc(sizeof(SpellNode));
    if (newNode == NULL) {
        printf("Erro de alocacao de memoria para o feitico.\n");
        return;
    }

    
    newNode->data.id = id;
    strncpy(newNode->data.name, name, 49);
    newNode->data.name[49] = '\0'; 
    newNode->data.mana_cost = mana_cost;
    newNode->next = NULL;


    if (book->head == NULL) {
        book->head = newNode;
    } else {
        SpellNode* current = book->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Feitico '%s' adicionado ao grimorio.\n", name);
}


void display_spellbook(Spellbook* book) {
    if (book == NULL || book->head == NULL) {
        printf("\nO grimorio esta vazio.\n");
        return;
    }

    printf("\n--- GRIMORIO ATUAL ---\n");
    SpellNode* current = book->head;
    while (current != NULL) {
        printf("ID: %d, Feitico: %s, Custo de Mana: %d\n",
               current->data.id, 
               current->data.name, 
               current->data.mana_cost);
        current = current->next;
    }
    printf("------------------------\n");
}


void destroy_spellbook(Spellbook* book) {
    if (book == NULL) return;

    SpellNode* current = book->head;
    SpellNode* next;
    
    // Libera os nos da lista
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    
    free(book);
    printf("\nGrimorio destruido e memoria liberada com sucesso.\n");
}