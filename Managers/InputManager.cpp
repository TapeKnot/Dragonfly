#include "InputManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "../Events/EventKeyboard.h"
#include "../Events/EventMouse.h"
#include "LogManager.h"
#include "../Testing/Testing.h"

namespace df {

	InputManager::InputManager() {
		setType("InputManager");
	}

	// Get the singleton instance of the InputManager.
	InputManager& InputManager::getInstance() {
		static InputManager single;
		return single;
	}

	// Get window ready to capture input.
	// Return 0 if ok, else return -1.
	int InputManager::startUp() {
		if (!DM.isStarted()) return -1;

		sf::RenderWindow* p_window = DM.getWindow();

		p_window->setKeyRepeatEnabled(true);

		Manager::startUp();
		return 0;
	}

	// Revert back to normal window mode.
	void InputManager::shutDown() {
		sf::RenderWindow* p_window = DM.getWindow();

		p_window->setKeyRepeatEnabled(false);

		Manager::shutDown();
	}

	// Get input from the keyboard and mouse.
	// Pass event along to all Objects.
	void InputManager::getInput() const {
		sf::RenderWindow* p_window = DM.getWindow();

		// Check past window events.
		while (const std::optional<sf::Event> p_event = p_window->pollEvent()) {
			// Get Event
			sf::Event e = p_event.value();

			// Window closed?
			if (p_event->is<sf::Event::Closed>()) {
				printf("IM: Event Recieved - Closed\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "IM: Event Recieved - Closed\n");

				GM.setGameOver();
			}

			// Key was pressed?
			else if (p_event->is<sf::Event::KeyPressed>()) {
				printf("IM: Event Recieved - KeyPressed\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "IM: Event Recieved - KeyPressed\n");

				// Setup as KeyPressed event.
				sf::Event::KeyPressed* p_kb_event = reinterpret_cast<sf::Event::KeyPressed*> (&e);

				// Get SFML keyboard code.
				sf::Keyboard::Key key;
				key = p_kb_event->code;

				EventKeyboard new_key;
				new_key.setKey(convertKey(key));
				new_key.setKeyboardAction(KEY_PRESSED);

				// Send EventKeyboard to all Objects.
				onEvent(&new_key);
			}

			// Key was released?
			else if (p_event->is<sf::Event::KeyReleased>()) {
				printf("IM: Event Recieved - KeyReleased\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "IM: Event Recieved - KeyReleased\n");

				// Setup as KeyPressed event.
				sf::Event::KeyReleased* p_kb_event = reinterpret_cast<sf::Event::KeyReleased*> (&e);

				// Get SFML keyboard code.
				sf::Keyboard::Key key;
				key = p_kb_event->code;

				EventKeyboard new_key;
				new_key.setKey(convertKey(key));
				new_key.setKeyboardAction(KEY_RELEASED);

				// Send EventKeyboard to all Objects.
				onEvent(&new_key);
			}

			// Mouse moved?
			else if (p_event->is<sf::Event::MouseMoved>()) {
				printf("IM: Event Recieved - MouseMoved\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "IM: Event Recieved - MouseMoved\n");

				// Setup as MouseMoved event.
				sf::Event::MouseMoved* p_mse_event = reinterpret_cast<sf::Event::MouseMoved*> (&e);

				// Get pixel location.
				sf::Vector2i pixel_pos = p_mse_event->position;

				EventMouse new_mse;
				new_mse.setMouseButton(Mouse::UNDEFINED_MOUSE_BUTTON);
				new_mse.setMouseAction(MOVED);
				Vector new_vec(pixel_pos.x, pixel_pos.y);

				new_mse.setMousePosition(DM.pixelsToSpaces(new_vec));

				// Send EventMouse to all Objects.
				onEvent(&new_mse);
			}

			// Mouse clicked?
			else if (p_event->is<sf::Event::MouseButtonPressed>()) {
				printf("IM: Event Recieved - MouseButtonPressed\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "IM: Event Recieved - MouseButtonPressed\n");

				// Setup as MouseButtonPressed event.
				sf::Event::MouseButtonPressed* p_mse_event = reinterpret_cast<sf::Event::MouseButtonPressed*> (&e);

				EventMouse new_mse;
				new_mse.setMouseAction(CLICKED);

				if (p_mse_event->button == sf::Mouse::Button::Left) {
					new_mse.setMouseButton(Mouse::LEFT);
				}

				else if (p_mse_event->button == sf::Mouse::Button::Middle) {
					new_mse.setMouseButton(Mouse::MIDDLE);
				}

				else if (p_mse_event->button == sf::Mouse::Button::Right) {
					new_mse.setMouseButton(Mouse::RIGHT);
				}

				// Get pixel location.
				sf::Vector2i pixel_pos = p_mse_event->position;

				Vector new_vec(pixel_pos.x, pixel_pos.y);

				new_mse.setMousePosition(DM.pixelsToSpaces(new_vec));

				// Send EventMouse to all Objects.
				onEvent(&new_mse);
			}

			else {
				printf("IM: Event Recieved - UNKNOWN\n");
				LM.writeLog(ts::TEST_LOG_LEVEL, "IM: Event Recieved - UNKNOWN\n");
			}
		}
	}

	Keyboard::Key InputManager::convertKey(sf::Keyboard::Key key) const {
		switch (key) {
			case sf::Keyboard::Key::Space:
				return Keyboard::Key::SPACE;
			case sf::Keyboard::Key::Enter:
				return Keyboard::Key::RETURN;
			case sf::Keyboard::Key::Escape:
				return Keyboard::Key::ESCAPE;
			case sf::Keyboard::Key::Tab:
				return Keyboard::Key::TAB;
			case sf::Keyboard::Key::Left:
				return Keyboard::Key::LEFTARROW;
			case sf::Keyboard::Key::Right:
				return Keyboard::Key::RIGHTARROW;
			case sf::Keyboard::Key::Up:
				return Keyboard::Key::UPARROW;
			case sf::Keyboard::Key::Down:
				return Keyboard::Key::DOWNARROW;
			case sf::Keyboard::Key::Pause:
				return Keyboard::Key::PAUSE;
			case sf::Keyboard::Key::Hyphen:
				return Keyboard::Key::MINUS;
			case sf::Keyboard::Key::Equal:
				return Keyboard::Key::PLUS;
			case sf::Keyboard::Key::Grave:
				return Keyboard::Key::TILDE;
			case sf::Keyboard::Key::Period:
				return Keyboard::Key::PERIOD;
			case sf::Keyboard::Key::Comma:
				return Keyboard::Key::COMMA;
			case sf::Keyboard::Key::Slash:
				return Keyboard::Key::SLASH;
			case sf::Keyboard::Key::LControl:
				return Keyboard::Key::LEFTCONTROL;
			case sf::Keyboard::Key::RControl:
				return Keyboard::Key::RIGHTCONTROL;
			case sf::Keyboard::Key::LShift:
				return Keyboard::Key::LEFTSHIFT;
			case sf::Keyboard::Key::RShift:
				return Keyboard::Key::RIGHTSHIFT;
			case sf::Keyboard::Key::F1:
				return Keyboard::Key::F1;
			case sf::Keyboard::Key::F2:
				return Keyboard::Key::F2;
			case sf::Keyboard::Key::F3:
				return Keyboard::Key::F3;
			case sf::Keyboard::Key::F4:
				return Keyboard::Key::F4;
			case sf::Keyboard::Key::F5:
				return Keyboard::Key::F5;
			case sf::Keyboard::Key::F6:
				return Keyboard::Key::F6;
			case sf::Keyboard::Key::F7:
				return Keyboard::Key::F7;
			case sf::Keyboard::Key::F8:
				return Keyboard::Key::F8;
			case sf::Keyboard::Key::F9:
				return Keyboard::Key::F9;
			case sf::Keyboard::Key::F10:
				return Keyboard::Key::F10;
			case sf::Keyboard::Key::F11:
				return Keyboard::Key::F11;
			case sf::Keyboard::Key::F12:
				return Keyboard::Key::F12;
			case sf::Keyboard::Key::A:
				return Keyboard::Key::A;
			case sf::Keyboard::Key::B:
				return Keyboard::Key::B;
			case sf::Keyboard::Key::C:
				return Keyboard::Key::C;
			case sf::Keyboard::Key::D:
				return Keyboard::Key::D;
			case sf::Keyboard::Key::E:
				return Keyboard::Key::E;
			case sf::Keyboard::Key::F:
				return Keyboard::Key::F;
			case sf::Keyboard::Key::G:
				return Keyboard::Key::G;
			case sf::Keyboard::Key::H:
				return Keyboard::Key::H;
			case sf::Keyboard::Key::I:
				return Keyboard::Key::I;
			case sf::Keyboard::Key::J:
				return Keyboard::Key::J;
			case sf::Keyboard::Key::K:
				return Keyboard::Key::K;
			case sf::Keyboard::Key::L:
				return Keyboard::Key::L;
			case sf::Keyboard::Key::M:
				return Keyboard::Key::M;
			case sf::Keyboard::Key::N:
				return Keyboard::Key::N;
			case sf::Keyboard::Key::O:
				return Keyboard::Key::O;
			case sf::Keyboard::Key::P:
				return Keyboard::Key::P;
			case sf::Keyboard::Key::Q:
				return Keyboard::Key::Q;
			case sf::Keyboard::Key::R:
				return Keyboard::Key::R;
			case sf::Keyboard::Key::S:
				return Keyboard::Key::S;
			case sf::Keyboard::Key::T:
				return Keyboard::Key::T;
			case sf::Keyboard::Key::U:
				return Keyboard::Key::U;
			case sf::Keyboard::Key::V:
				return Keyboard::Key::V;
			case sf::Keyboard::Key::W:
				return Keyboard::Key::W;
			case sf::Keyboard::Key::X:
				return Keyboard::Key::X;
			case sf::Keyboard::Key::Y:
				return Keyboard::Key::Y;
			case sf::Keyboard::Key::Z:
				return Keyboard::Key::Z;
			case sf::Keyboard::Key::Num1:
				return Keyboard::Key::NUM1;
			case sf::Keyboard::Key::Num2:
				return Keyboard::Key::NUM2;
			case sf::Keyboard::Key::Num3:
				return Keyboard::Key::NUM3;
			case sf::Keyboard::Key::Num4:
				return Keyboard::Key::NUM4;
			case sf::Keyboard::Key::Num5:
				return Keyboard::Key::NUM5;
			case sf::Keyboard::Key::Num6:
				return Keyboard::Key::NUM6;
			case sf::Keyboard::Key::Num7:
				return Keyboard::Key::NUM7;
			case sf::Keyboard::Key::Num8:
				return Keyboard::Key::NUM8;
			case sf::Keyboard::Key::Num9:
				return Keyboard::Key::NUM9;
			case sf::Keyboard::Key::Num0:
				return Keyboard::Key::NUM0;
			default:
				return Keyboard::Key::UNDEFINED_KEY;
		}
	}
}