// LevelCompletionObserver.h
#include "Observer.h"
#include "HUD.h"

class LevelCompletionObserver : public Observer {
private:
    Hud& hud;

public:
    LevelCompletionObserver(Hud& hud) : hud(hud) {}

    void onNotify(EventType event) override {
        if (event == EventType::LevelComplete) {
           // hud.updateLevelCompletion();
        }
    }
};
