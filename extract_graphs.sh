#!/bin/bash
# Extract mediapipe graphs from downloaded mediapipe repo and place them in mediapipe_graphs directory

mkdir mediapipe_graphs
cp -r mediapipe/mediapipe/graphs/* mediapipe_graphs/