
NAME := UserInterface.a
FANCY_NAME := UserInterface

################################################################

FILES := \
	Anchor1D.cpp \
	Anchor2D.cpp \
\
	Control/General/Graphics/Main/Data.cpp \
	Control/General/Graphics/Main/Layout.cpp \
	Control/General/Graphics/Inst/Data.cpp \
	Control/General/Graphics/Inst/Layout.cpp \
	Control/General/Graphics/Layout.cpp \
	\
	Control/General/Manager.cpp \
	Control/General/Control_Display.cpp \
	Control/General/Control_UserRelay.cpp \
	Control/General/Base.cpp \
	Control/General/BaseText.cpp \
\
	Control/Window.cpp \
	Control/Form.cpp \
	Control/Controls/GroupBox.cpp \
	Control/Controls/Button.cpp \
	Control/Controls/TextBox.cpp \
	Control/Controls/Slider.cpp \
	Control/Controls/CheckBox.cpp \
	Control/Controls/Label.cpp \
	Control/Controls/Graph.cpp \
	Control/Controls/ScrollBox.cpp \
	Control/Controls/ListBox.cpp \
\
	Text/Graphics/Main/Data.cpp \
	Text/Graphics/Main/Layout.cpp \
	Text/Graphics/Inst/Data.cpp \
	Text/Graphics/Inst/Layout.cpp \
	Text/Graphics/Layout.cpp \
	\
	Text/Manager.cpp \
	Text/ObjectData.cpp \
	Text/Object.cpp \
	Text/Font/Font.cpp \
	Text/Font/Parsing.cpp \
\
	Graph/ShaderLayout.cpp \
	Graph/BufferLayout.cpp \
	Graph/BufferData.cpp \
	\
	Graph/Manager.cpp \
	Graph/ObjectData.cpp \
	Graph/Object.cpp \
\
	HoverArgs.cpp \
	CursorManager.cpp \
	UIManager.cpp

DIR_SRC := .
DIR_OBJ := .

LIBRARYS :=
INCLUDES := .
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(REPOS_DIR)/Engine.mk

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################
