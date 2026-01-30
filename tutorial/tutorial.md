### 📄 Documentação do Código (`tutorial.c` - Gerador de Mandelbrot)

#### **Visão Geral**

Este programa utiliza a biblioteca MiniLibX para criar uma janela e desenhar o conjunto de Mandelbrot. Ele permite uma visualização inicial do fractal e está estruturado para ser expandido com interatividade, como zoom e navegação.

#### **Estruturas de Dados**

O programa se baseia na estrutura `t_data` (provavelmente definida em `subject.h`) para gerenciar todas as variáveis importantes:

-   `void *mlx`, `void *win`: Ponteiros para a instância da MiniLibX e para a janela.
-   `void *img`, `char *addr`: Ponteiros para a imagem em memória e seu endereço de buffer.
-   `int bits_per_pixel`, `int line_length`, `int endian`: Propriedades da imagem, essenciais para manipulação direta dos pixels.
-   `int w`, `int h`: Largura e altura da janela/imagem.
-   `double zoom`, `double shift_x`, `double shift_y`: Parâmetros para controlar a visualização do fractal (zoom e posição).
-   `int max_iter`: Número máximo de iterações para o cálculo do fractal, afetando o detalhe e o custo de processamento.
-   `int dirty`: Uma flag para controlar quando a tela precisa ser redesenhada.

#### **Funções Principais**

-   `my_mlx_pixel_put(t_data *d, int x, int y, int color)`: Uma função otimizada para desenhar um pixel. Em vez de usar a `mlx_pixel_put` da biblioteca (que é lenta para muitos pixels), esta função escreve a cor diretamente no buffer da imagem em memória. Isso é feito calculando a posição exata do pixel no buffer usando `line_length` e `bits_per_pixel`.
-   `mandelbrot_iters(...)`: O coração matemático do programa. Calcula quantas iterações são necessárias para determinar se um ponto (`cr`, `ci`) pertence ao conjunto de Mandelbrot.
-   `color_from_iter(...)`: Converte o número de iterações retornado por `mandelbrot_iters` em uma cor. Pontos dentro do conjunto recebem a cor preta.
-   `render_fractal(t_data *d)`: Itera por cada pixel da tela, converte as coordenadas do pixel em um ponto no plano complexo (usando o `zoom` e `shift`), calcula as iterações de Mandelbrot e desenha o pixel com a cor correspondente.
-   `loop_hook(void *param)`: Esta função é registrada com `mlx_loop_hook` e é chamada continuamente. Ela verifica a flag `dirty`. Se for verdade, significa que algo mudou (como o zoom), então ela chama `render_fractal` para redesenhar a imagem e a exibe na janela. Depois, reseta a flag `dirty`. Isso evita redesenhar a tela desnecessariamente.
-   `close_win(void *param)`: Função para fechar a janela e terminar o programa de forma limpa. É conectada ao evento de fechar a janela (`mlx_hook` com o evento 17).
-   `main()`: Inicializa a MiniLibX, a janela e a imagem. Define os valores iniciais para o fractal, conecta os hooks de eventos (`close_win` e `loop_hook`) e inicia o loop de eventos principal com `mlx_loop`.

---

### 🚀 Próximos Passos e Evolução

Seu código atual é uma excelente base. Os próximos passos lógicos, inclusive sugeridos nos comentários do próprio código, seriam:

1.  **Implementar Interatividade (Hooks):**
    *   **Zoom com o Mouse:** Use `mlx_mouse_hook` para detectar o scroll do mouse. Altere a variável `d.zoom` com base no scroll para cima ou para baixo. Não se esqueça de setar `d.dirty = 1;` para que o `loop_hook` redesenhe o fractal.
    *   **Navegação com o Teclado:** Use `mlx_key_hook` para detectar as setas do teclado. Altere as variáveis `d.shift_x` e `d.shift_y` para mover a visualização do fractal. Lembre-se de setar `d.dirty = 1;`.
    *   **Fechar com ESC:** Adicione um hook de teclado para que a tecla ESC também chame a função `close_win`.

2.  **Melhorar a Qualidade Visual:**
    *   **Cores:** A função `color_from_iter` atual usa um gradiente simples de vermelho. Pesquise sobre algoritmos de coloração de fractais (como "Normalized Iteration Count") para criar gradientes mais suaves e psicodélicos.
    *   **Aumentar Iterações:** Permita que o usuário aumente/diminua `max_iter` com teclas (+/-). Isso aumenta o detalhe do fractal, especialmente com zoom alto.

3.  **Refatoração e Limpeza:**
    *   As funções comentadas (`clear_image`, `clear_image_fast`, etc.) podem ser removidas se não forem mais necessárias, ou movidas para um arquivo de utilitários se forem úteis em outros projetos.

---

### 📁 Sugestão de Organização do Projeto

A estrutura atual, com um diretório para cada "subject", é **muito boa para aprender**. Ela isola cada exercício, o que é ideal. Minha sugestão é aprimorá-la, não mudá-la radicalmente:

1.  **Mantenha a Estrutura Modular:** Continue com `/tutorial`, `/subject00`, `/subject01`, etc.

2.  **Crie um Makefile Raiz:** Na pasta principal (`minilibx_estudo`), crie um `Makefile` que possa compilar todos os projetos. Isso facilita sua vida. Ele poderia ter regras como:
    ```makefile
    all:
        @make -C tutorial
        @make -C subject00
        @make -C subject01
        # ... e assim por diante

    tutorial:
        @make -C tutorial

    subject00:
        @make -C subject00

    clean:
        @make -C tutorial clean
        @make -C subject00 clean
        # ...

    fclean:
        @make -C tutorial fclean
        @make -C subject00 fclean
        # ...
    ```

3.  **Considere um diretório `common` ou `shared`:** Conforme você avança, pode notar que algumas funções (como `my_mlx_pixel_put`) são úteis em vários projetos. Você pode criar um diretório `common/` na raiz e colocar esses arquivos lá. Depois, ajuste os `Makefiles` de cada `subject` para compilar e linkar esses arquivos comuns. Isso evita a duplicação de código.

Sua jornada com a MiniLibX começou com um projeto bem interessante! Continue explorando os hooks e a manipulação de imagens.
