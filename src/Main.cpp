#include "Application.hpp"

#include <exception>
#include <iostream>


int main()
{
	vladistas::Application app;
	try
	{
		app.init();
		app.run();
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}
