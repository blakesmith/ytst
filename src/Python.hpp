#ifndef YTST_PYTHON_HPP
#define YTST_PYTHON_HPP

#include <memory>
#include <vector>
#include <string>

extern "C" {
#include <Python.h>
}

namespace ytst {
	class PythonException : virtual public std::exception {
		const char *errMessage_;
	public:
		PythonException(const char *msg) : errMessage_(msg) {}
		const char *what() const throw() { return errMessage_; }
	};

	class GilLock {
		PyGILState_STATE* gil;
	public:
		GilLock(PyGILState_STATE* gil) : gil(gil) {
			*gil = PyGILState_Ensure();
		}

		~GilLock() {
			PyGILState_Release(*gil);
		}
	};

	class Python {
		PyGILState_STATE gil;
		std::shared_ptr<PyObject> make_arguments(std::vector<std::string> args);
	public:
		Python();
		~Python();
		void add_path(const char* path);
		std::shared_ptr<PyObject> import_module(const char* module);
		std::shared_ptr<PyObject> call_func(PyObject* module, const char* func, std::vector<std::string> args);
		void interrupt();
	};
}

#endif
