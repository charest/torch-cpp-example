# ROCm on Windows with Torch

Initialize python virtual environment:
```
python -m venv .venv
.venv\Scripts\Activate.bat
```
Install rocm and torch:
```
python -m pip install --index-url https://rocm.nightlies.amd.com/v2/gfx110X-dgpu/ "rocm[libraries,devel]==7.0.0rc20250908"
python -m pip install --index-url https://rocm.nightlies.amd.com/v2/gfx110X-dgpu/ --pre torch==2.9.0a0+rocm7.0.0rc20250908 torchaudio==2.8.0a0+rocm7.0.0rc20250908 torchvision==0.24.0a0+rocm7.0.0rc20250908
```
Load the rocm_sdk module to kick off init scripts:
```
python -m rocm_sdk path --root
```
Clone repo and build
```
git clone git@github.com:charest/torch-cpp-example

cd torch-cpp-example

cmake -B build -GNinja . -DCMAKE_PREFIX_PATH=.venv\Lib\site-packages\_rocm_sdk_devel;.venv\Lib\site-packages\torch -DCMAKE_HIP_PLATFORM=amd -DCMAKE_HIP_ARCHITECTURES=gfx1101 -DCMAKE_CXX_COMPILER=hipcc.exe -DCMAKE_C_COMPILER=hipcc.exe -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_BUILD_TYPE=Release

cmake --build build
```
Run test:
```
build\torch_test.exe
```
Expected output:
```
Creating tensor...
Created data tensor
```
Actual output:
```
Creating tensor...
```
