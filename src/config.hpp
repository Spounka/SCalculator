//
// Created by spounka on 10/5/20.
//

// Last visit: 10/27/2020

#ifndef SCALCULATOR_CONFIG_HPP_
#define SCALCULATOR_CONFIG_HPP_

#include "frontend/window.hpp"

namespace spounka
{
#if NDEBUG
#define SRC_DIR "/usr/share/"
#else
#define SRC_DIR "/home/spounka/Work/Cpp/SCalculator/"
#endif

	int init();
	int loadUiFile(const Glib::RefPtr<Gtk::Builder>& builder, const Glib::ustring& path);
	Glib::ustring readFile(const Glib::ustring& path);
}
#endif //SCALCULATOR_CONFIG_HPP_
