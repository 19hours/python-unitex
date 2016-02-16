/*
 * NOTE: some parts of this file are an adaptation of the 'fr_umlv_unitex_jni_UnitexJni.cpp' file
 *       which is included in the Unitex source distribution.
 *
 */
#include <Python.h>

#include "AbstractFilePlugCallback.h"
#include "UnitexTool.h"
#include "UnitexLibIO.h"

#if defined(UNITEX_HAVING_PERSISTANCE_INTERFACE) && (!(defined(UNITEX_PREVENT_USING_PERSISTANCE_INTERFACE)))
#include "PersistenceInterface.h"
#endif

#ifdef HAS_UNITEX_NAMESPACE
using namespace unitex;
#endif

static char unitex_docstring[] =
	"This module provides some usefull C function to work with the Unitex library.";



/************************
 * UNITEX TOOL FUNCTION *
 ************************/

/* 'unitex_tool' function */
static char unitex_tool_docstring[] =
	"This function launches an Unitex command.";
static PyObject *unitex_tool(PyObject *self, PyObject *args);

PyObject *unitex_tool(PyObject *self, PyObject *args) {
	char *command;
	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;

	unsigned int ret;
	ret = UnitexTool_public_run_string(command);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}



/*************************
 * PERSISTENCE FUNCTIONS *
 *************************/

/* 'unitex_load_persistent_dictionary' function */
static char unitex_load_persistent_dictionary_docstring[] =
	"This function loads a dictionary in the persistent space.";
static PyObject *unitex_load_persistent_dictionary(PyObject *self, PyObject *args);

PyObject *unitex_load_persistent_dictionary(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;
	PyObject *result = NULL;

	size_t length = strlen(path)+0x200;

	char *persistent_path = (char*)malloc(length+1);
	if (persistent_path == NULL) {
		return NULL;
	}

	if (persistence_public_load_dictionary(path, persistent_path, length)) {
		result = Py_BuildValue("s", persistent_path);
	}
	free(persistent_path);

	return result;
}

/* 'unitex_load_persistent_fst2' function */
static char unitex_load_persistent_fst2_docstring[] =
	"This function loads a fst2 in the persistent space.";
static PyObject *unitex_load_persistent_fst2(PyObject *self, PyObject *args);

PyObject *unitex_load_persistent_fst2(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;
	PyObject *result = NULL;

	size_t length = strlen(path)+0x200;

	char *persistent_path = (char*)malloc(length+1);
	if (persistent_path == NULL) {
		return NULL;
	}

	if (persistence_public_load_fst2(path, persistent_path, length)) {
		result = Py_BuildValue("s", persistent_path);
	}
	free(persistent_path);

	return result;
}

/* 'unitex_load_persistent_alphabet' function */
static char unitex_load_persistent_alphabet_docstring[] =
	"This function loads an alphabet in the persistent space.";
static PyObject *unitex_load_persistent_alphabet(PyObject *self, PyObject *args);

PyObject *unitex_load_persistent_alphabet(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;
	PyObject *result = NULL;

	size_t length = strlen(path)+0x200;

	char *persistent_path = (char*)malloc(length+1);
	if (persistent_path == NULL) {
		return NULL;
	}

	if (persistence_public_load_alphabet(path, persistent_path, length)) {
		result = Py_BuildValue("s", persistent_path);
	}
	free(persistent_path);

	return result;
}



/* 'unitex_free_persistent_dictionary' function */
static char unitex_free_persistent_dictionary_docstring[] =
	"This function removes a dictionary from the persistent space.";
static PyObject *unitex_free_persistent_dictionary(PyObject *self, PyObject *args);

PyObject *unitex_free_persistent_dictionary(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	persistence_public_unload_dictionary(path);

	Py_RETURN_NONE;
}

/* 'unitex_free_persistent_fst2' function */
static char unitex_free_persistent_fst2_docstring[] =
	"This function removes a fst2 from the persistent space.";
static PyObject *unitex_free_persistent_fst2(PyObject *self, PyObject *args);

PyObject *unitex_free_persistent_fst2(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	persistence_public_unload_fst2(path);

	Py_RETURN_NONE;
}

/* 'unitex_free_persistent_alphabet' function */
static char unitex_free_persistent_alphabet_docstring[] =
	"This function removes an alphabet from the persistent space.";
