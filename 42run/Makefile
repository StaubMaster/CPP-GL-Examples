
NAME := 42run.exe
FANCY_NAME := 42run

################################################################

FILES := \
	code/NodePath.cpp \
	code/Player.cpp \
	code/PlayerChange.cpp \
	code/Tile/Feature/Pallet.cpp \
	code/Tile/Feature/Pallet/DeathFall.cpp \
	code/Tile/Feature/Pallet/DeathWall.cpp \
	code/Tile/Feature/Pallet/CoinParabola.cpp \
	code/Tile/Feature/Object.cpp \
	code/Tile/Feature/Object/Coin.cpp \
	code/Tile/Pallet.cpp \
	code/Tile/Object.cpp \
	code/Tile/Parser.cpp \
	code/Context.cpp \
	code/Layout/Multiform.cpp \
	code/main.cpp \

DIR_SRC := .
DIR_OBJ := .

LIBRARYS  :=
INCLUDES  := code/
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ./
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(OTHER_DIR)/Miscellaneous.mk
include $(OTHER_DIR)/UIText.mk

include $(REPOS_DIR)/Engine.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################
