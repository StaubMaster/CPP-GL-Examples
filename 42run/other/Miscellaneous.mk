
################################################################

MISC_DIR := $(OTHER_DIR)/

OTHER_LIST += $(MISC_DIR)/ValueGen
OTHER_LIST += $(MISC_DIR)/NewPolyHedra

MISC_LIBRARYS  := ValueGen/ValueGen.a NewPolyHedra/NewPolyHedra.a
MISC_INCLUDES  := ./ NewPolyHedra/
MISC_ARGUMENTS := 

LIBRARYS  += $(addprefix $(MISC_DIR)/,$(MISC_LIBRARYS))
INCLUDES  += $(addprefix $(MISC_DIR)/,$(MISC_INCLUDES))
ARGUMENTS += $(MISC_ARGUMENTS)

################################################################
