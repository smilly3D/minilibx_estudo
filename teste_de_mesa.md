# Teste de Mesa Visual: Fractal de Mandelbrot

Este documento demonstra o algoritmo do "tempo de escape" do Mandelbrot em ação, usando dois pontos de exemplo (`C`) para ver como a sequência de `Z` se comporta. O `max_iter` (máximo de iterações) será `10` para simplificar.

A fórmula-chave em cada passo (iteração `n`) é: `Z_{n+1} = Z_n^2 + C`

Onde:
- `C = cr + ci` (o ponto no plano complexo que estamos testando)
- `Z = zr + zi` (o valor que evolui a cada passo, começando com `zr=0, zi=0`)

A condição de escape é: `zr^2 + zi^2 > 4`

---

## Exemplo 1: Um Ponto DENTRO do Conjunto (Provavelmente)

Vamos testar um ponto `C` que sabemos estar na parte preta do fractal.
- **`C = -0.5 (cr) + 0.2 (ci)`**

**Objetivo:** Ver se o valor de `Z` permanece pequeno e não "escapa".

**Tabela de Iterações:**

| Iteração (i) | `zr` (inicial) | `zi` (inicial) | `zr_new = zr²-zi²+cr` | `zi_new = 2*zr*zi+ci` | `zr²+zi² > 4`? | `Z` (final) |
|:------------:|:--------------:|:--------------:|:---------------------:|:---------------------:|:---------------:|:--------------------:|
| **0** | `0.0` | `0.0` | 0² - 0² - 0.5 = **-0.5** | 2*0*0 + 0.2 = **0.2** | `0² + 0² = 0`. Não. | `(-0.5, 0.2)` |
| **1** | `-0.5` | `0.2` | (-0.5)²-0.2²-0.5 = **-0.29** | 2*(-0.5)*0.2+0.2 = **0.0** | `(-0.5)²+0.2² = 0.29`. Não. | `(-0.29, 0.0)` |
| **2** | `-0.29`| `0.0` | (-0.29)²-0²-0.5 = **-0.4159** | 2*(-0.29)*0+0.2 = **0.2** | `(-0.29)²+0² = 0.0841`. Não.| `(-0.4159, 0.2)`|
| **3** | `-0.4159`| `0.2` | (-0.4159)²-0.2²-0.5 = **-0.367**| 2*(-0.4159)*0.2+0.2 = **0.0336**| `(-0.4159)²+0.2² = 0.213`. Não.| `(-0.367, 0.0336)`|
| **...** | ... | ... | ... | ... | ... | ... |
| **9** | ... | ... | (continua pequeno) | (continua pequeno) | Não. | ... |
| **10** | ... | ... | (loop termina) | (loop termina) | Não. | ... |

**Conclusão para o Ponto 1:**
A condição de escape `(zr² + zi² > 4)` nunca foi verdadeira. O loop completou todas as `10` iterações. A função `mandelbrot_iters` retornaria `10`. Como `i == max_iter`, o programa colore este pixel de preto, indicando que ele pertence ao conjunto de Mandelbrot.

---

## Exemplo 2: Um Ponto FORA do Conjunto

Agora, vamos testar um ponto `C` que está fora da área principal do fractal.
- **`C = 1.0 (cr) + 1.0 (ci)`**

**Objetivo:** Ver como e quando o valor de `Z` "escapa" (cresce rapidamente).

**Tabela de Iterações:**

| Iteração (i) | `zr` (inicial) | `zi` (inicial) | `zr_new = zr²-zi²+cr` | `zi_new = 2*zr*zi+ci` | `zr²+zi² > 4`? | `Z` (final) |
|:------------:|:--------------:|:--------------:|:-----------------------:|:---------------------:|:----------------:|:-------------:|
| **0** | `0.0` | `0.0` | 0² - 0² + 1.0 = **1.0** | 2*0*0 + 1.0 = **1.0** | `0² + 0² = 0`. Não. | `(1.0, 1.0)` |
| **1** | `1.0` | `1.0` | 1.0² - 1.0² + 1.0 = **1.0** | 2*1.0*1.0 + 1.0 = **3.0** | `1²+1² = 2`. Não. | `(1.0, 3.0)` |
| **2** | `1.0` | `3.0` | 1.0² - 3.0² + 1.0 = **-7.0**| 2*1.0*3.0 + 1.0 = **7.0** | `1²+3² = 10`. **SIM!** | `(-7.0, 7.0)`|

**Conclusão para o Ponto 2:**
Na iteração `i = 2`, o valor de `|Z|^2` (ou `zr² + zi²`) tornou-se `10`, que é maior que `4`. A condição de escape foi atingida. O loop é interrompido (`break`).

A função `mandelbrot_iters` retornaria o valor atual de `i`, que é `2`. Como `i < max_iter`, o programa sabe que este ponto está fora do conjunto. O valor `2` é então usado para escolher uma cor (diferente de preto), criando os padrões coloridos que vemos no fractal. Quanto mais rápido um ponto escapa (menor o `i`), mais "longe" ele está do conjunto.

---

## 3. Mapeamento de Pixels para Números Complexos (C)

A parte final para desenhar o fractal é entender como cada pixel `(x, y)` na janela da sua aplicação é transformado em um número complexo `C = cr + ci` para ser usado na função `mandelbrot_iters`. O objetivo é "esticar" a tela do computador para cobrir uma região específica do plano complexo (geralmente de -2 a 2 nas partes real e imaginária).

