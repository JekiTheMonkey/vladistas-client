#include "Config.hpp"

#include <cassert>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>

/* fuck C++ */
size_t find(const char *str, char ch)
{
	const char *it = str;
	while (*it != ch)
		it++;
	return size_t(it - str);
}

namespace vladistas
{
	Config::Shortcut toShortcut(const char *str);
	sf::Keyboard::Key toKey(const char *str);

	Config::Config()
	{	}

	void Config::init()
	{
		const auto filepath = std::string("vladistas.cfg");
		auto ifs = std::ifstream(filepath);
		if (!ifs.is_open())
		{
			throw std::runtime_error("Config::init() Failed to open \"" +
				filepath + "\"");
		}
		char buf[4096];

		ifs.getline(buf, sizeof(buf), ' ');
		m_ipAddress = sf::IpAddress(buf);

		ifs.getline(buf, sizeof(buf), '\n');
		m_port = static_cast<unsigned short>(std::stoi(buf));

		while (ifs.getline(buf, sizeof(buf), '\n'))
		{
			char *it = buf;
			size_t len;
			auto action = Config::Action();

			len = find(it, ' ');
			action.userID = std::stoll(it);
			it += len + 1;

			len = find(it, ' ');
			action.reportLevel = std::stoi(it);
			it += len + 1;

			action.shortcut = toShortcut(it);
			if (!action.shortcut.empty())
			{
				fprintf(stderr, "New action has been added. Report lv. %d" \
					", user ID %lld\n", action.reportLevel, action.userID);
				m_actions.push_back(std::move(action));
			}
		}
	}

	sf::IpAddress Config::getIpAddress() const
	{
		return m_ipAddress;
	}

	unsigned short Config::getPort() const
	{
		return m_port;
	}

	std::vector<Config::Action> Config::getActions() const
	{
		return m_actions;
	}

	Config::Shortcut toShortcut(const char *str)
	{
		char buf[256];
		auto shortcut = Config::Shortcut();
		for (const char *it = str; ; it++)
		{
			if (*it == ' ' || *it == '\n' || *it == '\0')
			{
				const auto len = size_t(it - str);
				assert(len < sizeof(buf) - 1);

				strncpy(buf, str, len);
				buf[len] = '\0';

				const auto key = toKey(buf);
				if (key == sf::Keyboard::Unknown)
				{
					fprintf(stderr, "\"%s\" syntax error\n", str);
					return {};
				}
				shortcut.emplace_back(key);
				str += len + 1;
			}
			if (*it == '\n' || *it == '\0')
				break;
		}
		return shortcut;
	}

