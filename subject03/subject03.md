# Subject 03 — Eventos + Loop Hook + Estado

## 📋 Informações

- **Dificuldade:** ⭐⭐
- **Tempo estimado:** 1-2 horas
- **Tópicos:** `mlx_hook`, `mlx_loop_hook`, teclado/mouse, redesenho por frame

---

## 📝 Objetivo

Você vai controlar um quadrado na tela:

- setas movem o quadrado
- clique do mouse “teleporta” para o cursor
- a tela é redesenhada em loop (frame a frame)

Isso é a base de qualquer projeto tipo `so_long`, `cub3d` e afins.

---

## 🧠 Mini-API do dia

### `mlx_hook(win, event, mask, cb, param)`

- Você registra uma função (callback) para um evento X11.
- `cb` quase sempre retorna `int` (retorne `0`).
- `param` normalmente é um ponteiro para seu `t_app`.

Eventos comuns que você vai usar aqui:

- `KeyPress` com `KeyPressMask`: teclado.
- `ButtonPress` com `ButtonPressMask`: clique do mouse.
- `DestroyNotify` com `StructureNotifyMask`: usuário clicou no X.

### `mlx_loop_hook(mlx, cb, param)`

- Registra um callback que roda “sempre” (a cada iteração do loop).
- Use para redesenhar e para animações.
- Regra mental: **callbacks mudam estado → loop_hook desenha o estado**.

---

## ✅ Implementação sugerida (ordem que dói menos)

1) **Fechar no ESC e no X**

- No starter, `app_destroy()` já faz o cleanup.
- Em `on_keypress`, se `keysym == XK_Escape`, chame `app_destroy(app)`.
- No `main`, garanta um `mlx_hook(... DestroyNotify ...)`.

2) **Mover com teclado (sem render ainda)**

- Atualize `app->x`/`app->y` no `on_keypress`.
- Comece com `WASD` ou setas. Exemplo de keysyms úteis:
	- `XK_Left`, `XK_Right`, `XK_Up`, `XK_Down`
	- `XK_w`, `XK_a`, `XK_s`, `XK_d`

3) **Clique teleporta**

- Em `on_mousedown`, ignore o `button` no começo e faça:
	- `app->x = x - app->size/2;`
	- `app->y = y - app->size/2;`

4) **Redesenhar no `on_frame`**

- Limpe o buffer (preencher com uma cor sólida).
- Desenhe um quadrado na posição atual.
- Chame `mlx_put_image_to_window`.

---

## 🧩 Checkpoints (se travar)

- Se o `on_keypress` não dispara:
	- confira se você registrou `mlx_hook(win, KeyPress, KeyPressMask, ...)`.
- Se o loop_hook não roda:
	- confira `mlx_loop_hook(mlx, on_frame, &app)`.
- Se fecha no ESC mas não fecha no X:
	- adicione `mlx_hook(win, DestroyNotify, StructureNotifyMask, ...)`.

---

## ⚠️ Erros comuns

- Misturar render e lógica dentro do callback do teclado: funciona no começo, mas vira caos.
- Atualizar a imagem e esquecer o `mlx_put_image_to_window`.
- Não limitar `x/y` e o quadrado “some” (vai pra fora).

---

## ✅ Tarefas

1. Troque as teclas para WASD.
2. Limite o movimento para não sair da tela.
3. Exercício: adicione uma segunda forma (um círculo) seguindo o mouse.

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject03
make
./subject03
```
