#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>


namespace vladistas
{
	class Client : private sf::NonCopyable
	{
	public:
		Client() = default;
		~Client();

		bool connect(const sf::IpAddress &ip, unsigned short port);
		void disconnect();
		bool send(const char *data, std::size_t size);

	private:
		sf::TcpSocket m_socket;
	};
} // namespace vladistas
