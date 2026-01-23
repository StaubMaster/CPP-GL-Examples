
################################################################

ifeq ($(OS), Windows_NT)
	CheckOS := Windows
else
	CheckOS := $(shell uname -s)
endif

################################################################

ifeq ($(CheckOS), Windows)
FANCY_ECHO := echo -e
COLOR_REPO := \e[38;2;127;127;127m
COLOR_TYPE := \e[38;2;127;255;127m
COLOR_FILE := \e[38;2;127;127;255m
COLOR_NONE := \e[m
endif

################################################################

ifeq ($(CheckOS), Darwin)
FANCY_ECHO := echo
COLOR_REPO := \033[38;2;127;127;127m
COLOR_TYPE := \033[38;2;127;255;127m
COLOR_FILE := \033[38;2;127;127;255m
COLOR_NONE := \033[m
endif

################################################################

ifeq ($(CheckOS), Linux)
FANCY_ECHO := echo
COLOR_REPO := \033[38;2;127;127;127m
COLOR_TYPE := \033[38;2;127;255;127m
COLOR_FILE := \033[38;2;127;127;255m
COLOR_NONE := \033[m
endif

################################################################



#	@$(call fancyEcho,Arg0,Arg1,Arg2)

define fancyEcho
	@$(FANCY_ECHO) "$(COLOR_REPO)$(1): $(COLOR_TYPE)$(2): $(COLOR_FILE)$(3)$(COLOR_NONE)"
endef

define fancyNameTargetEcho
	@$(call fancyEcho,$(FANCY_NAME),Target,$(1))
endef

define fancyNameCompilingEcho
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$(1))
endef

define fancyNameArchivingEcho
	@$(call fancyEcho,$(FANCY_NAME),Archiving,$(1))
endef
