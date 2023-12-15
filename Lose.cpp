#include "Lose.h"
#include "Utility.h"



#define LEVEL_WIDTH 17
#define LEVEL_HEIGHT 8

unsigned int LOSE_DATA[] =
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

Lose::~Lose()
{
    delete [] m_state.enemies;
    delete [] m_state.bullets;
    delete    m_state.player;
    delete    m_state.token;
    delete    m_state.map;
    Mix_FreeMusic(m_state.bgm);
}

void Lose::initialise()
{

    
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/Untitled4.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LOSE_DATA, map_texture_id, 1.0f, 4, 1);

    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->m_texture_id = Utility::load_texture("assets/Girl updated sprites .png");
    m_state.player->set_position(glm::vec3(-10.0f, 0.0f, 0.0f));
    m_state.player->deactivate();
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/BUSY TRAFFIC NOISES, CARN HORNS (SOUND EFFECTS) HD.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(5.0f);

}

void Lose::update(float delta_time)
{
    m_state.player->deactivate();
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
  

}

void Lose::render(ShaderProgram *program)
{
    //text rednering
    std::string lose_text = "YOU LOSE";
    GLuint font_texture_id_1 = Utility::load_texture("assets/font1.png");
    Utility::draw_text(program, font_texture_id_1, lose_text, .40f, 0.0f, glm::vec3(2.0f,-3.5f,0.0f));
    m_state.map->render(program);
    if(m_state.player->get_active_status())m_state.player->render(program);
}

