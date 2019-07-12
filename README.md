<h3 align="center">El-MAVEN</h3>
<p align="center">An intuitive, opensource LC-MS data processing engine </p>
<p align="center">from </p>
<p align="center">
  <a href="http://www.elucidata.io"> 
	<img src="http://elucidata.io/static/images/elucidata-logo-with-text.svg">
  </a>

## Build Status
[![Build Status](https://travis-ci.org/ElucidataInc/ElMaven.svg?branch=develop)](https://travis-ci.org/ElucidataInc/ElMaven)
[![Build status](https://ci.appveyor.com/api/projects/status/hj92puovbucth7o1/branch/develop?svg=true)](https://ci.appveyor.com/project/ElucidataInc/elmaven/branch/develop)
[![codecov](https://codecov.io/gh/ElucidataInc/ElMaven/branch/develop/graph/badge.svg)](https://codecov.io/gh/ElucidataInc/ElMaven)


## Digital Object Identifier (DOI) 
[![DOI](https://zenodo.org/badge/70220005.svg)](https://zenodo.org/badge/latestdoi/70220005)

## Table of contents
- [Download](#download)
- [Build](#build-from-source)
- [El-MAVEN features](#el-maven-features)
- [Bugs and feature requests](#bugs-and-feature-requests)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [Contributors](#contributors)
- [References](#references)
- [Acknowledgment](#acknowledgment)
- [Copyright and license](#copyright-and-license)

## Download

El-MAVEN installers are available for Windows (7, 8, 10) and Mac.
Download [El-MAVEN](https://elucidatainc.github.io/ElMaven/) latest version or daily build for your preferred environment.

## Build from source

Contributers can build El-MAVEN on Windows, Ubuntu or Mac systems by following these instructions. Users are recommended to download the installers provided on the El-MAVEN website.
- Setting up Environment
  - [Windows](#windows)
  - [Ubuntu](#ubuntu)
  - [Mac](#mac)
- [Getting the source code](#source-code)
- [Build](#build)


#### <a name=setup> </a> Set up Environment(64 bit platforms only)
1. ##### Windows

- Download [MSYS2](http://www.msys2.org/) installer and follow the installation instructions provided on their website.
- Download OpenSSL package using https://indy.fulgan.com/SSL/openssl-1.0.2r-x64_86-win64.zip
- Extract the contents of OpenSSL package in `/c/msys64/mingw64/bin`
- NOTE: To verify whether the above two steps have been executed correctly make sure you have libeay32.dll and ssleay32.dll inside `/c/msys64/mingw64/bin/`

    #####  _Following commands needs to be executed from msys2 shell_
- `pacman --force -Sy`
- `pacman --force -Syu`
- `pacman --force -Su`
- `pacman --force -Sy base-devel msys2-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-qt5 mingw64/mingw-w64-x86_64-hdf5 mingw64/mingw-w64-x86_64-netcdf mingw64/mingw-w64-x86_64-boost msys/git mingw-w64-x86_64-curl`
- `export PATH=/c/msys64/mingw64/bin/:$PATH`. It will be benefical if this change is made permanent. To do so, you will have to make changes
in the .bashrc file. It can be achieved by either manually editing the .bashrc file or via command line.

  **For manually editing:**
    - Open .bashrc(located in C:\msys64\home\USERNAME\\) in any text editor
    - Add `export PATH=/c/msys64/mingw64/bin/:$PATH` at the end of the file
    - Save and exit the editor
    - From msys2 shell: `source ~/.bashrc`

  **For editing the file via command line:**
    - `echo export PATH=/c/msys64/usr/bin/:/c/msys64/mingw64/bin/:$PATH > ~/.bashrc`
    - `source ~/.bashrc`


2. ##### Ubuntu

- `sudo apt-get update`
- `sudo apt-get install g++`
- `sudo apt-get install libsqlite3-dev libboost-all-dev lcov libnetcdf-dev`
    ###### _Execute the command below only if Ubuntu <=16.04_ (Required for installing Qt >=5.7)
- `sudo add-apt-repository 'deb http://archive.neon.kde.org/user/lts/ xenial main binary-amd64'`

    ###### _Ubuntu 18.04 and above provides Qt >=5.7 and therefore we do not need to add the repository_
- `sudo apt-get install qt5-qmake qtbase5-dev qtscript5-dev qtdeclarative5-dev libqt5multimedia5`
- `sudo apt-get install libqt5multimedia5-plugins qtmultimedia5-dev libqt5webkit5-dev`

3. ##### Mac

- Install Xcode from App store

    ###### _Use Terminal for exectuing the following instructions_
- `sudo xcodebuild -license accept`
- `xcode-select --install`
- `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
- `brew install boost`
- `brew install qt`
- `brew install llvm@6`
- `brew install netcdf`

- `cd ~`

    ###### _Not required if the file already exists_
- `touch .bash_profile`

    ###### _e.g. /LLVM_DIR/ = /usr/local/opt/llvm@6/_
    ###### _e.g /QT_DIR/= /usr/local/opt/qt/_

- `echo "export PATH=/QT_DIR/bin:/LLVM_DIR/bin/:$PATH" >> .bash_profile`

- `echo "export LDFLAGS="-L/QT_DIR/lib -L/LLVM_DIR/lib -Wl,-rpath,/LLVM_DIR/lib" >> .bash_profile`

- `echo "export CPPFLAGS+="-I/QT_DIR/include -I/LLVM_DIR/include  -I/LLVM_DIR/c++/v1/" >> .bash_profile`

- `source .bash_profile`

_To make sure the environment has ben setup correctly make sure the correct version of libraries have been installed by issuing the following commands_
- Qt version should be >= 5.7: `qmake -v`
- Boost should be >= 1.58
  - On ubuntu : `apt-cache policy libboost-all-dev`
  - On Mac: `brew info boost`
  - On Windows: `pacman -Qi mingw64/mingw-w64-x86_64-boost`

#### <a name=source-code> </a> Getting the source code
- Change the directory to where you want to clone the code
- `git clone https://github.com/ElucidataInc/ElMaven.git`


#### <a name="build"> </a> Build
- `cd ElMaven`
- For release builds : `qmake CONFIG+=release build.pro`
- For debug builds : `qmake CONFIG+=debug build.pro`
- `make -j4`
- If you want to run tests and want to do a clean build, you can skip the above steps and just run the command from ElMaven directory: `./run.sh`
- Run El-MAVEN: `bin/El-MAVEN`
### Switching versions

Users can switch between versions once they have compiled El-MAVEN successfully on their system. Follow these steps to pull a specific release:

- Choose the version you wish to install from the list of releases. (We recommend the version tagged "Latest release". Pre-releases are not stable and should be avoided)
- Find the version tag (v0.2.x, 0.1.x, etc) on the left of release notes.
- Open your terminal and move to the installation folder
- Give the following commands in the terminal:  
`cd ElMaven`  
`./uninstall.sh` (to uninstall your current version)  
`git checkout develop`  
`git pull`  
`git checkout v0.x.y` (Eg. v0.1.5)
- Build the new version using the following command:

For Windows and Ubuntu: 
`./run.sh`

For Mac:  
`source ~/.bash_profile`

`qmake CONFIG+=debug -o Makefile build.pro`

`make -j4`

## El-MAVEN features

[Maven](http://genomics-pubs.princeton.edu/mzroll/index.php) and [El-MAVEN](https://elucidatainc.github.io/ElMaven/) share following features:
* Multi-file chromatographic aligner
* Peak-feature detector
* Isotope and adduct calculator
* Formula predictor
* Pathway visualizer
* Isotopic flux animator

El-MAVEN is robust, faster and with more user friendly features compared to Maven.

## Bugs and feature requests

Existing bugs and feature requests can be found on [El-MAVEN github issue page](https://github.com/ElucidataInc/ElMaven/issues). Please search existing bugs and feature requests before you file a bug or request a feature.

## Documentation

El-MAVEN user documentation can be found on the [GitWiki](https://github.com/ElucidataInc/ElMaven/wiki) page.

## Contributing

You are welcome to contribute. Please go through our [contributing guidelines](https://github.com/ElucidataInc/ElMaven/blob/develop/CONTRIBUTING.md) and [code of conduct](https://github.com/ElucidataInc/ElMaven/blob/develop/CODE_OF_CONDUCT.md). These guidelines include directions for coding standards, filing issues and development guidelines.

Pull requests must include relevant unit tests. All the functional features are to be tested before committing the code. When
contributing C++ code, please make sure that it follows the [style guide](https://github.com/ElucidataInc/ElMaven/blob/develop/STYLE_GUIDE.md) for this project.

## Contributors

*	[Maven team at Princeton University](http://genomics-pubs.princeton.edu/mzroll/index.php)
*	[Eugene Melamud](https://www.calicolabs.com/team-member/eugene-melamud/)
*	[Victor Chubukov](https://github.com/chubukov)
*	[George Sabu](https://github.com/GeorgeSabu)
*	[Sahil](https://github.com/sahil21)
*	[Raghav Sehgal](https://github.com/Raghavdata)
*	[Shubhra Agrawal](https://github.com/shubhra-agrawal)
*	[Raghuram Reddy](https://github.com/r-el-maya)
*	[Rishabh Gupta](https://github.com/rish9511)
*	[Pankaj Kumar](https://github.com/IpankajI)
*	[Rahul Kumar](https://github.com/rkdahmiwal)
*	[Giridhari](https://github.com/Giridhari013)
*	[Kiran Varghese](https://github.com/kiranvarghese2)
*	[Naman Gupta](https://github.com/naman)
*	[Saiful B. Khan](https://github.com/saifulbkhan)


## References

To understand [Maven](http://genomics-pubs.princeton.edu/mzroll/index.php) and [El-MAVEN](https://elucidatainc.github.io/ElMaven/) workflows and features, please refer to following literature on Maven:

* [Metabolomic Analysis and Visualization Engine for LC-MSData](http://pubs.acs.org/doi/abs/10.1021/ac1021166), Eugene Melamud, Livia Vastag, and Joshua D. Rabinowitz, Analytical Chemistry 2010 82 (23), 9818-9826
* [LC-MS Data Processing with MAVEN: A Metabolomic Analysis and Visualization Engine](http://onlinelibrary.wiley.com/doi/10.1002/0471250953.bi1411s37/abstract), Clasquin, M. F., Melamud, E. and Rabinowitz, J. D. 2012, Current Protocols in Bioinformatics. 37:14.11.1-14.11.23.

## Acknowledgment

El-MAVEN would not have been possible without the unwavering support, constant feedback and financial support from [Agios](http://www.agios.com/). El-MAVEN thanks the metabolomics community for its immense contribution in taking the tool forward and making it a great success.

## Copyright and license

Code and documentation copyright  2017 [Elucidata Inc](http://www.elucidata.io/). Code released under the [GPL v2.0](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html). Documentation is released under [MIT license](https://opensource.org/licenses/MIT).
