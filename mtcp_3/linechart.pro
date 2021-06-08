QT -= core gui
TEMPLATE = app
QT += charts
CONFIG += console
SOURCES += \
    drawData.cpp \
    main.cpp \
    polyFit.cpp

# Modify the next line to include your own Eigen library.
INCLUDEPATH += C:\src\vcpkg\installed\x86-windows\include\eigen3
INSTALLS += target

HEADERS += \
    drawData.h \
    polyFit.h
