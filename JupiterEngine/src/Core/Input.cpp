#include "Core/Input.h"

namespace Jupiter {

	// ----- START KeyState -----

	KeyState::KeyState() : 
		m_IsKeyDown(false),
		m_WasKeyDown(false)
	{}

	KeyState::~KeyState() {}

	const bool KeyState::isKeyDown() const {
		return m_IsKeyDown;
	}

	const bool KeyState::isKeyPressed() const {
		return !m_WasKeyDown && m_IsKeyDown;
	}

	const bool KeyState::isKeyReleased() const {
		return m_WasKeyDown && !m_IsKeyDown;
	}

	// -----  END  KeyState -----


	// ----- START KeyStateRegistry -----

	KeyStateRegistry::KeyStateRegistry() :
		m_RegistrySize(0) 
	{}

	KeyStateRegistry::~KeyStateRegistry() {}

	KeyState* KeyStateRegistry::getKeyState(s_uint keycode) {
		return &m_Registry[keycode];
	}

	void KeyStateRegistry::allocateRegistry(s_uint size) {
		m_RegistrySize = size;
		m_Registry.resize(size);
	}

	void KeyStateRegistry::freeRegistry() {
		m_Registry.resize(0);
	}

	void KeyStateRegistry::addTrackedKeys(std::initializer_list<s_uint> keycodes) {
		m_TrackedStates.insert(m_TrackedStates.end(), keycodes);
	}

	void KeyStateRegistry::updateKeyStates() {
		for (s_uint keycode : m_TrackedStates) {
			m_Registry[keycode].m_WasKeyDown = m_Registry[keycode].m_IsKeyDown;
		}
	}

	// -----  END  KeyStateRegistry -----


	// ----- START InputManager -----

	InputManager* InputManager::s_Instance = nullptr;

	InputManager::InputManager() {
		m_KeyStateRegistries[(uint)EnumInputDevice::KEYBOARD].allocateRegistry(JPT_KEYBOARD_BUTTON_COUNT);
		m_KeyStateRegistries[(uint)EnumInputDevice::MOUSE].allocateRegistry(JPT_MOUSE_BUTTON_COUNT);
	}

	InputManager::~InputManager() {
		m_KeyStateRegistries[(uint)EnumInputDevice::KEYBOARD].freeRegistry();
		m_KeyStateRegistries[(uint)EnumInputDevice::MOUSE].freeRegistry();
	}

	bool InputManager::isKeyDown(EnumInputDevice input_device, s_uint keycode) {
		return s_Instance->m_KeyStateRegistries[(uint)input_device].getKeyState(keycode)->isKeyDown();
	}

	bool InputManager::isKeyPressed(EnumInputDevice input_device, s_uint keycode) {
		return s_Instance->m_KeyStateRegistries[(uint)input_device].getKeyState(keycode)->isKeyPressed();
	}

	bool InputManager::isKeyReleased(EnumInputDevice input_device, s_uint keycode) {
		return s_Instance->m_KeyStateRegistries[(uint)input_device].getKeyState(keycode)->isKeyReleased();
	}

	void InputManager::updateInputs(std::initializer_list<EnumInputDevice> input_devices) {
		for (EnumInputDevice e : input_devices) {
			s_Instance->m_KeyStateRegistries[(uint)e].updateKeyStates();
		}
	}

	void InputManager::onKeyStateChanged(EnumInputDevice input_device, s_uint keycode, bool down) {
		s_Instance->m_KeyStateRegistries[(uint)input_device].getKeyState(keycode)->m_IsKeyDown = down;
	}

	// -----  END  InputManager -----

}