set /p VERSION=<version
set OUTPUT_DIR=build-cmake-gcc
set OUTPUT_NAME=ClientServer

cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" -B %OUTPUT_DIR%

cd %OUTPUT_DIR%

mingw32-make

md %OUTPUT_NAME%-%VERSION%

move %OUTPUT_NAME%-Release-%VERSION%.exe %OUTPUT_NAME%-%VERSION%\%OUTPUT_NAME%-Release-%VERSION%.exe