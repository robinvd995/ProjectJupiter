#pragma once

#include "Core.h"

namespace Jupiter {

	enum class EnumInputDevice {
		KEYBOARD = 0,
		MOUSE = 1,

		COUNT
	};

	class KeyState {

	public:
		KeyState();
		~KeyState();

		const bool isKeyDown() const;
		const bool isKeyPressed() const;
		const bool isKeyReleased() const;

	private:
		bool m_IsKeyDown;
		bool m_WasKeyDown;

		friend class KeyStateRegistry;
		friend class InputManager;
	};

	class KeyStateRegistry {

	public:
		KeyStateRegistry();
		KeyStateRegistry(const KeyStateRegistry&) = delete;
		~KeyStateRegistry();

		KeyState* getKeyState(s_uint keycode);

		void allocateRegistry(s_uint size);
		void freeRegistry();

		void addTrackedKeys(std::initializer_list<s_uint> keycodes);

		void updateKeyStates();

	private:
		s_uint m_RegistrySize;
		std::vector<KeyState> m_Registry;
		std::vector<s_uint> m_TrackedStates;

		friend class InputManager;
	};

	class InputManager {

	public:

		static bool isKeyDown(EnumInputDevice input_device, s_uint keycode);
		static bool isKeyPressed(EnumInputDevice input_device, s_uint keycode);
		static bool isKeyReleased(EnumInputDevice input_device, s_uint keycode);

	private:
		InputManager();
		~InputManager();

		static void updateInputs(std::initializer_list<EnumInputDevice> input_devices);
		static void onKeyStateChanged(EnumInputDevice input_device, s_uint keycode, bool down);

		static InputManager* s_Instance;
	private:
		KeyStateRegistry m_KeyStateRegistries[(uint)EnumInputDevice::COUNT];

#ifdef JPT_PLATFORM_WINDOWS
		friend class WindowsWindow;
#endif // JPT_PLATFORM_WINDOWS
	};
}
