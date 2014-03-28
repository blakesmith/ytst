#ifndef YTST_PYTHON_SUPERVISOR_H
#define YTST_PYTHON_SUPERVISOR_H

#include <vector>
#include <string>
#include <memory>

#include "Python.hpp"

namespace ytst {
	class PythonSupervisor {
		std::vector<std::string> default_paths;
	public:
		PythonSupervisor();
		~PythonSupervisor();
		void add_default_path(std::string path);
		std::shared_ptr<Python> new_python();
	};
}

#endif
