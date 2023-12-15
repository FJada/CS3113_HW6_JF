
#include "LevelX.h"
#include "Utility.h"

/**
* Author: JADA FORRESTER]
* Assignment: FINAL
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define LEVEL_WIDTH 17
#define LEVEL_HEIGHT 8

unsigned int LEVELX_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

LevelX::~LevelX()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    delete    m_state.token;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelX::initialise()
{

    
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/Untitled4.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELX_DATA, map_texture_id, 1.0f, 4, 1);

    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->m_texture_id = Utility::load_texture("assets/Girl updated sprites .png");
    m_state.player->set_position(glm::vec3(1.0f, -7.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(1.0f);
    m_state.player->m_texture_id = Utility::load_texture("assets/Girl updated sprites .png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[4] { 1, 5, 9,  13 };
    m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 3, 7, 11, 15 };
    m_state.player->m_walking[m_state.player->UP]    = new int[4] { 2, 6, 10, 14 };
    m_state.player->m_walking[m_state.player->DOWN]  = new int[4] { 0, 4, 8,  12 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 4;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(1.0f);
    m_state.player->set_width(1.0f);
    
    

    m_state.token = new Entity();
    m_state.token->set_entity_type(TOKEN);
    GLuint token_texture_id = Utility::load_texture("assets/bread.png");
    m_state.token->m_texture_id = token_texture_id;
    m_state.token->set_position(glm::vec3(5.0f, -7.0f, 0.0f));

    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/Ice Spice - Deli (INSTRUMENTAL) (Best Version).mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(5.0f);
}

void LevelX::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    m_state.token->update(delta_time, m_state.player, m_state.token, ENEMY_COUNT, m_state.map);
    
    if(m_state.player->get_position().y >= -7.0f && m_state.player->get_position().x >= 5.0f){
            m_state.next_scene_id++;
    }
   
}

void LevelX::render(ShaderProgram *program)
{
    m_state.map->render(program);
    if(m_state.token->get_active_status())  m_state.token->render(program);
    if(m_state.player->get_active_status())m_state.player->render(program);
}

