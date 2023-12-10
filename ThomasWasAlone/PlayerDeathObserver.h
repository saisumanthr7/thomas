// PlayerDeathObserver.h
#include "Observer.h"
#include "HUD.h"

class PlayerDeathObserver : public Observer {
private:
    Hud& hud;

public:
    PlayerDeathObserver(Hud& hud) : hud(hud) {}

    void onNotify(EventType event) override {
        if (event == EventType::PlayerDeath) {
           // hud.updatePlayerDeath();
        }
    }
};
