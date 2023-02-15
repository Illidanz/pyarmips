import os
from distutils.core import setup, Extension

with open("README.md", "r") as fh:
    long_description = fh.read()

if not os.name == 'nt':
    EXTRA_COMPILE_ARGS = ["-std=c++17"]
    LIBRARIES = []
else:
    EXTRA_COMPILE_ARGS = ["/std:c++17"]
    LIBRARIES = ["Shell32"]

INCLUDES = ["armips", "armips/ext/filesystem/include", "armips/ext/tinyformat"]

sources = ["pyarmips.cpp"]
for dir in ["Archs", "Archs/ARM", "Archs/MIPS", "Archs/SuperH", "Commands", "Core", "Core/ELF", "Parser", "Util"]:
    for file in os.listdir("armips/" + dir):
        if file.endswith(".cpp"):
            sources.append("armips/" + dir + "/" + file)

def main():
    setup(name="pyarmips",
          version="0.11.0",
          author="Illidan",
          description="Python interface for armips.",
          long_description=long_description,
          long_description_content_type="text/markdown",
          url="https://github.com/Illidanz/pyarmips",
          classifiers=[
              "Programming Language :: Python :: 3",
              "License :: OSI Approved :: MIT License",
          ],
          ext_modules=[Extension("pyarmips", sources, include_dirs=INCLUDES, libraries=LIBRARIES, extra_compile_args=EXTRA_COMPILE_ARGS)]
        )

if __name__ == "__main__":
    main()
