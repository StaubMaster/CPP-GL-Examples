
################################################################

UI_TEXT_DIR := $(OTHER_DIR)/

OTHER_LIST += $(UI_TEXT_DIR)/UIText

UI_TEXT_LIBRARYS  := UIText/UIText.a
UI_TEXT_INCLUDES  := ./
UI_TEXT_ARGUMENTS := 

LIBRARYS  += $(addprefix $(UI_TEXT_DIR)/,$(UI_TEXT_LIBRARYS))
INCLUDES  += $(addprefix $(UI_TEXT_DIR)/,$(UI_TEXT_INCLUDES))
ARGUMENTS += $(UI_TEXT_ARGUMENTS)

################################################################
