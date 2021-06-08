QT -= core gui
TEMPLATE = app
QT += charts
CONFIG += console
SOURCES += \
    drawData.cpp \
    main.cpp \
    polyFit.cpp
INCLUDEPATH += C:\src\vcpkg\installed\x86-windows\include\eigen3
target.path = $$[QT_INSTALL_EXAMPLES]/charts/linechart
INSTALLS += target

HEADERS += \
    drawData.h \
    polyFit.h
