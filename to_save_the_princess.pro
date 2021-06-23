TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG   += console precompile_header

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = pch.h

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
	LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
	LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        animationcomponent.cpp \
        editorstate.cpp \
        engine.cpp \
        gamestate.cpp \
        graphicssettings.cpp \
        gui.cpp \
        hitboxcomponent.cpp \
        main.cpp \
        mainmenustate.cpp \
        movementcomponent.cpp \
        pausemenu.cpp \
        player.cpp \
        settingstate.cpp \
        state.cpp \
        tile.cpp \
        tilemap.cpp \
        unit.cpp

HEADERS += \
	animationcomponent.h \
	editorstate.h \
	engine.h \
	gamestate.h \
	graphicssettings.h \
	gui.h \
	hitboxcomponent.h \
	mainmenustate.h \
	movementcomponent.h \
	pausemenu.h \
	pch.h \
	player.h \
	settingstate.h \
	state.h \
	tile.h \
	tilemap.h \
	unit.h

DISTFILES +=
