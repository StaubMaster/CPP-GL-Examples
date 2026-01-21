
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



define fancyEcho
	@$(FANCY_ECHO) "$(COLOR_REPO)$(1): $(COLOR_TYPE)$(2): $(COLOR_FILE)$(3)$(COLOR_NONE)"
endef



fancy_explanation:
	@$(call fancyEcho,Fancy,Default,Example)
.PHONY: fancy_explanation
