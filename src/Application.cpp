#include "Application.hpp"
#include "Client.hpp"

#include <SFML/System.hpp>
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
		const auto connected = connect();
		if (connected)
			checkConnection();
	}

	void Application::run()
	{
		auto timeSinceLastUpdate = sf::Time::Zero;
		const auto timePerFrame = sf::seconds(1.f / 120.f);
		auto clock = sf::Clock();

		while (m_continue)
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				handleInput();
				update();
				checkConnection();
			}
			sf::sleep(timePerFrame - timeSinceLastUpdate);
		}
	}

	void Application::update()
	{
		int res;
		char buf[128];
		while (!m_buffer.empty())
		{
			const auto msg = m_buffer.front();
			res = snprintf(buf, sizeof(buf) - 1, "%lld %d",
				msg.userID, msg.reportLevel);
			buf[res] = '\0';

			fprintf(stderr, "Sending message [%s]...\n", buf);
			res = m_client->send(buf, static_cast<std::size_t>(res + 1));
			if (res == sf::Socket::Done)
			{
				fprintf(stderr, "Report lv. %d to user %lld has been sent " \
					"successfully\n", msg.reportLevel, msg.userID);
			}
			else
			{
				fprintf(stderr, "Report to user with ID %lld could not be " \
					"sent to the server\n", msg.userID);
				if (res == sf::Socket::Disconnected)
				{
					fprintf(stderr, "Connection with the server has been " \
						" lost\n");
					m_continue = false;
				}
			}
			m_buffer.pop();
		}
	}

	bool Application::connect()
	{
		const auto serverIp = m_config.getIpAddress();
		const auto ip = sf::IpAddress::getPublicAddress() != serverIp
			? serverIp : sf::IpAddress::getLocalAddress();
		const auto port = m_config.getPort();
		const auto connected = m_client->connect(ip, port);

		if (connected == sf::Socket::Done)
		{
			fprintf(stderr, "Connection has been enstablished successfully\n");
			return true;
		}
		else
		{
			fprintf(stderr, "Failed to connect to the server. " \
				"Error code: %d\n", connected);
			return false;
		}
	}

	void Application::checkConnection()
	{
		const float timeouts[] =
			{ 5.f,   15.f,  30.f,  60.f,
			  120.f, 180.f, 240.f, 300.f };
		auto i = 0u;
		while (!m_continue)
		{
			fprintf(stderr, "Trying to reconnect to the server...\n");
			const auto connected = connect();
			if (!connected)
			{
				fprintf(stderr, "Failed to connect... Retrying in %f...",
					timeouts[i]);
				sf::sleep(sf::seconds(timeouts[i]));
				i += i < sizeof(timeouts) - 1;
			}
			else
				m_continue = true;
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
			m_buffer.emplace(action.userID, action.reportLevel);
		}
		wasPressed = isPressed;
	}
} // namespace vladistas
