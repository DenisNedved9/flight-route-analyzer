Flight Route Analyzer
A lightweight C console tool for parsing aeronautical waypoints and analyzing flight route metrics from telemetry data.

Problem & Purpose
Aviation and flight planning systems require precise parsing and distance analysis of waypoint coordinates from raw text inputs. Manually calculating path metrics or using unsafe fixed-size arrays is inefficient and prone to memory failures. 

This tool solves this challenge by automatically:
- Parsing telemetry data: Reads waypoint names and 2D coordinates from structured input files.
- Ensuring memory safety: Utilizes dynamic memory allocation (`malloc`/`free`) with strict error handling to support arbitrary dataset sizes safely.
- Generating route reports: Computes Euclidean leg distances, total path length, and identifies the longest flight segment, outputting clean diagnostic summaries to the console and a report file.
