#!/usr/bin/python
import os
import subprocess
import sys
import shutil
import patch

mediapipe_dir = os.path.join(os.path.dirname(__file__), 'mediapipe')

old_packet_src = os.path.join(mediapipe_dir, "mediapipe/framework/packet.h")
old_packet_dst = os.path.join(mediapipe_dir, "mediapipe/framework/packet.h.old")
packet_src = os.path.join(os.path.dirname(__file__), "patch/packet.h")
packet_dst = os.path.join(mediapipe_dir, "mediapipe/framework/packet.h")

library_files_src = os.path.join(os.path.dirname(__file__), "src")
library_files_dst = os.path.join(mediapipe_dir, "cpp_library")

patch_file = open(os.path.dirname(__file__)+"/patch/0001-mediapipe_module.patch", "rb")

# Apply patch file
print("##########")
print("Applying patch file...")
os.chdir(mediapipe_dir)
pset = patch.fromfile(mediapipe_dir+"/../patch/0001-mediapipe_module.patch")
pset.apply()
print("Patch applied!")
print("##########")

# Copy packet.h file
print("\n##########")
print("Replacing packet.h file...")
shutil.copyfile(old_packet_src, old_packet_dst)
shutil.copyfile(packet_src, packet_dst)
print("packet.h replaced!")
print("##########")

# Copy src files
print("\n##########")
print("Copying library code...")
shutil.copytree(library_files_src, library_files_dst)
print("Copied library code!")
print("##########")