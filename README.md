Python Wrapper for the KUtrace Userspace Library
================================================

This project provides a way to interact with the [KUtrace](https://github.com/dicksites/KUtrace)
Linux Kernel/Userspace tracing facility. Specifically, it provides access to
all of the top-level functions exposed by the `kutrace_lib` library.


Prerequisites
=============

Prior to using this library you must be running a version of the Linux kernel
with the KUtrace patches applied.
[See the instructions in the KUtrace repo for this.](https://github.com/dicksites/KUtrace/blob/master/linux_patches_installation_guide.pdf)

Second, you must have built and loaded the KUtrace kernel module. After setting
up the patched kernel, download the [module sources](https://github.com/dicksites/KUtrace/blob/master/loadable-module.tar.gz),
extract and build the module, and then load it.

This project requires Python 3.


Installation
============

Clone this repository, `cd` into it, and run `python setup.py install`.
Afterwards, you should be able to run `python basic_test.py`, which, if
successful, produces `basic_test.trace`.


Usage
=====

To use the library, you can `import kutrace` in Python:
```python
import kutrace

if not kutrace.test():
    print("The KUtrace kernel module is too old or not loaded.")
    exit()

# Start recording a trace. Requires a name for the calling process.
kutrace.go("python")

# Add a 'mark' of up to 6 alphanumeric characters to the trace
kutrace.mark_a("start")
do_some_work()
kutrace.mark_b("end")

# Stop tracing, and save the trace to the named file. The file can then be
# processed with the normal KUtrace tools.
kutrace.stop("my_trace.trace")
```

If you want to see a full list of available functions:
```python
import kutrace
help(kutrace)
```
All functions share the same name and arguments as their C++ counterparts.

