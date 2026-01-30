# Definição dos diretórios dos subjects
SUBJECTS = subject00_base_fractal subject01_interaction subject02_colors

.PHONY: all clean fclean re $(SUBJECTS)

# Target 'all' para compilar todos os subjects
all: $(SUBJECTS)

# Regra genérica para cada subject
# Isso permite compilar um subject individualmente, ex: 'make subject00_base_fractal'
$(SUBJECTS):
	@echo "--- Compiling $(@) ---"
	@$(MAKE) -C $(@)

# Target 'clean' para limpar os arquivos .o de todos os subjects
clean:
	@for dir in $(SUBJECTS); do \
		echo "--- Cleaning $(dir) ---"; \
		$(MAKE) -C $$dir clean; \
	done

# Target 'fclean' para limpar os executáveis e .o de todos os subjects
fclean:
	@for dir in $(SUBJECTS); do \
		echo "--- Full cleaning $(dir) ---"; \
		$(MAKE) -C $$dir fclean; \
	done

# Target 're' para fazer um fclean seguido de um all
re: fclean all

# Mensagem de ajuda
help:
	@echo "Makefile Principal"
	@echo "------------------"
	@echo "make all          - Compila todos os exercícios."
	@echo "make clean        - Remove arquivos de objeto (.o) de todos os exercícios."
	@echo "make fclean       - Remove todos os arquivos compilados de todos os exercícios."
	@echo "make re           - Re-compila tudo do zero."
	@echo "make <subject>    - Compila um exercício específico (ex: make subject01_interaction)."
