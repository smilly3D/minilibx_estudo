# Subject 00 — Setup + Janela + Sair Limpinho (Linux)

## 📋 Informações

- **Dificuldade:** ⭐ Iniciante
- **Tempo estimado:** 30-45 min
- **Tópicos:** `mlx_init`, `mlx_new_window`, `mlx_loop`, hooks básicos, cleanup

---

## 📝 Objetivo

Você vai criar uma janela e aprender o “ciclo de vida” mínimo da MiniLibX no Linux:

1. inicializar o MLX
2. criar uma janela
3. registrar eventos (ESC e fechar a janela)
4. destruir tudo corretamente (sem leaks e sem double free)

Você vai aprender a sequência “canônica” no Linux:

- `mlx_init()` → `mlx_new_window()` → `mlx_hook()`/`mlx_key_hook()` → `mlx_loop()`

E o cleanup típico:

- `mlx_destroy_window()` → `mlx_destroy_display()` → `free(mlx)`

---

## 📌 Mini-API do dia

### `void *mlx_init(void)`

- O que faz: cria/conecta um “contexto” do MLX (no Linux, é a conexão com o X11).
- Retorno: ponteiro não-NULL em caso de sucesso.
- Erro comum: chamar qualquer outra função MLX com `mlx == NULL`.

### `void *mlx_new_window(void *mlx, int w, int h, char *title)`

- O que faz: cria uma janela do X11.
- Retorno: ponteiro da janela.
- Erro comum: criar janela e nunca destruir.

### `int mlx_loop(void *mlx)`

- O que faz: entra no loop de eventos. Daqui para frente seu programa “vive” pelos callbacks.
- Observação: se você não registrar hooks, não acontece nada além de “ficar aberto”.

### `int mlx_hook(void *win, int x_event, int mask, int (*f)(), void *param)`

- O que faz: registra callbacks de eventos do X11.
- Você vai usar bastante:
	- `DestroyNotify` (clicar no X)
	- `KeyPress` (tecla pressionada)
- `mask` costuma ser a máscara do evento (ex.: `KeyPressMask`). Em vários casos, `0` também funciona.

---

## 🎯 Checkpoints (faça em ordem)

1. **Criar** `mlx` e `win` e entrar no `mlx_loop`.
2. Registrar `DestroyNotify`: fechar no X chama seu `app_destroy`.
3. Registrar `KeyPress`: se `keysym == XK_Escape`, fechar.
4. No destroy, aplicar a ordem:
	 - destruir janela
	 - destruir display
	 - dar `free(mlx)`

---

## 🐛 Erros comuns

- Esquecer de `free(mlx)` depois do `mlx_destroy_display()`.
- Chamar `mlx_destroy_display()` mas continuar usando `mlx`.
- Não tratar o clique do X e ficar preso no loop.

---

## ✅ Tarefas

### Parte 1 — Rodar
- Compile e execute `subject00`.
- Confirme que abrir/fechar não dá crash.

### Parte 2 — Entender
No código, localize:
- `mlx_init()`
- `mlx_new_window()`
- `mlx_hook(... DestroyNotify ...)` (fechar no X)
- `mlx_hook(... KeyPress ...)` (ESC)
- função `app_destroy()`

### Parte 3 — Exercício
1. Troque o tamanho da janela para `1024x768`.
2. Mude o título.
3. Ao apertar `SPACE`, imprima no terminal `space!`.

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject00
make
./subject00
```

---

## ✅ Checklist

- [ ] Abre a janela
- [ ] Fecha no ESC
- [ ] Fecha no clique do X
- [ ] Não dá crash ao fechar
- [ ] Sei onde fica o cleanup

---

## 🚀 Próximo

Vá para `subject01` para desenhar seus primeiros pixels.
