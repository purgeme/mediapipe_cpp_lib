#!/usr/bin/python
import os
import shutil
import subprocess
import requests
import patch
from zipfile import ZipFile

current_dir = os.path.dirname(__file__)
project_dir = os.path.join(current_dir, '..')

graphs_src = os.path.join(project_dir, "mediapipe_graphs")
graphs_dst = os.path.join(current_dir, "mediapipe_graphs")

api_src = os.path.join(project_dir, "src", "gmod_api.h")
api_dst = os.path.join(current_dir, "gmod_api.h")

models_src = os.path.join(project_dir, "mediapipe_models")
models_dst = os.path.join(current_dir, "mediapipe_models")

import_files_src = os.path.join(project_dir, "import_files")
import_files_dst = os.path.join(current_dir, "mediapipe")

protobuf_version = "3.19.1"
protobuf_dst = current_dir # Later moved to protobuf

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

print("\n##########")
print("Downloading protobuf...")
if os.path.isfile(os.path.join(current_dir, "protobuf-cpp-"+protobuf_version+".zip")):
    print("Protobuf is already downloaded!")
else:
    response = requests.get("https://github.com/protocolbuffers/protobuf/releases/download/v"+protobuf_version+"/protobuf-cpp-"+protobuf_version+".zip")
    file = open("protobuf-cpp-"+protobuf_version+".zip", "wb")
    file.write(response.content)
    file.close()
if os.path.isdir(os.path.join(protobuf_dst, "protobuf")):
    print("Protobuf is already extracted!")
else:
    print("Extracting protobuf...")
    with ZipFile("protobuf-cpp-"+protobuf_version+".zip", 'r') as zip:
        print("Extracting to: " + protobuf_dst)
        zip.extractall(protobuf_dst)
        os.rename(os.path.join(protobuf_dst, "protobuf-"+protobuf_version), os.path.join(protobuf_dst, "protobuf"))
print("Protobuf placed!")
print("##########")

# Copy api file
print("\nCopying api file...")
copy2dir(graphs_src, graphs_dst)
shutil.copyfile(api_src, api_dst)
print("Copied api file!")

# Copy graph files
print("\nCopying graph files...")
copy2dir(graphs_src, graphs_dst)
print("Copied graph files!")

# Copy model files
print("\nCopying model files...")
copy2dir(models_src, models_dst)
print("Copied model files!")

# Copy import files
print("\nCopying import files...")
copy2dir(import_files_src, import_files_dst)
print("Copied import files!")

# Build project
build_cmd = ['g++','-o','demo','demo.cpp','-I./protobuf/src/','-L../library/','-lgmod']
if subprocess.run(build_cmd).returncode != 0:
    print("Error building demo!")
    quit()

print("Demo built successfully!")

inp = input ("Do you want to run the demo? [n/Y]: ")
if inp != "n" or inp != "N":
    subprocess.run(["./demo"])