static PyObject *unitex_free_persistent_alphabet(PyObject *self, PyObject *args);

PyObject *unitex_free_persistent_alphabet(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	persistence_public_unload_alphabet(path);

	Py_RETURN_NONE;
}



/* 'unitex_is_persistent_dictionary' function */
static char unitex_is_persistent_dictionary_docstring[] =
	"This function checks if a dictionary is in the persistent space.";
static PyObject *unitex_is_persistent_dictionary(PyObject *self, PyObject *args);

PyObject *unitex_is_persistent_dictionary(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	unsigned int ret;
	ret = persistence_public_is_persisted_dictionary_filename(path);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}

/* 'unitex_is_persistent_fst2' function */
static char unitex_is_persistent_fst2_docstring[] =
	"This function checks if a fst2 is in the persistent space.";
static PyObject *unitex_is_persistent_fst2(PyObject *self, PyObject *args);

PyObject *unitex_is_persistent_fst2(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	unsigned int ret;
	ret = persistence_public_is_persisted_fst2_filename(path);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}

/* 'unitex_is_persistent_alphabet' function */
static char unitex_is_persistent_alphabet_docstring[] =
	"This function checks if an alphabet is in the persistent space.";
static PyObject *unitex_is_persistent_alphabet(PyObject *self, PyObject *args);

PyObject *unitex_is_persistent_alphabet(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	unsigned int ret;
	ret = persistence_public_is_persisted_alphabet_filename(path);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}



/*****************
 * I/O FUNCTIONS *
 *****************/

/* 'unitex_enable_stdout' function */
static char unitex_enable_stdout_docstring[] =
	"This function enable the standard output.";
static PyObject *unitex_enable_stdout(PyObject *self, PyObject *noarg);

PyObject *unitex_enable_stdout(PyObject *self, PyObject *noarg) {
	enum stdwrite_kind swk = stdwrite_kind_out;

	unsigned int ret;
	ret = SetStdWriteCB(swk, 0, NULL, NULL);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}

/* 'unitex_enable_stderr' function */
static char unitex_enable_stderr_docstring[] =
	"This function enable the error output.";
static PyObject *unitex_enable_stderr(PyObject *self, PyObject *noarg);

PyObject *unitex_enable_stderr(PyObject *self, PyObject *noarg) {
	enum stdwrite_kind swk = stdwrite_kind_err;

	unsigned int ret;
	ret = SetStdWriteCB(swk, 0, NULL, NULL);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}

/* 'unitex_disable_stdout' function */
static char unitex_disable_stdout_docstring[] =
	"This function disable the standard output.";
static PyObject *unitex_disable_stdout(PyObject *self, PyObject *noarg);

PyObject *unitex_disable_stdout(PyObject *self, PyObject *noarg) {
	enum stdwrite_kind swk = stdwrite_kind_out;

	unsigned int ret;
	ret = SetStdWriteCB(swk, 1, NULL, NULL);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}

/* 'unitex_disable_stderr' function */
static char unitex_disable_stderr_docstring[] =
	"This function disable the error output.";
static PyObject *unitex_disable_stderr(PyObject *self, PyObject *noarg);

PyObject *unitex_disable_stderr(PyObject *self, PyObject *noarg) {
	enum stdwrite_kind swk = stdwrite_kind_err;

	unsigned int ret;
	ret = SetStdWriteCB(swk, 1, NULL, NULL);

	return Py_BuildValue("O", ret ? Py_True: Py_False);
}

/* 'unitex_cp' function */
static char unitex_cp_docstring[] =
	"This function copies a file to the (virtual) filesystem.";
static PyObject *unitex_cp(PyObject *self, PyObject *args);

PyObject *unitex_cp(PyObject *self, PyObject *args) {
	char *source_path;
	char *target_path;
	if (!PyArg_ParseTuple(args, "ss", &source_path, &target_path))
		return NULL;

	unsigned int ret;
	ret = CopyUnitexFile(source_path, target_path);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}

/* 'unitex_rm' function */
static char unitex_rm_docstring[] =
	"This function removes a file from the (virtual) filesystem.";
static PyObject *unitex_rm(PyObject *self, PyObject *args);

PyObject *unitex_rm(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	unsigned int ret;
	ret = RemoveUnitexFile(path);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}

