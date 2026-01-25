# MiniLibX (Linux) — Guia Progressivo (Subjects)

Este diretório é um “curso” incremental no estilo dos seus `subjects` de structs.

Importante: os `subjectXX.c` agora são **starter files** (com TODOs) para você ir implementando enquanto lê.
Os gabaritos completos ficam em `estudo_minilibx/gabaritos/`.

## Pré-requisitos (Linux)

A `minilibx-linux` precisa das libs de X11 e `libbsd`.
No Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev
```

## Como rodar cada subject

Cada pasta tem seu próprio `Makefile`.

Exemplo:

```bash
cd estudo_minilibx/subject00
make
./subject00
```

## Subjects

- `subject00` — Janela + loop + sair corretamente
- `subject01` — `mlx_pixel_put` (primeiros pixels na tela)
- `subject02` — Imagem (buffer) + `mlx_put_image_to_window`
- `subject03` — Eventos (teclado/mouse) + estado + `mlx_loop_hook`
- `subject04` — Primitivas 2D (linha/retângulo/círculo) no buffer
- `subject05` — Animação + tempo (dt) + HUD simples
- `subject06` — Mini-projeto: “paint” (clique desenha, teclas, salvar PPM)

Dica: se algo der `Segmentation fault`, o caminho mais rápido é conferir se você não está usando ponteiros MLX depois de destruí-los (janela/imagem/display).

## Convenções (Linux)

- Callbacks costumam receber `int keysym` e `void *param` (aqui usamos um `t_app *`).
- Para keysyms: inclua `<X11/keysym.h>` e compare com `XK_Escape`, `XK_space`, etc.
- Para eventos/máscaras: inclua `<X11/X.h>` (ex.: `KeyPress`, `KeyPressMask`, `DestroyNotify`).
# minilibx_estudo
