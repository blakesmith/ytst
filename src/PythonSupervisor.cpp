#include "Log.hpp"


#include "PythonSupervisor.hpp"

namespace ytst {
	PythonSupervisor::PythonSupervisor() {}
	PythonSupervisor::~PythonSupervisor() {}

	void PythonSupervisor::add_default_path(std::string path) {
		default_paths.push_back(path);
	}

	std::shared_ptr<Python> PythonSupervisor::new_python() {
		auto python = std::make_shared<Python>();
		for (auto path : default_paths) {
			python->add_path(path.c_str());
		}

		return python;
	}
}
