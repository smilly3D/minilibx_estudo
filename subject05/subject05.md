# Subject 05 — Animação + Tempo (dt) + HUD

## 📋 Informações

- **Dificuldade:** ⭐⭐⭐
- **Tempo estimado:** 2-3 horas
- **Tópicos:** `mlx_loop_hook`, tempo real, velocidade em px/s, FPS

---

## 📝 Objetivo

Mover uma bolinha na tela usando **tempo real** (delta time):

- a velocidade não depende do FPS
- a bolinha rebate nas bordas
- desenha um texto simples com `mlx_string_put`

---

## 🧠 Conceito-chave: dt (delta time)

Se você move “X pixels por frame”, o jogo muda com o FPS. A ideia é mover em **pixels por segundo**.

- Defina `vx` e `vy` em px/s.
- A cada frame, calcule `dt` em segundos.
- Atualize: `x += vx * dt` e `y += vy * dt`.

---

## 🧰 Como medir tempo no Linux

Opções boas:

- `clock_gettime(CLOCK_MONOTONIC, ...)` (recomendado)
- `gettimeofday` (funciona, mas não é monotônico)

Você vai guardar `last_time` e no frame atual faz:

1) `now = ...`
2) `dt = (now - last_time)`
3) `last_time = now`

---

## ✅ Implementação sugerida (ordem)

1) **Desenho estático**

- Limpe a tela (retângulo fill).
- Desenhe uma bolinha em `(x, y)`.
- `mlx_put_image_to_window`.

2) **Adicionar loop_hook**

- Tudo acontece no `on_frame`.
- No começo, ignore `dt` e mova com um `x += 1` só pra ver que anima.

3) **Trocar para dt**

- Transforme `x, y` em `double`.
- Use `vx, vy`.

4) **Rebate nas bordas**

- Se bater, inverta o sinal de `vx`/`vy`.
- Leve em conta o raio da bolinha.

5) **HUD com `mlx_string_put`**

- Exiba `FPS` aproximado: `fps = 1.0 / dt`.
- Exiba velocidade ou estado “paused”.

---

## ⚠️ Erros comuns

- dt muito grande ao voltar de pausa/debug: limite `dt` (ex.: clamp em 0.05s).
- Usar `sleep` dentro do loop: trava o processamento de eventos.
- Desenhar texto no buffer da imagem: `mlx_string_put` escreve direto na janela, então se você redesenhar o fundo por cima, vai “sumir” (re-desenhe o texto todo frame).

---

## ✅ Tarefas

1. Aumente a velocidade com `+` e diminua com `-`.
2. Adicione pausa no `P`.
3. Exercício: faça a cor mudar quando bater na parede.

---

## 🧪 Compilação

```bash
cd estudo_minilibx/subject05
make
./subject05
```