	sf::Keyboard::Key toKey(const char *str)
	{
		if (strcmp(str, "A") == 0) return sf::Keyboard::A;
		else if (strcmp(str, "B") == 0) return sf::Keyboard::B;
		else if (strcmp(str, "C") == 0) return sf::Keyboard::C;
		else if (strcmp(str, "D") == 0) return sf::Keyboard::D;
		else if (strcmp(str, "E") == 0) return sf::Keyboard::E;
		else if (strcmp(str, "F") == 0) return sf::Keyboard::F;
		else if (strcmp(str, "G") == 0) return sf::Keyboard::G;
		else if (strcmp(str, "H") == 0) return sf::Keyboard::H;
		else if (strcmp(str, "I") == 0) return sf::Keyboard::I;
		else if (strcmp(str, "J") == 0) return sf::Keyboard::J;
		else if (strcmp(str, "K") == 0) return sf::Keyboard::K;
		else if (strcmp(str, "L") == 0) return sf::Keyboard::L;
		else if (strcmp(str, "M") == 0) return sf::Keyboard::M;
		else if (strcmp(str, "N") == 0) return sf::Keyboard::N;
		else if (strcmp(str, "O") == 0) return sf::Keyboard::O;
		else if (strcmp(str, "P") == 0) return sf::Keyboard::P;
		else if (strcmp(str, "Q") == 0) return sf::Keyboard::Q;
		else if (strcmp(str, "R") == 0) return sf::Keyboard::R;
		else if (strcmp(str, "S") == 0) return sf::Keyboard::S;
		else if (strcmp(str, "T") == 0) return sf::Keyboard::T;
		else if (strcmp(str, "U") == 0) return sf::Keyboard::U;
		else if (strcmp(str, "V") == 0) return sf::Keyboard::V;
		else if (strcmp(str, "W") == 0) return sf::Keyboard::W;
		else if (strcmp(str, "X") == 0) return sf::Keyboard::X;
		else if (strcmp(str, "Y") == 0) return sf::Keyboard::Y;
		else if (strcmp(str, "Z") == 0) return sf::Keyboard::Z;
		else if (strcmp(str, "Num0") == 0) return sf::Keyboard::Num0;
		else if (strcmp(str, "Num1") == 0) return sf::Keyboard::Num1;
		else if (strcmp(str, "Num2") == 0) return sf::Keyboard::Num2;
		else if (strcmp(str, "Num3") == 0) return sf::Keyboard::Num3;
		else if (strcmp(str, "Num4") == 0) return sf::Keyboard::Num4;
		else if (strcmp(str, "Num5") == 0) return sf::Keyboard::Num5;
		else if (strcmp(str, "Num6") == 0) return sf::Keyboard::Num6;
		else if (strcmp(str, "Num7") == 0) return sf::Keyboard::Num7;
		else if (strcmp(str, "Num8") == 0) return sf::Keyboard::Num8;
		else if (strcmp(str, "Num9") == 0) return sf::Keyboard::Num9;
		else if (strcmp(str, "Escape") == 0) return sf::Keyboard::Escape;
		else if (strcmp(str, "LControl") == 0) return sf::Keyboard::LControl;
		else if (strcmp(str, "LShift") == 0) return sf::Keyboard::LShift;
		else if (strcmp(str, "LAlt") == 0) return sf::Keyboard::LAlt;
		else if (strcmp(str, "LSystem") == 0) return sf::Keyboard::LSystem;
		else if (strcmp(str, "RControl") == 0) return sf::Keyboard::RControl;
		else if (strcmp(str, "RShift") == 0) return sf::Keyboard::RShift;
		else if (strcmp(str, "RAlt") == 0) return sf::Keyboard::RAlt;
		else if (strcmp(str, "RSystem") == 0) return sf::Keyboard::RSystem;
		else if (strcmp(str, "Menu") == 0) return sf::Keyboard::Menu;
		else if (strcmp(str, "LBracket") == 0) return sf::Keyboard::LBracket;
		else if (strcmp(str, "RBracket") == 0) return sf::Keyboard::RBracket;
		else if (strcmp(str, "Semicolon") == 0) return sf::Keyboard::Semicolon;
		else if (strcmp(str, "Comma") == 0) return sf::Keyboard::Comma;
		else if (strcmp(str, "Period") == 0) return sf::Keyboard::Period;
		else if (strcmp(str, "Quote") == 0) return sf::Keyboard::Quote;
		else if (strcmp(str, "Slash") == 0) return sf::Keyboard::Slash;
		else if (strcmp(str, "Backslash") == 0) return sf::Keyboard::Backslash;
		else if (strcmp(str, "Tilde") == 0) return sf::Keyboard::Tilde;
		else if (strcmp(str, "Equal") == 0) return sf::Keyboard::Equal;
		else if (strcmp(str, "Hyphen") == 0) return sf::Keyboard::Hyphen;
		else if (strcmp(str, "Space") == 0) return sf::Keyboard::Space;
		else if (strcmp(str, "Enter") == 0) return sf::Keyboard::Enter;
		else if (strcmp(str, "Backspace") == 0) return sf::Keyboard::Backspace;
		else if (strcmp(str, "Tab") == 0) return sf::Keyboard::Tab;
		else if (strcmp(str, "PageUp") == 0) return sf::Keyboard::PageUp;
		else if (strcmp(str, "PageDown") == 0) return sf::Keyboard::PageDown;
		else if (strcmp(str, "End") == 0) return sf::Keyboard::End;
		else if (strcmp(str, "Home") == 0) return sf::Keyboard::Home;
		else if (strcmp(str, "Insert") == 0) return sf::Keyboard::Insert;
		else if (strcmp(str, "Delete") == 0) return sf::Keyboard::Delete;
		else if (strcmp(str, "Add") == 0) return sf::Keyboard::Add;
		else if (strcmp(str, "Subtract") == 0) return sf::Keyboard::Subtract;
		else if (strcmp(str, "Multiply") == 0) return sf::Keyboard::Multiply;
		else if (strcmp(str, "Divide") == 0) return sf::Keyboard::Divide;
		else if (strcmp(str, "Left") == 0) return sf::Keyboard::Left;
		else if (strcmp(str, "Right") == 0) return sf::Keyboard::Right;
		else if (strcmp(str, "Up") == 0) return sf::Keyboard::Up;
		else if (strcmp(str, "Down") == 0) return sf::Keyboard::Down;
		else if (strcmp(str, "Numpad0") == 0) return sf::Keyboard::Numpad0;
		else if (strcmp(str, "Numpad1") == 0) return sf::Keyboard::Numpad1;
		else if (strcmp(str, "Numpad2") == 0) return sf::Keyboard::Numpad2;
		else if (strcmp(str, "Numpad3") == 0) return sf::Keyboard::Numpad3;
		else if (strcmp(str, "Numpad4") == 0) return sf::Keyboard::Numpad4;
		else if (strcmp(str, "Numpad5") == 0) return sf::Keyboard::Numpad5;
		else if (strcmp(str, "Numpad6") == 0) return sf::Keyboard::Numpad6;
		else if (strcmp(str, "Numpad7") == 0) return sf::Keyboard::Numpad7;
		else if (strcmp(str, "Numpad8") == 0) return sf::Keyboard::Numpad8;
		else if (strcmp(str, "Numpad9") == 0) return sf::Keyboard::Numpad9;
		else if (strcmp(str, "F1") == 0) return sf::Keyboard::F1;
		else if (strcmp(str, "F2") == 0) return sf::Keyboard::F2;
		else if (strcmp(str, "F3") == 0) return sf::Keyboard::F3;
		else if (strcmp(str, "F4") == 0) return sf::Keyboard::F4;
		else if (strcmp(str, "F5") == 0) return sf::Keyboard::F5;
		else if (strcmp(str, "F6") == 0) return sf::Keyboard::F6;
		else if (strcmp(str, "F7") == 0) return sf::Keyboard::F7;
		else if (strcmp(str, "F8") == 0) return sf::Keyboard::F8;
		else if (strcmp(str, "F9") == 0) return sf::Keyboard::F9;
		else if (strcmp(str, "F10") == 0) return sf::Keyboard::F10;
		else if (strcmp(str, "F11") == 0) return sf::Keyboard::F11;
		else if (strcmp(str, "F12") == 0) return sf::Keyboard::F12;
		else if (strcmp(str, "F13") == 0) return sf::Keyboard::F13;
		else if (strcmp(str, "F14") == 0) return sf::Keyboard::F14;
		else if (strcmp(str, "F15") == 0) return sf::Keyboard::F15;
		else if (strcmp(str, "Pause") == 0) return sf::Keyboard::Pause;
		else return sf::Keyboard::Unknown;
	}
} // namespace vladistas
