
NAME := Engine.a
FANCY_NAME := Engine

################################################################

DIR_SRC := src/
DIR_OBJ := obj/

################################################################

FILES := \

################################################################

FILES += \
	PolyGon/PolyGon.cpp \
\
	PolyGon/Graphics/Full/Main/Data.cpp \
	PolyGon/Graphics/Full/Main/Layout.cpp \
	PolyGon/Graphics/Full/ShaderLayout.cpp \
\
	PolyGon/Graphics/Wire/Main/Layout.cpp \
	PolyGon/Graphics/Wire/ShaderLayout.cpp \
\
	PolyGon/InstanceManager.cpp \
	PolyGon/ObjectData.cpp \
	PolyGon/Manager.cpp \
	PolyGon/Object.cpp \

################################################################

FILES += \
	PolyHedra/Data.cpp \
	PolyHedra/PolyHedra.cpp \
	PolyHedra/FileCollection.cpp \
	PolyHedra/Parser.cpp \
	PolyHedra/Generate.cpp \
\
	PolyHedra/Skin/Data.cpp \
	PolyHedra/Skin/Skin.cpp \
	PolyHedra/Skin/Parsing.cpp \

################################################################

#FILES += \
#	Wavefront/OBJ.cpp \
#	Wavefront/Main/Data.cpp \
#	Wavefront/Main/Buffer.cpp \
#	Wavefront/Simple3D/BufferArray.cpp \
#	Wavefront/Simple3D/Shader.cpp \
#	Wavefront/MTL.cpp \

################################################################

FILES += \
	FrameTime.cpp \
	Window.cpp \
	Debug.cpp \

################################################################

LIBRARYS  := $(NAME)  ValueType/ValueType.a Generics/Generics.a FileManager/FileManager.a OpenGL/OpenGL.a Display/Display.a Graphics/Graphics.a User/User.a  ../OpenGL/include
INCLUDES  := include/ ValueType/include     Generics/include    FileManager/include       OpenGL/include  Display/include   Graphics/include    User/include ../OpenGL/include
ARGUMENTS := -D ENGINE_DIR='"$(shell pwd)"'

################################################################

OTHER_LIST := ValueType/ValueType.a Generics/Generics.a FileManager/FileManager.a OpenGL/OpenGL.a Display/Display.a Graphics/Graphics.a User/User.a

BASE_DIR := .

include $(BASE_DIR)/MakefileArchiver.mk

################################################################
