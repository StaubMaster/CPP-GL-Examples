
################################################################

UI_DIR := $(OTHER_DIR)/UI
OTHER_LIST += $(UI_DIR)

UI_LIBRARYS := $(UI_DIR)/UI.a
UI_INCLUDES := $(UI_DIR)/../
UI_ARGUMENTS :=

LIBRARYS += $(UI_LIBRARYS)
INCLUDES += $(UI_INCLUDES)
ARGUMENTS += $(UI_ARGUMENTS)

$(UI_LIBRARYS) : $(UI_DIR)
	$(MAKE) -C $(UI_DIR) -s $(@:$(UI_DIR)/%=%)

################################################################
