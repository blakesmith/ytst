#ifndef YTST_PYTHON_HPP
#define YTST_PYTHON_HPP

#include <memory>
#include <vector>
#include <string>

extern "C" {
#include <Python.h>
}

namespace ytst {
	class Python {
		std::shared_ptr<PyObject> make_arguments(std::vector<std::string> args);
	public:
		Python();
		~Python();
		void add_path(const char* path);
		std::shared_ptr<PyObject> import_module(const char* module);
		std::shared_ptr<PyObject> call_func(PyObject* module, const char* func, std::vector<std::string> args);
	};
}

#endif