As fórmulas para este mapeamento são:

```c
double scale = 4.0 / d->w; // Determina a escala inicial
double cr = (x - d->w / 2.0) * scale / d->zoom + d->shift_x;
double ci = (y - d->h / 2.0) * scale / d->zoom + d->shift_y;
```

Onde:
- `x`, `y`: Coordenadas do pixel na tela (por exemplo, de 0 a `d->w-1` para `x`, e de 0 a `d->h-1` para `y`).
- `d->w`, `d->h`: Largura e altura da janela em pixels.
- `d->zoom`: Fator de zoom (1.0 para sem zoom).
- `d->shift_x`, `d->shift_y`: Deslocamentos no plano complexo para navegação.

### Exemplo de Mapeamento:

Vamos considerar uma janela de `800x600` pixels e sem zoom ou deslocamento inicial (`d->w = 800`, `d->h = 600`, `d->zoom = 1.0`, `d->shift_x = 0.0`, `d->shift_y = 0.0`).

Primeiro, calculamos `scale`:
`scale = 4.0 / 800 = 0.005`

#### Exemplo A: Pixel (200, 300)

- **Calculando `cr`:**
  `cr = (200 - 800 / 2.0) * 0.005 / 1.0 + 0.0`
  `cr = (200 - 400) * 0.005`
  `cr = -200 * 0.005`
  `cr = -1.0`

- **Calculando `ci`:**
  `ci = (300 - 600 / 2.0) * 0.005 / 1.0 + 0.0`
  `ci = (300 - 300) * 0.005`
  `ci = 0 * 0.005`
  `ci = 0.0`

Para o pixel `(200, 300)`, o número complexo `C` correspondente é **`-1.0 + 0.0i`**.

#### Exemplo B: Pixel (600, 150)

- **Calculando `cr`:**
  `cr = (600 - 800 / 2.0) * 0.005 / 1.0 + 0.0`
  `cr = (600 - 400) * 0.005`
  `cr = 200 * 0.005`
  `cr = 1.0`

- **Calculando `ci`:**
  `ci = (150 - 600 / 2.0) * 0.005 / 1.0 + 0.0`
  `ci = (150 - 300) * 0.005`
  `ci = -150 * 0.005`
  `ci = -0.75`

Para o pixel `(600, 150)`, o número complexo `C` correspondente é **`1.0 - 0.75i`**.

#### Exemplo C: Pixel Central com Deslocamento Horizontal

Vamos usar as seguintes configurações:
- `d->w = 800`
- `d->h = 800`
- `d->zoom = 1.0`
- `d->shift_x = -0.5` (desloca a visualização 0.5 unidades para a esquerda no plano complexo)
- `d->shift_y = 0.0`

Calculando `scale` (mantém o mesmo valor se `d->w` for 800):
`scale = 4.0 / 800 = 0.005`

Vamos calcular o `C` para o pixel central da tela: `(x = 400, y = 400)`

- **Calculando `cr`:**
  `cr = (400 - 800 / 2.0) * 0.005 / 1.0 + (-0.5)`
  `cr = (400 - 400) * 0.005 - 0.5`
  `cr = 0 * 0.005 - 0.5`
  `cr = -0.5`

- **Calculando `ci`:**
  `ci = (400 - 800 / 2.0) * 0.005 / 1.0 + 0.0`
  `ci = (400 - 400) * 0.005 + 0.0`
  `ci = 0 * 0.005 + 0.0`
  `ci = 0.0`

Para o pixel central `(400, 400)` com estas configurações, o número complexo `C` correspondente é **`-0.5 + 0.0i`**.

Este exemplo demonstra como o `d->shift_x` (e `d->shift_y` se fosse diferente de zero) move o centro do plano complexo que está sendo visualizado. Em vez do centro da tela corresponder a `0.0 + 0.0i`, ele agora corresponde a `-0.5 + 0.0i`, efetivamente "panorando" a imagem para a direita para revelar diferentes partes do fractal.

#### Exemplo D: Pixel Superior Esquerdo (0,0) com Deslocamento Horizontal

Usando a mesma configuração do Exemplo C:
- `d->w = 800`
- `d->h = 800`
- `d->zoom = 1.0`
- `d->shift_x = -0.5`
- `d->shift_y = 0.0`

`scale = 4.0 / 800 = 0.005`

Vamos calcular o `C` para o pixel `(x = 0, y = 0)`:

- **Calculando `cr`:**
  `cr = (0 - 800 / 2.0) * 0.005 / 1.0 + (-0.5)`
  `cr = (0 - 400) * 0.005 - 0.5`
  `cr = -400 * 0.005 - 0.5`
  `cr = -2.0 - 0.5`
  `cr = -2.5`

- **Calculando `ci`:**
  `ci = (0 - 800 / 2.0) * 0.005 / 1.0 + 0.0`
  `ci = (0 - 400) * 0.005 + 0.0`
  `ci = -400 * 0.005 + 0.0`
  `ci = -2.0`

Para o pixel `(0, 0)` com estas configurações, o número complexo `C` correspondente é **`-2.5 - 2.0i`**.


---

Com este mapeamento, cada pixel da tela obtém seu próprio número complexo `C`, que é então alimentado ao algoritmo de escape time para determinar sua cor. É assim que a imagem final do fractal é construída, pixel por pixel.
