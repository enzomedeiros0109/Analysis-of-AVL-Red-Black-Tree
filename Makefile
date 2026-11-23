# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(SRC_DIR)

# Diretórios
SRC_DIR = src
BIN_DIR = bin

# Nome do executável final
TARGET = $(BIN_DIR)/bst

# Lista de arquivos fonte e objetos
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

# Regra padrão
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJ)
	@echo "Ligando objetos..."
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar arquivos .c em .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@echo "🧱 Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório bin/ se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpeza dos binários
clean:
	@echo "Limpando arquivos compilados..."
	rm -rf $(BIN_DIR)/*.o $(TARGET)

# Limpeza completa
fclean: clean
	rm -rf $(BIN_DIR)

# Reconstrói tudo do zero
re: fclean all

.PHONY: all clean fclean re
