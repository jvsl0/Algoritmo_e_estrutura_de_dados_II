#ifndef SPELLBOOK_H
#define SPELLBOOK_H


typedef struct {
    int id;
    char name[50];
    int mana_cost;
} Spell;


typedef struct SpellNode {
    Spell data;
    struct SpellNode* next;
} SpellNode;


typedef struct {
    SpellNode* head;
} Spellbook;


Spellbook* create_spellbook();
void add_spell(Spellbook* book, int id, const char* name, int mana_cost);
void display_spellbook(Spellbook* book);
void destroy_spellbook(Spellbook* book);

#endif