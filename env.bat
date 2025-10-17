
@echo off
REM Add TheRock install\bin to PATH for this session
set "NEW_PATH=C:\Users\azureuser\sources\.venv\Lib\site-packages\torch\lib;C:\Users\azureuser\sources\.venv\Lib\site-packages\_rocm_sdk_devel\lib;C:\Users\azureuser\sources\.venv\Lib\site-packages\_rocm_sdk_core\bin;C:\Users\azureuser\sources\.venv\Lib\site-packages\_rocm_sdk_core\lib\llvm\bin"

REM Prepend to PATH (so it takes priority)
set "PATH=%NEW_PATH%;%PATH%"

echo [INFO] PATH updated for this session:
echo %PATH%
