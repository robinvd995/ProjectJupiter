#pragma once

namespace Jupiter {

	// DATA DRIVEN APPROACH
	// Reserve a buffer of a certain size for an event
	// What to do with listeners?

	// IDK about this one yet
	enum class EnumEventType {
		ENGINE_EVENT, // Events that have to do with core engine system, window resized, mouse clicked etc
		SCENE_EVENT // Events that occur during runtime and are called from the scene
	};

	enum class EnumEventCatergory {
		INPUT_EVENT,
		GAMEPLAY_EVENT
	};

	class Event {

	};

	class EventManager {

	};

}
