#include "Scene.h"

class LevelB : public Scene {
public:
    int ENEMY_COUNT = 6;
    int PLAYER_MAX_BULLETS = 5;
    int dead = 0;
    
    
    ~LevelB();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};

