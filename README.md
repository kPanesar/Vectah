# Vectah
**Cross Platform Tool for viewing and organizing vector based icons.**

There are currently no tools (as far as I am aware) for viewing and managing a large number of SVG icons on Windows and Linux. Svgsus exists but only on the Mac platform despite it being built on the Electron Framework. Vectah aims to be a free and open-source tool that can be used by artists and developers across multiple platforms.

Here's a preliminary concept of what Vectah may look like:


![](https://i.imgur.com/mmDOYAh.jpg)

#### Building on Linux (Ubuntu 18.04)

```console
sudo apt install libgtkmm-3.0-dev librsvg2-dev cmake
cd Vectah && mkdir build
cd build && cmake ../
```