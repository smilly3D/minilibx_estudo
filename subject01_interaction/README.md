# Subject 01: Interação com o Fractal

Neste exercício, vamos dar vida ao fractal. Adicionaremos a capacidade de navegar e dar zoom, transformando a imagem estática em uma visualização dinâmica.

## Objetivos

1.  **Implementar Hooks**: Adicione as funções e os hooks necessários para interagir com o fractal.
    -   `mlx_key_hook`: Use as setas do teclado para mover a visualização (alterando `shift_x` e `shift_y`). Faça a tecla `ESC` fechar a janela.
    -   `mlx_mouse_hook`: Use o scroll do mouse para aplicar zoom (alterando a variável `zoom`).

2.  **Mecanismo de Redesenho**: Toda vez que uma interação acontecer (tecla ou mouse), a `flag dirty` deve ser setada como `1`. Isso sinalizará ao `loop_hook` que a imagem precisa ser recalculada e redesenhada.

3.  **Ajuste de Sensibilidade**: Note que a velocidade de movimento (`shift`) deve ser ajustada de acordo com o nível de `zoom` para que a navegação continue fluida.

## Dicas

-   Os códigos de teclado e mouse podem variar entre sistemas operacionais. Os valores no código de exemplo são para macOS.
-   Lembre-se de passar o ponteiro para sua estrutura `t_data` nos hooks para que as funções possam modificar as variáveis do fractal.
