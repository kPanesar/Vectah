# Vectah
**Cross Platform Tool for viewing and organizing vector based icons.**

There are currently no tools (as far as I am aware) for viewing and managing a large number of SVG icons on Windows and Linux. Svgsus exists but only on the Mac platform despite it being built on the Electron Framework. Vectah aims to be a free and open-source tool that can be used by artists and developers across multiple platforms.

Here's a preliminary concept of what Vectah may look like:


![](https://i.imgur.com/mmDOYAh.jpg)

### Building on Linux (Ubuntu 18.04)

#### Install GCC 8
For C++17 functionality, GCC 8 is required. Install and set it up to be the default version:

```shell
sudo apt install gcc-8 && g++-8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8
```
To see a list of alternatives for gcc run `sudo update-alternatives --config gcc`. The output should look like this:
```shell
There are 2 choices for the alternative gcc (providing /usr/bin/gcc).

  Selection    Path            Priority   Status
------------------------------------------------------------
* 0            /usr/bin/gcc-8   800       auto mode
  1            /usr/bin/gcc-7   700       manual mode
  2            /usr/bin/gcc-8   800       manual mode

Press <enter> to keep the current choice[*], or type selection number: 
```

#### Install required libraries and build
```shell
sudo apt install libgtkmm-3.0-dev librsvg2-dev cmake
cd Vectah && mkdir build
cd build && cmake ../
```
