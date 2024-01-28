NAME	= tests

OBJ_DIR	= ./obj
SRC_DIR = .

CC 		= c++
CFLAGS 	= -MP -MMD -I$(SRC_DIR) -Wall -Wextra -Werror -Wpedantic -g -std=c++17
SHELL	= /bin/sh

SRCS	= main.cpp Serializer.cpp Data.cpp

all: $(NAME)

run: all
	./$(NAME)

leaks: all
	leaks -q --atExit -- ./$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
	$(CC) $(CFLAGS) -o $@ $^
# Add the debugging tool entitlement when building on OS X
ifneq ($(OS),Windows_NT)
ifeq ($(shell uname -s),Darwin)
	@make osx_debug_codesign
endif
endif

OSX_ENTITLEMENTS_FILE = $(OBJ_DIR)/tmp.entitlements
$(OSX_ENTITLEMENTS_FILE):
	/usr/libexec/PlistBuddy -c \
		"Add :com.apple.security.get-task-allow bool true" \
		$@

osx_debug_codesign: $(OSX_ENTITLEMENTS_FILE)
	codesign -s - -f --entitlements $< ./$(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

.PHONY: all leaks re clean fclean run osx_debug_codesign

vpath %.cpp $(SRC_DIR)
-include $(SRCS:%.cpp=$(OBJ_DIR)/%.d)
