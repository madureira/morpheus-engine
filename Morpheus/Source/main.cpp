#include "Core/Window/Window.h"
#include "Core/Event/Event.h"
#include "Core/Event/EventBus.h"

using namespace Morpheus;

class CollisionEvent : public Event {
private:
	std::string& m_Text;

public:
	CollisionEvent(std::string& message) : m_Text(message) {
	}

	~CollisionEvent()
	{
	}

	std::string& GetText() const
	{
		return this->m_Text;
	}
};

class CombatSystem {
private:
	EventBus* m_EventBus;

public:
	CombatSystem(EventBus* eventBus) {
		this->m_EventBus = eventBus;
	}

	void init() {
		this->m_EventBus->subscribe(this, &CombatSystem::onCollisionEvent);
	}

	void onCollisionEvent(CollisionEvent* collision) {
		std::cout << "Event -> " << collision->GetText() << std::endl;
	}
};

int main()
{
	Window window("Test", 1024, 768, true);

	EventBus eventBus;
	CombatSystem combatSystem(&eventBus);
	combatSystem.init();

	while (window.IsOpen())
	{
		window.OnFrameStart();

		std::string msg = "TEST";
		CollisionEvent collision(msg);
		eventBus.publish(&collision);

		window.OnFrameEnd();
	}

	return 0;
}