/* 'unitex_mv' function */
static char unitex_mv_docstring[] =
	"This function renames (and potentially moves) a (virtual) file.";
static PyObject *unitex_mv(PyObject *self, PyObject *args);

PyObject *unitex_mv(PyObject *self, PyObject *args) {
	char *old_path;
	char *new_path;
	if (!PyArg_ParseTuple(args, "ss", &old_path, &new_path))
		return NULL;

	unsigned int ret;
	ret = RenameUnitexFile(old_path, new_path);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}

/* 'unitex_mkdir' function */
static char unitex_mkdir_docstring[] =
	"This function creates a directory on the disk.";
static PyObject *unitex_mkdir(PyObject *self, PyObject *args);

PyObject *unitex_mkdir(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	unsigned int ret;
	ret = CreateUnitexFolder(path);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}

/* 'unitex_rmdir' function */
static char unitex_rmdir_docstring[] =
	"This function removes a directory from disk (and all its content).";
static PyObject *unitex_rmdir(PyObject *self, PyObject *args);

PyObject *unitex_rmdir(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	unsigned int ret;
	ret = RemoveUnitexFolder(path);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}

/* 'unitex_ls' function */
static char unitex_ls_docstring[] =
	"This function list (disk or virtual) directory contents.";
static PyObject *unitex_ls(PyObject *self, PyObject *args);

PyObject *unitex_ls(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	char **_file_list = GetUnitexFileList(path);
	if (_file_list==NULL)
		return PyList_New(0);

	unsigned int size = 0;
	while ((*(_file_list + size))!=NULL) {
		size ++;
	}

	PyObject *file_list = PyList_New(size);
	for (unsigned int i = 0; i != size; ++i) {
		PyList_SET_ITEM(file_list, i, PyUnicode_FromString(_file_list[i]));
	}

	char **_file_list_walk=_file_list;
	while ((*_file_list_walk)!=NULL) {
		free(*_file_list_walk);
		_file_list_walk++;
	}
	free(_file_list);

	return file_list;
}

/* 'unitex_read_file' function (UTF-8 encoding only)*/
static char unitex_read_file_docstring[] =
	"This function read a (virtual) file.";
static PyObject *unitex_read_file(PyObject *self, PyObject *args);

PyObject *unitex_read_file(PyObject *self, PyObject *args) {
	char *path;
	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;
	PyObject *content = NULL;

    UNITEXFILEMAPPED *amf;
    const void *buffer;
    size_t file_size;

	GetUnitexFileReadBuffer(path, &amf, &buffer, &file_size);
	const unsigned char* bufchar = (const unsigned char*)buffer;

	size_t bom_size = 0;
    if (file_size>2) {
        if (((*(bufchar))==0xef) && ((*(bufchar+1))==0xbb) && ((*(bufchar+2))==0xbf)) {
            bom_size = 3;
        }
	}

	char* _content = (char*)malloc(file_size+1);
	memcpy(_content, bufchar+bom_size, file_size-bom_size);

	*(_content+file_size-bom_size) = '\0';

	content = PyUnicode_FromString(_content);
	free(_content);

    CloseUnitexFileReadBuffer(amf, buffer, file_size);

    return content;
}

/* 'unitex_write_file' function (UTF-8 encoding only)*/
static char unitex_write_file_docstring[] =
	"This function write a (virtual) file.";
static PyObject *unitex_write_file(PyObject *self, PyObject *args);

PyObject *unitex_write_file(PyObject *self, PyObject *args) {
	char *path;
	PyObject *ustring;
	int *use_bom;
	if (!PyArg_ParseTuple(args, "sUi", &path, &ustring, &use_bom))
		return NULL;

	PyObject *bytes;
	char *content;
	Py_ssize_t length;

	bytes = PyUnicode_AsUTF8String(ustring);
	PyBytes_AsStringAndSize(bytes, &content, &length);

	const unsigned char UTF8BOM[3] = { 0xef,0xbb,0xbf };

	unsigned int ret;
	ret = WriteUnitexFile(path, UTF8BOM, use_bom ? 3:0, content, length);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}

/* 'unitex_append_to_file' function */
static char unitex_append_to_file_docstring[] =
	"This function append_to a (virtual) file.";
