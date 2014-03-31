#ifndef YTST_PYTHON_SUPERVISOR_H
#define YTST_PYTHON_SUPERVISOR_H

#include <vector>
#include <string>
#include <memory>

#include "python_executor.h"

namespace ytst {
	class PythonSupervisor {
		std::vector<std::string> default_paths;
	public:
		PythonSupervisor();
		~PythonSupervisor();
		void add_default_path(std::string path);
		std::unique_ptr<PythonExecutor> new_python();
	};
}

#endif
