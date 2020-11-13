//
// Created by spounka on 17/10/2020.
//

// Last visit: 10/27/2020

#ifndef SCALCULATOR_WINDOW_HPP
#define SCALCULATOR_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/menubar.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/messagedialog.h>

#include <config.hpp>

namespace spounka
{
	class Window : public Gtk::Window
	{
	public:
		Window(BaseObjectType* cobject, Glib::RefPtr<Gtk::Builder> _refGlade);
		virtual ~Window();

	protected:
		Glib::RefPtr<Gtk::Builder> refGlade;

		Gtk::Grid* mainGrid;
		Gtk::Box* mainBox;
		Gtk::MenuBar* mainMenu;
		Gtk::ImageMenuItem* quitMenuItem;
		Gtk::ImageMenuItem* aboutMenuItem;

		Gtk::Label resultLabel;
		
		float firstNumber, secondNumber, result;
		char operation = 'N';

		void createButtons(const Glib::ustring* buttonStrings);
		void onButtonClick(const Glib::ustring& label);
		void connectButtons();
		void eraseLabel(bool clearAll = false);
		void onAbout();
	private:
		static bool isOperator(const Glib::ustring& string);
		void calcResult();
	};
}
#endif //SCALCULATOR_WINDOW_HPP
