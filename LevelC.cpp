
#include "LevelC.h"
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
#define LEVEL_WIDTH 18
#define LEVEL_HEIGHT 9

unsigned int LEVELC_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1
};

LevelC::~LevelC()
{
    delete [] m_state.enemies;
    delete [] m_state.bullets;
    delete    m_state.player;
    delete    m_state.token;
    delete    m_state.map;
    Mix_FreeMusic(m_state.bgm);
}

void LevelC::initialise()
{
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/Untitled4.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 4, 1);
    
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.0f, -5.0f, 0.0f));
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
    
    //token
    m_state.token = new Entity();
    m_state.token->set_entity_type(TOKEN);
    GLuint token_texture_id = Utility::load_texture("assets/cheese.png");
    m_state.token->m_texture_id = token_texture_id;
    m_state.token->set_position(glm::vec3(16.0f, -4.0f, 0.0f));
    
    //bullets
    GLuint bullet_texture_id = Utility::load_texture("assets/nerf bullet.png");
    m_state.bullets = new Entity[PLAYER_MAX_BULLETS];
    for(int i =0; i< PLAYER_MAX_BULLETS; i++){
        m_state.bullets[i].set_entity_type(BULLET);
        m_state.bullets[i].set_active_status(false);
        m_state.bullets[i].set_speed(2.0f);
        m_state.bullets[i].m_texture_id = bullet_texture_id;
    
    }
  
    /**
     Enemies' stuff */
    GLuint enemy_texture_id_1 = Utility::load_texture("assets/cop.png");

    
    m_state.enemies = new Entity[ENEMY_COUNT];
    //boss
    
    for(int i = 0; i < ENEMY_COUNT; i++){
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(GUARD);
        m_state.enemies[i].set_ai_state(IDLE);
        m_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_state.enemies[i].set_speed(.50f);
        m_state.enemies[i].set_width(.50f);
        m_state.enemies[i].set_height(.50f);
        m_state.enemies[i].m_texture_id = enemy_texture_id_1;
    }

    m_state.enemies[0].set_position(glm::vec3(8.0f, -5.0f, 0.0f));
    
    //m_state.enemies[1].set_position(glm::vec3(15.0f, -6.6f, 0.0f));

   

    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("assets/Ice Spice - Deli (INSTRUMENTAL) (Best Version).mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(5.0f);
    m_state.died_sfx = Mix_LoadWAV("assets/crash-7075.wav");
}



void LevelC::update(float delta_time){
    //main game functionality
    
    for(int i =0; i < PLAYER_MAX_BULLETS; i++){

        for(int j = 0; j < ENEMY_COUNT; j++){

            m_state.player->check_collision_y(&m_state.enemies[j], 1);
            m_state.player->check_collision_x(&m_state.enemies[j], 1);
            

            
            m_state.bullets[i].update(delta_time,m_state.player, m_state.bullets, PLAYER_MAX_BULLETS, m_state.map);
            m_state.enemies[j].update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
            
            
            m_state.bullets[i].check_collision_y(&m_state.enemies[j], 1);
            m_state.bullets[i].check_collision_x(&m_state.enemies[j], 1);
            
            m_state.enemies[j].check_collision_y(&m_state.bullets[i], 1);
            m_state.enemies[j].check_collision_x(&m_state.bullets[i], 1);
            
            m_state.bullets[i].check_collision_x(m_state.map);
            m_state.bullets[i].check_collision_y(m_state.map);
            
            //c if bullet dotn hit anything disappear after 3 spaces
            if(glm::length(m_state.bullets[i].get_position().x - m_state.player->get_position().x) >= 5.0f){
                m_state.bullets[i].deactivate();
            }
            
            //check if bullets hit enemy
            if(m_state.bullets[i].m_collided_entity_right){
                m_state.enemies[j].Entity::deactivate();
                m_state.enemy_damage = true;
                m_state.bullets[i].deactivate();
            
                
            }
            //hits map
            if(m_state.bullets[i].m_collided_entity_right && m_state.bullets[i].m_collided_right){
                m_state.bullets[i].deactivate();
                
            }
            
            if(m_state.player->m_collided_entity_top){
                m_state.damage = true;
                //m_state.player->deactivate();
            }
            
            if(m_state.player->m_collided_entity_left){
                m_state.damage = true;
                //m_state.player->deactivate();
            }
            
            if(m_state.player->m_collided_entity_right){
                m_state.damage = true;
                //m_state.player->deactivate();
            }
            
            if(m_state.player->m_collided_entity_bottom){
                m_state.damage = true;
                //m_state.player->deactivate();
            }
            
        }
        m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
        
    }
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    m_state.token->activate();
    m_state.token->update(delta_time, m_state.player, m_state.token, ENEMY_COUNT, m_state.map);

    if(m_state.player->get_position().y >= -4.0f && m_state.player->get_position().x >= 16.0f){
            m_state.next_scene_id++;
    }
    
}




void LevelC::render(ShaderProgram *program)
{
    m_state.map->render(program);
    if(m_state.player->get_active_status())  m_state.player->render(program);
    if(m_state.token->get_active_status())  m_state.token->render(program);
    for(int i =0; i< PLAYER_MAX_BULLETS; i++){
        if(m_state.bullets[i].get_active_status())  m_state.bullets[i].render(program);
    }
  
    for(int i =0; i < ENEMY_COUNT; i++)  if(m_state.enemies[i].get_active_status()) m_state.enemies[i].render(program);
    
}
