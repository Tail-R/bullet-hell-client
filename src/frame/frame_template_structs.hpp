#pragma once

#include <vector>
#include <cstdint>

/*
    Packet header (8bytes)
*/
struct PacketHeader {
    uint32_t magic_number;
    uint32_t body_size;
};

static_assert(sizeof(PacketHeader) == 8);

/*
    Position (8bytes)
*/
struct Position {
    float x;
    float y;
};

static_assert(sizeof(Position) == 8);

/*
    Velocity (8bytes)
*/
struct Velocity {
    float x;
    float y;
};

static_assert(sizeof(Velocity) == 8);

/*
    Stage object (8bytes)
*/
struct Stage {
    uint8_t     id;
    uint8_t     name;
    uint8_t     state;
    uint8_t     next_stage;

    uint32_t    timestamp;
};

constexpr size_t STAGE_OBJECT_SIZE = 8;
static_assert(sizeof(Stage) == STAGE_OBJECT_SIZE);

/*
    Player object (32bytes)
*/
struct Player {
    uint8_t     id;
    uint8_t     name;
    uint8_t     state;
    uint8_t     attack_pattern;

    Position    pos;
    Velocity    vel;
    float       radius;
    float       angle;

    uint8_t     current_spell;
    uint8_t     lives;
    uint8_t     bombs;
    uint8_t     power;
};

constexpr size_t PLAYER_OBJECT_SIZE = 32;
static_assert(sizeof(Player) == PLAYER_OBJECT_SIZE);

/*
    Enemy object (32bytes)
*/
struct Enemy {
    uint8_t     id;
    uint8_t     name;
    uint8_t     state;
    uint8_t     attack_pattern;
    
    Position    pos;
    Velocity    vel;
    float       radius;
    float       angle;
    uint32_t    health;
};

constexpr size_t ENEMY_OBJECT_SIZE = 32;
static_assert(sizeof(Enemy) == ENEMY_OBJECT_SIZE);

/*
    Boss object (36bytes)
*/
struct Boss {
    uint8_t     id;
    uint8_t     name;
    uint8_t     state;
    uint8_t     attack_pattern;

    Position    pos;
    Velocity    vel;
    float       radius;
    float       angle;
    uint32_t    health;

    uint8_t     current_spell;
    uint8_t     phase;
    uint8_t     reserved_01;    // Reserved area
    uint8_t     reserved_02;    // Reserved area
};

constexpr size_t BOSS_OBJECT_SIZE = 36;
static_assert(sizeof(Boss) == BOSS_OBJECT_SIZE);

/*
    Bullet object (32bytes)
*/
struct Bullet {
    uint32_t    id;
    Position    pos;
    Velocity    vel;
    float       radius;
    float       angle;
    uint32_t    damage;

    uint8_t     name;
    uint8_t     state;
    uint8_t     flight_pattern;
    uint8_t     owner;
};

constexpr size_t BULLET_OBJECT_SIZE = 36;
static_assert(sizeof(Bullet) == BULLET_OBJECT_SIZE);

/*
    Item object (32bytes)
*/
struct Item {
    uint8_t     id;
    uint8_t     name;
    uint8_t     state;
    uint8_t     flight_pattern;

    Position    pos;
    Velocity    vel;
    float       radius;
    float       angle;
    float       score;
};

constexpr size_t ITEM_OBJECT_SIZE = 32;
static_assert(sizeof(Item) == ITEM_OBJECT_SIZE);

/*
    Frame object
*/
struct Frame {
    uint8_t     client_id;
    uint8_t     opponent_id;
    uint8_t     mode;
    uint8_t     state;

    uint32_t    timestamp;
    uint32_t    score;

    uint8_t     difficulty;
    uint8_t     reserved_01;    // Reserved area
    uint8_t     reserved_02;    // Reserved area
    uint8_t     reserved_03;    // Reserved area

    /***** 16 bytes total *****/

    // Stage object         [8bytes]
    Stage                   stage;

    // Player objects       [32bytes * n]
    uint32_t                player_count;
    std::vector<Player>     player_vector;

    // Enemy objects        [32bytes * n]
    uint32_t                enemy_count;
    std::vector<Enemy>      enemy_vector;

    // Boss objects         [36bytes * n]
    uint32_t                boss_count;
    std::vector<Boss>       boss_vector;

    // Bullet objects       [32bytes * n]
    uint32_t                bullet_count;
    std::vector<Bullet>     bullet_vector;

    // Item objects         [32bytes * n]
    uint32_t                item_count;
    std::vector<Item>       item_vector;
};

constexpr size_t FRAME_OBJECT_FIXED_HEADER_SIZE = 16;