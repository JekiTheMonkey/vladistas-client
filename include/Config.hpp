#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <vector>
#include <stdint.h>


namespace vladistas
{
	class Config : private sf::NonCopyable
	{
	public:
		using Shortcut = std::vector<sf::Keyboard::Key>;
		struct Action
		{
			Shortcut shortcut;
			int64_t userID;
			int reportLevel;
		};

	public:
		Config();

		void init();

		sf::IpAddress getIpAddress() const;
		unsigned short getPort() const;
		std::vector<Action> getActions() const;

	private:
		sf::IpAddress m_ipAddress;
		unsigned short m_port;
		std::vector<Action> m_actions;
	};
} // namespace vladistas
