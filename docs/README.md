# Getting Started
After completing installation, read [First Game](first-game.md).

## Installation
Build the project:
```bash
make
```

Install system-wide:
```bash
sudo make install
```
> [!NOTE]
> Use `make install_local` for a local install

### Fix Shared Library Issues
If you have errors like
```
error while loading shared libraries
```

Add `/usr/local/lib` to the linker path:
```bash
cd /etc/ld.so.conf.d/
echo "/usr/local/lib" | sudo tee -a usrlocal.conf
```

Then refresh:
```bash
sudo ldconfig
```

## Compiling Your Game
```bash
g++ -std=c++20 -o game game.cc -lAsciiEngine
```
