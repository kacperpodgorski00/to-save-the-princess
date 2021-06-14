TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
	LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
	LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        button.cpp \
        engine.cpp \
        gamestate.cpp \
        main.cpp \
        mainmenustate.cpp \
        movementcomponent.cpp \
        player.cpp \
        state.cpp \
        unit.cpp

HEADERS += \
	button.h \
	engine.h \
	gamestate.h \
	mainmenustate.h \
	movementcomponent.h \
	player.h \
	state.h \
	unit.h

DISTFILES +=
