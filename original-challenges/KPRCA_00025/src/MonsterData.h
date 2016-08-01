#ifndef MONSTER_DATA_H
#define MONSTER_DATA_H

#define NUM_BUILTIN_KINDS 3

#define TYPE_EARTH  0x01
#define TYPE_WIND   0x02
#define TYPE_FIRE   0x04

// given as percent
#define LEVEL_HEALTH_MULTIPLIER 800
#define LEVEL_ATTACK_MULTIPLIER 100
#define LEVEL_DEFENSE_MULTIPLIER 100

#define MAX_LEVEL 99

typedef struct {
    const char *name;
    unsigned int power;
} attack_data_t;

typedef struct {
    unsigned char id;
    unsigned char type;
    const char *name;
    unsigned int max_health;
    unsigned int attack;
    unsigned int defense;
    unsigned int num_attacks;
    attack_data_t attacks[4];
} kind_data_t;

extern const kind_data_t builtin_kinds[NUM_BUILTIN_KINDS];

// as a percentage: 100 = 1.00x, 50 = 0.50x
unsigned int attack_multiplier(const kind_data_t *attacker, const kind_data_t *defender);

#endif
