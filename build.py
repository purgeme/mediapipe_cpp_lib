#!/usr/bin/python
import os
import subprocess
import sys
import shutil

# Variables
mediapipe_dir = os.path.join(os.path.dirname(__file__), 'mediapipe')

library_name = "libgmod.so"
library_src = os.path.join(mediapipe_dir, "bazel-bin/cpp_library")
library_dst = os.path.join(os.path.dirname(__file__), 'library')

import_files_src = os.path.join(mediapipe_dir, "bazel-bin/mediapipe")
import_files_dst = os.path.join(os.path.dirname(__file__), 'import_files')

bazel_build_cmd = ["bazel", "build", "-c", "opt", "--define", "DISABLE_MEDIAPIPE_GPU=1", "cpp_library:gmod"]

# Build library
print("##########")
os.chdir(mediapipe_dir)
print("Building library...")
subprocess.run(bazel_build_cmd)
print("##########")

# Copy library
print("\n##########")
os.chdir(os.path.dirname(__file__))
if os.path.isdir(library_dst) == False:
    os.mkdir(library_dst)
print("Copying library...")
shutil.copyfile(library_src+"/"+library_name, library_dst+"/"+library_name)
print("##########")

# Copy import files
print("\n##########")
save_import_files = input("Do you want to copy the import files to import_files folder ? [Y/n]:")
if save_import_files != "N" and save_import_files != "n":
    if os.path.isdir(import_files_dst) == False:
        print("Copying import files...")
        shutil.copytree(import_files_src, import_files_dst)
    else:
        inp = input("import_files directory already exists. Do you wish to replace it [y/N]:")
        if inp == "Y" or inp == "y":
            print("Copying import files...")
            os.removedirs(import_files_dst)
            shutil.copytree(import_files_src, import_files_dst)
print("##########")
