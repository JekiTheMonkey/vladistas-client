#pragma once

#include "Config.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <memory>
#include <queue>

#include <stdint.h>


namespace vladistas
{
	class Client;

	class Application : private sf::NonCopyable
	{
	public:
		Application();
		~Application();

		void init();
		void run();

	private:
		void update();
		void handleInput();

		bool connect();
		void checkConnection();

	private:
		struct Message
		{
			Message(int64_t _userID, int _reportLevel)
				: userID(_userID), reportLevel(_reportLevel) { }
			int64_t userID;
			int reportLevel;
		};

	private:
		Config m_config;

		std::unique_ptr<Client> m_client;
		std::queue<Message> m_buffer;
		bool m_continue = true;
	};
} // namespace vladistas
