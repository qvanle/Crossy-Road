echo @off
cls 
cmake -S src/ -B build/ -DCMAKE_BUILD_TYPE=Debug  -G "Ninja" 
pause
ninja -C build
pause
.\build\CLM
