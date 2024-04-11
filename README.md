# pybind11-template

## How to install

### Windows

1. Install Python
   1. Install from [here](https://pythonlinks.python.jp/en/index.html)
   2. Install a specific version: `winget install Python.Python3.10`
2. Install C++ build tools

    ```powershell
    # allow .ps1 scripts
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

    # for MSVC
    winget install Microsoft.VisualStudio.2022.BuildTools

    # for GCC
    Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
    # Refresh shell if you needed
    # cf. https://qiita.com/javacommons/items/49d1503c8e76dbaa0fb0
    scoop install mingw-winlibs

    # Other tools
    winget install Git.Git
    ```

3. Create virtual environment

    ```powershell
    # Use Python 3.10
    py -3.10 -m venv .venv
    .\.venv\Scripts\Activate.ps1
    which python
    ```

4. Install this library: `pip install -e .`

If you need this binding only, do these:

- For MSVC

    ```powershell
    cmake -G "Visual Studio 17 2022" -A "x64" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -B build -S .
    cmake --build build --config Release
    ```

- For GCC

    ```powershell
    cmake -G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B build -S .
    cmake --build build --config Release
    ```

### Ubuntu

1. Install Python

    ```bash
    # introduce add-apt-repository
    sudo apt install -y software-properties-common
    # introduce Python packages
    sudo add-apt-repository ppa:deadsnakes/ppa -y
    # update package list
    sudo apt update 

    sudo apt install -y python3.10 python3.10-dev python3.10-venv   

    # Use Python3.10 as the highest priority
    sudo update-alternatives --install /usr/bin/python python "/usr/bin/python3.10" 1
    # Check the version
    python --version
    ```

2. Install C++ build tools: `sudo apt-get install -y build-essential gdb cmake git`
3. Create virtual environemnt

    ```bash
    python -m venv .venv
    source ./.venv/bin/activate
    which python
    ```

4. Install this library: `pip install -e .`

If you need this binding only, do these:

```bash
cmake -B build -S .
cmake --build build --config Release
```

## How to build wheel

```shell
# source code only
python setup.py sdist
# build package (`pip install wheel` needed)
python setup.py bdist_wheel
```

## Notes

- In windows environemnts, Japanese character cannot be used for descriptions of pybind11 modules.
- Older version for glog and Eigen3 cannot be used to build in Windows environments.
