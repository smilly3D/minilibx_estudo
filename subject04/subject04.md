# Subject 04 — Primitivas 2D (linha/retângulo/círculo)

## 📋 Informações

- **Dificuldade:** ⭐⭐⭐
- **Tempo estimado:** 2-3 horas
- **Tópicos:** Bresenham (linha), rasterização, desenho no buffer

---

## 📝 Objetivo

Implementar algumas primitivas para desenhar no buffer:

- `draw_line` (Bresenham)
- `draw_rect` (contorno e preenchido)
- `draw_circle` (simples)

---

## 🧠 Mini-API do dia (buffer)

Você já está trabalhando com:

- `mlx_new_image(mlx, w, h)`
- `mlx_get_data_addr(img, &bpp, &line_len, &endian)`
- `mlx_put_image_to_window(mlx, win, img, 0, 0)`

O ponto importante é entender **como endereçar um pixel**.

Se `bpp == 32`, cada pixel ocupa 4 bytes. O endereço do pixel $(x, y)$ é:

$$addr + (y * line\_len) + (x * (bpp/8))$$

---

## ✅ Implementação sugerida (ordem)

1) **`img_put_pixel` com clamp**

- Se `x` ou `y` estiver fora da tela, não escreva.
- Escreva um `int` (ou `unsigned int`) no endereço calculado.

2) **Retângulo preenchido (`draw_rect_fill`)**

- Dois loops: `y` externo, `x` interno.
- Use isso para “limpar a tela” (background).

3) **Linha (Bresenham)**

- Implementação clássica usa `dx`, `dy`, `sx`, `sy`, `err`.
- Você desenha 1 pixel por passo e vai andando até chegar no destino.

4) **Círculo preenchido (`draw_circle_fill`)**

- Comece com a versão simples: para cada `y` de `-r..r`, para cada `x` de `-r..r`, se $x^2 + y^2 <= r^2$ então pinta.
- Otimização (opcional): usar simetria / midpoint circle algorithm.

---

## 🧪 Debug rápido

- Primeiro teste: pinte 1 pixel no centro com cor forte.
- Depois: desenhe um retângulo grande (background).
- Depois: desenhe uma linha diagonal.
- Só então: Bresenham/círculo.

---

## ⚠️ Erros comuns

- Trocar `line_len` com `width` (não é a mesma coisa!).
- Assumir `bpp == 32` sem checar (na MLX Linux normalmente é 32, mas não trate como lei universal).
- Esquecer que o buffer não “aparece” até chamar `mlx_put_image_to_window`.

---

## ✅ Tarefas

1. Mude a cena: desenhe um “grid” 50x50.
2. Faça o círculo virar uma “rosquinha” (anel): só contorno.
3. Exercício bônus: desenhe um triângulo (3 linhas) e preencha (scanline).

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject04
make
./subject04
```
