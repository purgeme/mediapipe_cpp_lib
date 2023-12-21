#!/usr/bin/python
import os
import shutil
import patch

current_dir = os.path.dirname(__file__)
mediapipe_dir = os.path.join(current_dir, 'mediapipe')

old_packet_src = os.path.join(mediapipe_dir, "mediapipe", "framework", "packet.h")
old_packet_dst = os.path.join(mediapipe_dir, "mediapipe", "framework", "packet.h.old")
packet_src = os.path.join(current_dir, "patch", "packet.h")
packet_dst = os.path.join(mediapipe_dir, "mediapipe", "framework", "packet.h")

library_files_src = os.path.join(current_dir, "src")
library_files_dst = os.path.join(mediapipe_dir, "mcl")

patch_path = os.path.join(current_dir, "patch")
patch_file = open(patch_path, "rb")

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

# Apply patch file
print("Applying patch file...")
os.chdir(mediapipe_dir)
pset = patch.fromfile(os.path.join(current_dir, "patch"))
pset.apply()
print("Patch applied!")

# Copy src files
print("\nCopying library code...")
copy2dir(library_files_src, library_files_dst)
print("Copied library code!")
