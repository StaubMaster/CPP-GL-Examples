
NAME := Selector.exe
FANCY_NAME := Selector

################################################################

FILES := \
	ContextBase.cpp \
\
	ValueGen/Random.cpp \
	ValueGen/Perlin2D.cpp \
	ValueGen/Perlin3D.cpp \
\
	UnitToString.cpp \
\
	main.cpp \

################################################################

BASE_DIR := ../
include BaseC.mk

################################################################

include Context0.mk
include Context1.mk
include NoisePlane.mk

include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################
