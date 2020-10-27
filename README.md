# SCalculator
A lightweight Gtkmm calculator

## How to install ?

### Using CMAKE

#### Cloning the repository
Clone the repository using:

`git clone https://github.com/Spounka/SCalculator.git`

#### Building
change to SCalculator directory then run:

`cmake -B build/release -DCMAKE_BUILD_TYPE=Release`
then build using whatever build system your OS uses, `make` or `qmake` or Windows equivalent

### Using PKGBUILD
If you're on ArchLinux, make an empty directory, cd to it then run:

`curl -o PKGBUILD.spounka https://raw.githubusercontent.com/Spounka/SCalculator/main/PKGBUILD`

`makepkg -sci`
