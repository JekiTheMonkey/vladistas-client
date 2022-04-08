#include "Client.hpp"

#include <iostream>


namespace vladistas
{
	sf::Socket::Status Client::connect(const sf::IpAddress &ip,
		unsigned short port)
	{
		const auto status = m_socket.connect(ip, port, sf::seconds(5.f));

		if (status == sf::Socket::Done)
			std::cerr << "Connection with the server has been established " \
				"successfully" << std::endl;
		else
		if (status == sf::Socket::NotReady)
			std::cerr << "Connection has not been established, the server "
				"is probably offline" << std::endl;
		else
		if (status == sf::Socket::Disconnected)
			std::cerr << "Socket has been disconnected, the server is " \
				"probably offline" << std::endl;
		else
		if (status == sf::Socket::Error)
			std::cerr << "An unexpected error happend while connecting to " \
				"the server" << std::endl;
		else
			std::cerr << "Something unexpected happend while connecting to " \
				"the server, please report this fact" << std::endl;

		return status;
	}

	void Client::disconnect()
	{
		m_socket.disconnect();
	}

	sf::Socket::Status Client::send(const char *data, std::size_t size)
	{
		const auto status = m_socket.send(data, size);

		switch (status)
		{
			case sf::Socket::Partial:
				std::cerr << "The socket has sent a part of the data"
					<< std::endl;
				break;
			case sf::Socket::Disconnected:
				std::cerr << "The socket has been disconnected. Terminating "
					"the program execution" << std::endl;
				exit(1);
			case sf::Socket::Error:
				std::cerr << "An unexpected error happened while sending " \
					"the data" << std::endl;
				break;
			default: break;
		}

		return status;
	}

	Client::~Client()
	{
		m_socket.disconnect();
	}
} // namespace vladistas
