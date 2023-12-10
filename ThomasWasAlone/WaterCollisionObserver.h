#include "Observer.h"
#include "HUD.h"

// WaterCollisionObserver is a concrete observer class that responds to water collision events.
class WaterCollisionObserver : public Observer {
private:
    // Reference to the HUD object. This observer will update the HUD when notified.
    Hud& hud;

public:
    // Constructor initializes the observer with a reference to the HUD.
    WaterCollisionObserver(Hud& hud) : hud(hud) {}

    // onNotify is called when the subject notifies this observer of an event.
    void onNotify(EventType event) override {
        // Check if the event is a collision with water.
        if (event == EventType::CollisionWithWater) {
            hud.updateWaterCollision();
        }
    }
};
