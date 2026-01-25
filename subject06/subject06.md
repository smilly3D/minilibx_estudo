# Subject 06 — Mini-projeto: Paint (interativo) + Salvar PPM

## 📋 Informações

- **Dificuldade:** ⭐⭐⭐⭐
- **Tempo estimado:** 3-5 horas
- **Tópicos:** mouse, teclado, brush, desenho contínuo, salvar imagem (PPM)

---

## 📝 Objetivo

Você vai fazer um mini “paint”:

- **Clique esquerdo**: pinta um círculo (brush)
- **Segurar e arrastar**: pinta continuamente
- **Clique direito**: limpa a tela
- **Roda do mouse**: muda o tamanho do brush
- **S**: salva `output.ppm`
- **ESC**: sai

PPM é um formato simples (texto/binário). Aqui vamos salvar em PPM binário (P6).

---

## 🧠 Mini-API do dia

### Mouse/teclado

- `mlx_hook(win, ButtonPress, ButtonPressMask, on_mousedown, &app)`
- `mlx_hook(win, KeyPress, KeyPressMask, on_keypress, &app)`
- `mlx_loop_hook(mlx, on_frame, &app)`

No Linux/X11, o mouse costuma vir assim:

- Botão 1: clique esquerdo
- Botão 3: clique direito
- Botão 4/5: scroll up/down (varia com o sistema)

### Desenho

- Desenhe no **buffer** (imagem) e mostre com `mlx_put_image_to_window`.
- Evite `mlx_pixel_put` aqui (lento demais).

---

## ✅ Roteiro incremental (bem prático)

1) **Fechar no ESC e no X**

- O starter já fecha no ESC e no X.

2) **Pintar um ponto no clique**

- Em `on_mousedown`, quando botão esquerdo:
	- chame `img_put_pixel(&app->img, x, y, brush_color)`.
- Em `on_frame`, faça `mlx_put_image_to_window` para “aparecer”.

3) **Brush circular**

- Faça `draw_circle_fill(img, cx, cy, radius, color)`.
- Comece com o método simples $x^2 + y^2 <= r^2$.

4) **Arrastar sem furar**

- Guarde `last_x/last_y` quando o botão estiver pressionado.
- A cada evento/movimento (ou no frame), interpole uma linha entre os pontos e desenhe círculos ao longo dela.

5) **Limpar tela**

- Clique direito: preencha o buffer com cor de fundo.

6) **Salvar PPM (P6)**

Formato (binário):

```
P6\n
<width> <height>\n
255\n
<bytes RGBRGBRGB...>
```

- Cada pixel vira **3 bytes** (R, G, B).
- Se sua imagem estiver em `0xRRGGBB`, extraia:
	- `r = (color >> 16) & 0xFF`
	- `g = (color >> 8) & 0xFF`
	- `b = color & 0xFF`

Dica: escreva o header com `snprintf` + `write_all` (para não ter warning de retorno ignorado com `-Werror`).

---

## ⚠️ Erros comuns

- Pintar fora da tela: sempre faça clamp/guard no put_pixel.
- Scroll invertido ou botões diferentes: imprima o `button` recebido pra confirmar.
- Salvar a imagem “torta”: você precisa ler o pixel do seu buffer respeitando `line_len` e `bpp`.
- Confundir endian: em geral, se você escreve pixels como `int` e funciona na tela, para salvar prefira extrair R/G/B daquele `int` do mesmo jeito (não tente salvar os bytes crus do buffer sem entender o formato).

---

## ✅ Tarefas

1. Troque a cor do brush com teclas `1..5`.
2. Faça `C` alternar modo “borracha” (pinta com cor do fundo).
3. Exercício bônus: desenhe uma linha interpolando pontos para não ficar “furado” ao arrastar rápido.

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject06
make
./subject06
```

Abra o arquivo gerado:

```bash
xdg-open output.ppm
```
