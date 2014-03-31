#include "log.h"

#include "python_supervisor.h"

namespace ytst {
	PythonSupervisor::PythonSupervisor() {}
	PythonSupervisor::~PythonSupervisor() {}

	void PythonSupervisor::add_default_path(std::string path) {
		default_paths.push_back(path);
	}

	std::unique_ptr<PythonExecutor> PythonSupervisor::new_python() {
		auto python = std::unique_ptr<PythonExecutor>(new PythonExecutor);
		for (auto path : default_paths) {
			python->add_path(path.c_str());
		}

		return std::move(python);
	}
}
