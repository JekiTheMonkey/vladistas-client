#include "Application.hpp"
#include "Client.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <exception>
#include <iostream>


namespace vladistas
{
	Application::Application()
	: m_client(std::make_unique<Client>())
	{	}

	Application::~Application() = default;

	void Application::init()
	{
		m_config.init();

		const auto serverIp = m_config.getIpAddress();
		const auto ip = sf::IpAddress::getPublicAddress() != serverIp
			? serverIp : sf::IpAddress::getLocalAddress();
		const auto port = m_config.getPort();

		const auto connected = m_client->connect(ip, port);
		if (!connected)
			throw std::runtime_error("Failed to connect to the server");
		std::cerr << "Connection has been enstablished successfully"
			<< std::endl;
	}

	void Application::run()
	{
		auto timeSinceLastUpdate = sf::Time::Zero;
		const auto timePerFrame = sf::seconds(1.f / 120.f);
		auto clock = sf::Clock();

		while (m_continue)
		{
			timeSinceLastUpdate += clock.restart();
			if (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				update();
				handleInput();
			}
		}
	}

	void Application::update()
	{
		int res;
		char buf[128];
		while (!m_buffer.empty())
		{
			const auto msg = m_buffer.front();
			res = snprintf(buf, sizeof(buf) - 1, "%ld %d",
				msg.userID, msg.reportLevel);
			buf[res] = '\0';

			fprintf(stderr, "Sending message [%s]\n", buf);
			res = m_client->send(buf, static_cast<std::size_t>(res + 1));
			if (!res)
			{
				fprintf(stderr, "Report to user with ID %ld could not be " \
					"sent to the server\n", msg.userID);
			}
			else
			{
				fprintf(stderr, "Report lv. %d to user %ld has been sent " \
					"successfully\n", msg.reportLevel, msg.userID);
			}
			m_buffer.pop();
		}
	}

	int getPressedIndex(const std::vector<Config::Action> &actions)
	{
		int i = 0;
		for (const auto &action : actions)
		{
			auto isPressed = true;
			for (const auto &shortcut : action.shortcut)
			{
				if (!sf::Keyboard::isKeyPressed(shortcut))
				{
					isPressed = false;
					break;
				}
			}
			if (isPressed)
				return i;
			i++;
		}
		return -1;
	}

	void Application::handleInput()
	{
		static auto wasPressed = false;
		const auto actions = m_config.getActions();
		const auto pressedIndex = getPressedIndex(actions);
		const auto isPressed = pressedIndex != -1;
		if (isPressed && wasPressed)
			return;
		if (isPressed)
		{
			const auto &action = actions.at(static_cast<size_t>(pressedIndex));
			fprintf(stderr, "Report lv. %d to user %ld has been saved to " \
				"send\n", action.reportLevel, action.userID);
			m_buffer.emplace(action.userID, action.reportLevel);
		}
		wasPressed = isPressed;
	}
} // namespace vladistas
