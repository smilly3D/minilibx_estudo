# Subject 01 — Primeiros Pixels (mlx_pixel_put)

## 📋 Informações

- **Dificuldade:** ⭐ Iniciante
- **Tempo estimado:** 45-60 min
- **Tópicos:** `mlx_pixel_put`, cores em hex, loops e performance

---

## 📝 Objetivo

Desenhar na janela usando `mlx_pixel_put` (simples, porém mais lento). Você vai fazer:

- um fundo em gradiente
- um “alvo” (crosshair) no centro

---

## 📌 Mini-API do dia

### `int mlx_pixel_put(void *mlx, void *win, int x, int y, int color)`

- O que faz: desenha 1 pixel diretamente na janela.
- `color`: normalmente `0xRRGGBB`.
- Retorno: geralmente ignorado.
- Observação: **lento**. Se você desenhar 800×600 = 480k pixels por frame, pode ficar ruim.

### Cor `0xRRGGBB`

- Vermelho: `0xFF0000`
- Verde: `0x00FF00`
- Azul: `0x0000FF`
- Branco: `0xFFFFFF`

---

## 🎯 Checkpoints (faça em ordem)

1. Abra a janela (pode copiar base do subject00).
2. Faça um loop duplo `(y,x)` e chame `mlx_pixel_put`.
3. Gere um gradiente simples:
	- `r = x * 255 / (w - 1)`
	- `g = y * 255 / (h - 1)`
4. Desenhe um crosshair no centro.

---

## 🐛 Erros comuns

- Trocar `x`/`y` e desenhar “girado”.
- Usar `w` ou `h` igual a 1 e dividir por zero.
- Tentar animar tudo com `mlx_pixel_put` (vai travar) — isso é o gancho para o subject02.

---

## ✅ Tarefas

1. Entenda a função `rgb(r,g,b)`.
2. Modifique o gradiente para mudar de direção.
3. Desenhe um quadrado 100x100 no centro (cor sólida).

---

## ⚠️ Observação importante

`mlx_pixel_put` é ótimo para aprender, mas **não escala bem**. No próximo subject você vai usar **imagem/buffer** para desenhar rápido.

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject01
make
./subject01
```

---

## 🚀 Próximo

Vá para `subject02` para desenhar em um buffer de imagem e depois “blitar” na janela.
