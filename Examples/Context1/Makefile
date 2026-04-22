
NAME := Context1.a
FANCY_NAME := Context1

################################################################

FILES := \
	Context1.cpp \
	Context1Menu.cpp \

################################################################

BASE_DIR := ../../
include ../BaseA.mk

################################################################

include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

INCLUDES += . ../
