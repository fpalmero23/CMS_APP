set PROJECT_NAME=MainApp
set BUILD_TYPE=Debug
set TEST=BankUnitTest
cd $CURRENT_DIR
rmdir /s /q build
cmake -E make_directory build
cd build
cmake ..
cmake --build .
cd %BUILD_TYPE%
start %TEST%.exe