#pragma once

#include "JupiterEngine/JupiterEngine.h"

namespace Jupiter {

	/// <summary>
	/// The type of HID used to give input
	/// </summary>
	enum class EnumInputDevice {
		KEYBOARD = 0,
		MOUSE = 1,

		COUNT
	};

	/// <summary>
	/// The current state of a given key
	/// </summary>
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

	/// <summary>
	/// A general purpose registry used to map and track keys which need to be updated every frame
	/// </summary>
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

	/// <summary>
	/// Input manager
	/// </summary>
	class InputManager {

	public:
		/// <summary>
		/// Checks if the key is currently held down or not
		/// </summary>
		/// <param name="input_device">The type of input device that need to be checked</param>
		/// <param name="keycode">The keycode of the key</param>
		static bool isKeyDown(EnumInputDevice input_device, s_uint keycode);

		/// <summary>
		/// Checks if the key has been pressed in the current frame (only works when the key is beeing tracked)
		/// </summary>
		/// <param name="input_device">The type of input device that need to be checked</param>
		/// <param name="keycode">The keycode of the key</param>
		static bool isKeyPressed(EnumInputDevice input_device, s_uint keycode);

		/// <summary>
		/// Checks if the key has been released in the current frame (only works when the key is beeing tracked)
		/// </summary>
		/// <param name="input_device">The type of input device that need to be checked</param>
		/// <param name="keycode">The keycode of the key</param>
		static bool isKeyReleased(EnumInputDevice input_device, s_uint keycode);

	private:
		InputManager();
		~InputManager();

		/// <summary>
		/// Updates all the keys that are tracked for the given input devices
		/// </summary>
		/// <param name="input_devices">the input devices that are currently in use and in need of updating</param>
		static void updateInputs(std::initializer_list<EnumInputDevice> input_devices);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="input_devices"></param>
		/// <param name="keycode"></param>
		/// <param name="down"></param>
		static void onKeyStateChanged(EnumInputDevice input_device, s_uint keycode, bool down);

		static InputManager* s_Instance;
	private:
		KeyStateRegistry m_KeyStateRegistries[(uint)EnumInputDevice::COUNT];

#ifdef JPT_PLATFORM_WINDOWS
		friend class WindowsWindow;
#endif // JPT_PLATFORM_WINDOWS
	};
}
