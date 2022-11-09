#!/usr/bin/python
import os
import platform
import subprocess
import shutil

# Variables
current_dir = os.path.dirname(__file__)
mediapipe_dir = os.path.join(current_dir, 'mediapipe')

library_name = 'libgmod.so'
library_src = os.path.join(mediapipe_dir, 'bazel-bin', 'cpp_library')
library_dst = os.path.join(current_dir, 'library')

import_files_src = os.path.join(mediapipe_dir, 'bazel-bin', 'mediapipe')
import_files_dst = os.path.join(current_dir, 'import_files')

build_prefix = ['bazel', 'build', '-c', 'opt'] 
build_suffix = ['cpp_library:gmod']
build_options = []
build_cmd = []

def copy2dir( src, dst ):
    if os.path.isdir(dst):
        inp = input ("Destination already exists, do you wish to replace it ? [N/y]: ")
        if inp == "y" or inp == "Y":
            shutil.rmtree(dst)
            shutil.copytree(src, dst)
            return
        else:
            return
    else:
        shutil.copytree(src, dst)

def _get_input(string, default_yes = False):
    inp = input(string)
    if default_yes:
        return (inp != 'N' and inp != 'n')
    else:
        return (inp == 'Y' or inp == 'y')

def _setup_build_options():
    build_options = []
    # Setup build command
    if _get_input('Do you wish to build with GPU support ? [N/y]: ', False):
        if platform.system() == 'Windows':
            # Windows does not support GPU yet
            print('GPU builds are not supported on windows!')
            exit()
        else:
            build_options += ['--copt', '-DMESA_EGL_NO_X11_HEADERS', '--copt', '-DEGL_NO_X11']
    else:
        build_options += ['--define', 'DISABLE_MEDIAPIPE_GPU=1']
        if platform.system() == 'windows':
            build_options += ['--action_envs', 'PYTHON_BIN_PATH=C://Python//python.exe']
    return build_options

def _build_library(cmd):
    # Build library
    os.chdir(mediapipe_dir)
    print("Building library...")
    return subprocess.run(cmd, shell=True)

def _copy_library():
    # Copy library
    print("Copying library...")
    os.chdir(current_dir)
    if os.path.isdir(library_dst) == False:
        os.mkdir(library_dst)
    shutil.copyfile(os.path.join(library_src, library_name), os.path.join(library_dst, library_name))


def _copy_import_files():
    # Copy import files
    save_import_files = input("Do you want to copy the import files to import_files folder ? [Y/n]:")
    if save_import_files != "N" and save_import_files != "n":
        print("Copying import files...")
        copy2dir(import_files_src, import_files_dst)

build_options = _setup_build_options()

build_cmd = build_prefix + build_options + build_suffix


if _build_library(build_cmd).returncode != 0:
    print("Error building library...!!!")
else:
    _copy_library()
    _copy_import_files()