#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>


namespace viper {
	class InputSystem {
	public:


		enum class MouseButton {
			Left,
			Middle,
			Right
		};


		enum class Direction {
			Left,
			Right
		};


		InputSystem() = default;

		bool Initialize();

		void ShutDown();

		void Update();

		bool getKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		bool getPrevKeyDown(uint8_t key) const { return m_prevKeyboardState[key]; }
	
		bool getKeyPressed(uint8_t key) const { return !m_prevKeyboardState[key] && m_keyboardState[key]; }
		bool getKeyReleased(uint8_t key) const { return m_prevKeyboardState[key] && !m_keyboardState[key]; }

		const vec2& GetMousePosition() const { return m_mousePosition; }
		const vec2& GetPrevMousePosition() const { return m_prevMousePosition; }


		bool GetMouseButtonDown(MouseButton button) { return m_mouseButtonState[static_cast<size_t>(button)]; }
		bool GetPrevMouseButtonDown(MouseButton button) { return m_prevMouseButtonState[static_cast<size_t>(button)]; }
		bool GetMouseButtonPressed(MouseButton button) { return !m_prevMouseButtonState[static_cast<size_t>(button)] && m_mouseButtonState[static_cast<size_t>(button)]; }
		bool GetMouseButtonReleased(MouseButton button) { return m_prevMouseButtonState[static_cast<size_t>(button)] && !m_mouseButtonState[static_cast<size_t>(button)]; }


		

	public:






	private:
		std::vector<bool> m_keyboardState;
		std::vector<bool> m_prevKeyboardState;


		vec2 m_mousePosition{ 0, 0 };
		vec2 m_prevMousePosition{ 0, 0 };

		std::array<bool, 3> m_mouseButtonState{ false, false, false };
		std::array<bool, 3> m_prevMouseButtonState{ false, false, false };


	};




};
