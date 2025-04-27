# Dossiers
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
DATA_DIR = dictionnaires
TESTS_DIR = tests

# Compilateur et options
CC=gcc
CFLAGS=-Wall -Wextra -O2 -I$(INCLUDE_DIR)

# Tous les fichiers sources
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Tous les fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Nom de l'exécutable
TARGET = projet

# Règle principale
all: $(TARGET)

# Comment construire l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Comment construire les .o à partir des .c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Créer build/ s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyer le projet (fichiers objets + exécutable)
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Nettoyer tout (dossier build entier)
fclean: clean
	rm -rf $(BUILD_DIR)

# Recompiler proprement
re: fclean all

.PHONY: all clean fclean re
