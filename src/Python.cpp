#include <stdexcept>
#include <iostream>

#include "Python.hpp"

namespace ytst {
	Python::Python() {
		Py_Initialize();
	}

	Python::~Python() {
		Py_Finalize();
	}

	void Python::add_path(const char* path) {
		PyObject* sys = PyImport_ImportModule("sys");
		PyObject* pPath = PyObject_GetAttrString(sys, "path");
		PyList_Append(pPath, PyString_FromString(path));
	}

	std::shared_ptr<PyObject> Python::import_module(const char* module) {
		PyObject* pName = PyString_FromString(module);
		PyObject* pModule = PyImport_Import(pName);
		Py_DECREF(pName);
		if (pModule == nullptr) {
			throw std::runtime_error("Error importing youtube module");
		}

		return std::shared_ptr<PyObject>(pModule,
						 [](PyObject* p) {
							 Py_DECREF(p);
						 });
	}

	std::shared_ptr<PyObject> Python::call_func(PyObject* module, const char* func, std::vector<std::string> args) {
		std::unique_ptr<PyObject, std::function<void(PyObject*)>>
			pFunc(PyObject_GetAttrString(module, func),
			      [](PyObject* p) {
				      Py_XDECREF(p);
			      });

		if (pFunc.get() && PyCallable_Check(pFunc.get())) {
			auto pArgs = make_arguments(args);
			PyObject* pValue = PyObject_CallObject(pFunc.get(), pArgs.get());
			if (pValue != nullptr) {
				return std::shared_ptr<PyObject>(pValue,
								 [](PyObject* p) { 
									 Py_DECREF(p);
								 });
			} else {
				throw std::runtime_error("Python call failed");
			}
		} else {
			throw std::runtime_error("Python object is not callable");
		}
		
		return nullptr;
	}

	std::shared_ptr<PyObject> Python::make_arguments(std::vector<std::string> args) {
		PyObject* tuple = PyTuple_New(1);
		PyObject* list = PyList_New(args.size());

		for (unsigned int i = 0; i < args.size(); ++i) {
			PyObject* arg = PyString_FromString(args[i].c_str());
			PyList_SetItem(list, i, arg);
		}
		
		PyTuple_SetItem(tuple, 0, list);

		return std::shared_ptr<PyObject>(tuple,
						 [](PyObject* p) {
							 Py_DECREF(p);
						 });
	}
}
