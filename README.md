# pybind11-template

## Requirements

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
