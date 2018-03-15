cmake_minimum_required(VERSION 3.8)
project(opengl7)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_PREFIX_PATH "/Applications/Qt/5.10.1/clang_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCE_FILES
        main.cpp MainWindow.cpp MainWindow.h GLWidget.cpp GLWidget.h DicomUtils.h DicomUtils.cpp filters/SepiaFilter.cpp filters/SepiaFilter.h Shader.cpp Shader.h utils.h filters/BlurFilter.cpp filters/BlurFilter.h filters/BlueFilter.cpp filters/BlueFilter.h filters/RedFilter.cpp filters/RedFilter.h filters/GreenFilter.cpp filters/GreenFilter.h utils.cpp FiltersPool.cpp FiltersPool.h filters/GammaFilter.cpp filters/GammaFilter.h filters/Original.cpp filters/Original.h filters/AberrationFilter.cpp filters/AberrationFilter.h filters/Emboss.cpp filters/Emboss.h filters/ReflectionFilter.cpp filters/ReflectionFilter.h filters/SharpenFilter.cpp filters/SharpenFilter.h filters/ThresholdingFilter.cpp filters/ThresholdingFilter.h filters/GrayscaleFilter.cpp filters/GrayscaleFilter.h filters/DistractionFilter.cpp filters/DistractionFilter.h dialogs/ThresholdingDialog.cpp dialogs/ThresholdingDialog.h dialogs/GammaDialog.cpp dialogs/GammaDialog.h filters/ColorBalance.cpp filters/ColorBalance.h dialogs/ColorBalanceDialog.cpp dialogs/ColorBalanceDialog.h filters/Ripple.cpp filters/Ripple.h dialogs/RippleDialog.cpp dialogs/RippleDialog.h filters/Kernel.cpp filters/Kernel.h dialogs/KernelDialog.cpp dialogs/KernelDialog.h filters/Canny.cpp filters/Canny.h filters/Lap.cpp filters/Lap.h dialogs/CannyDialog.cpp dialogs/CannyDialog.h)

INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(lib)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(OpenGL)
find_package(GLUT)
find_package(OpenCV REQUIRED )

add_executable(opengl7 ${SOURCE_FILES})
qt5_use_modules(opengl7 Widgets OpenGL)
target_link_libraries(opengl7 ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${OPENCV_LIBRARIES} imebra)