static PyObject *unitex_append_to_file(PyObject *self, PyObject *args);

PyObject *unitex_append_to_file(PyObject *self, PyObject *args) {
	char *path;
	PyObject *ustring;
	if (!PyArg_ParseTuple(args, "sU", &path, &ustring))
		return NULL;

	PyObject *bytes;
	char *content;
	Py_ssize_t length;

	bytes = PyUnicode_AsUTF8String(ustring);
	PyBytes_AsStringAndSize(bytes, &content, &length);

	unsigned int ret;
	ret = AppendUnitexFile(path, content, length);

	return Py_BuildValue("O", ret ? Py_False: Py_True);
}



static PyMethodDef unitex_methods[] = {
	/* Unitex Tool function */
	{"unitex_tool", unitex_tool, METH_VARARGS, unitex_tool_docstring},

	/* Persistence functions */
	{"unitex_load_persistent_dictionary", unitex_load_persistent_dictionary, METH_VARARGS, unitex_load_persistent_dictionary_docstring},
	{"unitex_load_persistent_fst2", unitex_load_persistent_fst2, METH_VARARGS, unitex_load_persistent_fst2_docstring},
	{"unitex_load_persistent_alphabet", unitex_load_persistent_alphabet, METH_VARARGS, unitex_load_persistent_alphabet_docstring},

	{"unitex_free_persistent_dictionary", unitex_free_persistent_dictionary, METH_VARARGS, unitex_free_persistent_dictionary_docstring},
	{"unitex_free_persistent_fst2", unitex_free_persistent_fst2, METH_VARARGS, unitex_free_persistent_fst2_docstring},
	{"unitex_free_persistent_alphabet", unitex_free_persistent_alphabet, METH_VARARGS, unitex_free_persistent_alphabet_docstring},

	{"unitex_is_persistent_dictionary", unitex_is_persistent_dictionary, METH_VARARGS, unitex_is_persistent_dictionary_docstring},
	{"unitex_is_persistent_fst2", unitex_is_persistent_fst2, METH_VARARGS, unitex_is_persistent_fst2_docstring},
	{"unitex_is_persistent_alphabet", unitex_is_persistent_alphabet, METH_VARARGS, unitex_is_persistent_alphabet_docstring},

	/* I/O functions */
	{"unitex_enable_stdout", unitex_enable_stdout, METH_NOARGS, unitex_enable_stdout_docstring},
	{"unitex_disable_stdout", unitex_disable_stdout, METH_NOARGS, unitex_disable_stdout_docstring},
	{"unitex_enable_stderr", unitex_enable_stderr, METH_NOARGS, unitex_enable_stderr_docstring},
	{"unitex_disable_stderr", unitex_disable_stderr, METH_NOARGS, unitex_disable_stderr_docstring},

	{"unitex_cp", unitex_cp, METH_VARARGS, unitex_cp_docstring},
	{"unitex_rm", unitex_rm, METH_VARARGS, unitex_rm_docstring},
	{"unitex_mv", unitex_mv, METH_VARARGS, unitex_mv_docstring},
	{"unitex_mkdir", unitex_mkdir, METH_VARARGS, unitex_mkdir_docstring},
	{"unitex_rmdir", unitex_rmdir, METH_VARARGS, unitex_rmdir_docstring},
	{"unitex_ls", unitex_ls, METH_VARARGS, unitex_ls_docstring},

	{"unitex_read_file", unitex_read_file, METH_VARARGS, unitex_read_file_docstring},
	{"unitex_write_file", unitex_write_file, METH_VARARGS, unitex_write_file_docstring},
	{"unitex_append_to_file", unitex_append_to_file, METH_VARARGS, unitex_append_to_file_docstring},

	{NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef unitex_module_def = {
	PyModuleDef_HEAD_INIT,
	"_unitex",
	unitex_docstring,
	-1,
	unitex_methods
};

PyMODINIT_FUNC PyInit__unitex(void) {
	PyObject *module = PyModule_Create(&unitex_module_def);

	if (module == NULL)
		return NULL;
	return module;
}
#else
PyMODINIT_FUNC init_unitex(void) {
	PyObject *module = Py_InitModule3("_unitex", unitex_methods, unitex_docstring);

	if (module == NULL)
		return;
}
#endif
