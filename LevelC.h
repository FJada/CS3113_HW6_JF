/**
* Author: JADA FORRESTER]
* Assignment: FINAL
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Scene.h"

class LevelC : public Scene {
public:
    int ENEMY_COUNT = 1;
    int PLAYER_MAX_BULLETS = 5;
    
    
    
    ~LevelC();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};


