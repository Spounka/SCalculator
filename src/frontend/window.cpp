//
// Created by spounka on 17/10/2020.
//

#include "window.hpp"

#include <gtkmm/button.h>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace spounka
{
	Window::Window(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder> _refGlade) :
		Gtk::Window(cobject), refGlade(std::move(_refGlade)), mainGrid(nullptr), mainBox(nullptr),
		resultLabel(""), mainMenu(nullptr), quitMenuItem(nullptr), aboutMenuItem(nullptr)
	{
		this->set_decorated(true);
		result = 0;

		Glib::ustring buttonStrings[20] = {
			"DE", "CLR", "*", "/",
			"7", "8", "9", "-",
			"4", "5", "6", "+",
			"1", "2", "3", "=",
			"0", "0", ".", "="
		};
		refGlade->get_widget("mainGrid", mainGrid);
		refGlade->get_widget("mainBox", mainBox);
		refGlade->get_widget("mainMenu", mainMenu);
		refGlade->get_widget("quitMenuItem", quitMenuItem);
		refGlade->get_widget("aboutMenuItem", aboutMenuItem);

		if (!mainGrid || !mainBox || !mainMenu || !quitMenuItem || !aboutMenuItem)
		{
			std::cerr << "Failed to load all necessary elements\n";
			exit(255);
		}

		resultLabel.set_size_request(-1, 35);
		resultLabel.set_alignment(0.025);
		resultLabel.override_background_color(Gdk::RGBA("#fff"));
		resultLabel.override_color(Gdk::RGBA("#000"));

		mainBox->pack_start(resultLabel, Gtk::PACK_SHRINK, 0);
		resultLabel.set_margin_bottom(5);

		createButtons(buttonStrings);
		connectButtons();

		this->show_all_children();

	}
	Window::~Window()
	{
		for (auto& item : mainGrid->get_children())
			delete item;

		delete aboutMenuItem;
		delete quitMenuItem;
		delete mainMenu;
		delete mainGrid;
		delete mainBox;
	}

	void Window::onButtonClick(const Glib::ustring& label)
	{
		if (!isOperator(label))
		{
			if (operation == '=')
				eraseLabel(true);
			if (!label.compare(".") && resultLabel.get_text().find(".") != Glib::ustring::npos)
				return;
			resultLabel.set_label(resultLabel.get_label().append(label));
		}
		else
		{
			try
			{
				if (resultLabel.get_label().empty())
					return;
				if (operation != 'N')
					calcResult();
				firstNumber = std::stof(resultLabel.get_label());
				operation = label.data()[0];
				resultLabel.set_text("");
			}
			catch (const std::invalid_argument& error)
			{
				auto dialog = Gtk::MessageDialog("Invalid number");
				dialog.show();
			}
			catch (const std::out_of_range& error)
			{
				auto dialog = Gtk::MessageDialog("Out of range");
				dialog.set_secondary_text("The number you entered is too big");
				dialog.show();
			}
		}
	}
	void Window::calcResult()
	{
		if (operation == 'N') return;
		auto label = resultLabel.get_label();
		Gtk::MessageDialog errorDialog(*this, "");
		if (label.empty()) return;
		try
		{
			secondNumber = std::stof(label);
			switch (operation)
			{
			case '+':
				result = firstNumber + secondNumber;
				break;
			case '-':
				result = firstNumber - secondNumber;
				break;
			case '*':
				result = firstNumber * secondNumber;
				break;
			case '/':
				if (std::abs(secondNumber) >= 0.000000001)
				{
					result = firstNumber / secondNumber;
					break;
				}
				else
				{
					errorDialog.set_message("Zero Division Error");
					errorDialog.set_secondary_text("You cannot divide by a 0");
					errorDialog.show_all_children();
					errorDialog.run();
					return;
				}
			}
			operation = '=';
			resultLabel.set_label(std::to_string(result));
		}
		catch (const std::invalid_argument& error)
		{
			errorDialog.set_message("Invalid Argument");
			errorDialog.set_secondary_text("The operation you entered is invalid");
			errorDialog.run();
		}
		catch (const std::out_of_range& error)
		{
			errorDialog.set_message("Number out of Range");
			errorDialog.set_secondary_text("The number you entered was out of range, please consider a smaller number");
			errorDialog.run();
		}

	}
	void Window::eraseLabel(bool clearAll)
	{
		if (clearAll)
		{
			resultLabel.set_label("");
			result = 0;
			firstNumber = 0;
			secondNumber = 0;
			operation = 'N';
		}
		else
		{
			std::string text = resultLabel.get_label().raw();
			if (text.empty())
				return;
			text.pop_back();
			resultLabel.set_label(text);
		}
	}
	void Window::createButtons(const Glib::ustring* buttonStrings)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (i * 4 + j == 19)
					break;
				auto button = new Gtk::Button(buttonStrings[i * 4 + j]);
				if (!buttonStrings[i * 4 + j].compare("0"))
				{
					mainGrid->attach(*button, j, i, 2, 1);
					j++;
				}
				else if (!buttonStrings[i * 4 + j].compare("="))
					mainGrid->attach(*button, j, i, 1, 2);
				else
					mainGrid->attach(*button, j, i, 1, 1);

				button->set_margin_bottom(5);
				button->set_margin_top(5);
				button->set_margin_left(5);
				button->set_margin_right(5);
			}
		}
	}
	void Window::connectButtons()
	{
		for (auto widget : mainGrid->get_children())
		{
			auto button = (Gtk::Button*)widget;
			if (!button->get_label().compare("DE"))
				button->signal_clicked()
					  .connect(sigc::bind<bool>(sigc::mem_fun(*this, &Window::eraseLabel),
						  false));
			else if (!button->get_label().compare("CLR"))
				button->signal_clicked()
					  .connect(sigc::bind<bool>(sigc::mem_fun(*this, &Window::eraseLabel),
						  true));
			else if (!button->get_label().compare("="))
				button->signal_clicked()
					  .connect(sigc::mem_fun(*this, &Window::calcResult));
			else
			{
				button->signal_clicked()
					  .connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Window::onButtonClick),
						  button->get_label()));
			}
		}

		quitMenuItem->signal_activate().connect([this] { this->hide(); });
		aboutMenuItem->signal_activate().connect(sigc::mem_fun(*this, &Window::onAbout));

	}
	void Window::onAbout()
	{
		auto aboutDialog = Gtk::AboutDialog();
		aboutDialog.set_copyright("Copyright 2020 - All rights reserved");
		aboutDialog.set_license_type(Gtk::LICENSE_MIT_X11);
		aboutDialog.set_authors({ "Nazih Boudaakkar" });
		aboutDialog.set_comments("SCalculator is a Calculator written in C++ using gtkmm and glade\n"
								 "Program Written By Nazih Boudaakkar");

		aboutDialog.show_all_children();
		aboutDialog.run();
	}
	bool Window::isOperator(const Glib::ustring& string)
	{
		return !string.compare("+") || !string.compare("-") || !string.compare("*")
			|| !string.compare("/");
	}
}
