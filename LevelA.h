#include "Scene.h"

class LevelA : public Scene {
public:
    int ENEMY_COUNT = 4;
    int PLAYER_MAX_BULLETS = 5;
    int dead = 0;
    
    
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
