#!/usr/bin/python
import os
import shutil

current_dir = os.path.dirname(__file__)

mediapipe_graphs_src =  os.path.join(current_dir, "mediapipe/mediapipe/graphs")
mediapipe_graphs_dst =  os.path.join(current_dir, "mediapipe_graphs")

print("##########")
if os.path.isdir(mediapipe_graphs_dst):
    inp = input("Graphs folder already exists, do you wish to replace it ? [y/N]: ")
    if inp == "y" or inp == "Y":
        os.rmdir(mediapipe_graphs_dst)
        print("Copying graph files...")
        shutil.copytree(mediapipe_graphs_src, mediapipe_graphs_dst)
print("##########")