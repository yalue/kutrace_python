from distutils.core import setup, Extension

kutrace_module = Extension(
    "kutrace", sources=["kutrace_python.cc", "kutrace_lib/kutrace_lib.cc"]
)
description = "An interface to the KUtrace userspace library."
setup(name="KUtrace", version="1.0", description=description,
    ext_modules=[kutrace_module])

