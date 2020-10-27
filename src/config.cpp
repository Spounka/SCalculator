//
// Created by spounka on 22/10/2020.
//

// Last visit: 10/27/2020

#include "config.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <giomm.h>

namespace spounka
{
	int init()
	{
		auto app = Gtk::Application::create("tk.spounka.scalculator");
		auto builder = Gtk::Builder::create();
		if(loadUiFile(builder, SRC_DIR "scalculator/ui/calculator.glade"))
			return -1;
		Window* window = nullptr;
		builder->get_widget_derived("MainWindow", window);

		if(window)
		{
			app->run(*window);
			delete window;
			return 0;
		}
		else
			return 1;
	}

	int loadUiFile(const Glib::RefPtr<Gtk::Builder>& builder, const Glib::ustring& path)
	{
		try
		{
			builder->add_from_string(spounka::readFile(path));
		}
		catch (const Glib::FileError& error)
		{
			std::cout << "File Error: " << error.what() << std::endl;
			return 1;
		}
		catch (const Glib::MarkupError& error)
		{
			std::cout << "Markup Error: " << error.what() << std::endl;
			return 1;
		}
		catch (const Gtk::BuilderError& error)
		{
			std::cout << "Build Error: " << error.what() << std::endl;
			return 1;
		}
		catch (const Gio::ResourceError& error)
		{
			std::cout << "Resource error: " << error.what() << std::endl;
			return 1;
		}
		return 0;
	}
	Glib::ustring readFile(const Glib::ustring& path)
	{
		std::string output, line;
		try
		{
			std::ifstream uiFile(path);
			if (uiFile.is_open())
				while (uiFile.good())
				{
					getline(uiFile, line);
					output.append(line + '\n');
				}
			uiFile.close();

		}
		catch (const std::ifstream::failure& failure)
		{
			std::string errorCode = std::string("File opening failed: ") + failure.what() + std::string("\n");
			throw std::runtime_error(errorCode);
		}
		const char* out = output.data();
		return out;
	}

}