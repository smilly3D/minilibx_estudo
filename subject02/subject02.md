# Subject 02 — Imagem (buffer) + put_image_to_window

## 📋 Informações

- **Dificuldade:** ⭐⭐ Iniciante/Intermediário
- **Tempo estimado:** 1-2 horas
- **Tópicos:** `mlx_new_image`, `mlx_get_data_addr`, stride, endianness, performance

---

## 📝 Objetivo

Parar de usar `mlx_pixel_put` e desenhar em um **buffer de imagem** (um array de bytes) para depois renderizar com:

- `mlx_put_image_to_window`

Esse é o jeito “certo” de desenhar bastante coisa.

---

## 📌 Mini-API do dia

### `void *mlx_new_image(void *mlx, int width, int height)`

- O que faz: cria uma imagem off-screen (um buffer em memória).
- Você escreve pixels nesse buffer e depois “blita” para a janela.

### `char *mlx_get_data_addr(void *img, int *bpp, int *size_line, int *endian)`

- O que faz: te dá acesso ao ponteiro bruto do buffer.
- `bpp`: bits por pixel (geralmente 32).
- `size_line`: quantos **bytes** cada linha ocupa (stride). Não assuma `width * 4`.
- `endian`: 0/1 (na prática, pra começar, você pode ignorar se estiver usando `0xRRGGBB`).

### `int mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y)`

- O que faz: desenha a imagem pronta na janela.

---

## 🔥 Fórmula do pixel (a parte mais importante)

Se `addr` é `char*`:

- bytes por pixel = `bpp / 8`
- endereço do pixel:

	`dst = addr + (y * line_len + x * (bpp / 8))`

Depois você escreve a cor (normalmente 4 bytes):

- `*(unsigned int *)dst = color;`

---

## 🎯 Checkpoints

1. Criar janela.
2. Criar imagem.
3. Pegar `addr/bpp/line_len/endian`.
4. Implementar `img_put_pixel` com a fórmula.
5. Desenhar algo simples (xadrez 8×8 é perfeito).
6. `mlx_put_image_to_window`.

---

## 🐛 Erros comuns

- Escrever fora do buffer (não checar `x/y` antes).
- Assumir `line_len == width * 4`.
- Esquecer de chamar `mlx_put_image_to_window` (você desenha no buffer, mas não aparece).

---

## ✅ Tarefas

1. Entenda o struct `t_img`.
2. Entenda como `bpp` e `line_len` afetam o endereço do pixel.
3. Exercício: desenhe um tabuleiro 8x8 (xadrez) alternando duas cores.

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject02
make
./subject02
```

---

## 🚀 Próximo

Vá para `subject03` para aprender eventos (teclado/mouse) e atualizar a tela em loop.
