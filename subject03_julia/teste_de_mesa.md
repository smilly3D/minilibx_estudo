# Teste de Mesa Visual: Fractal de Julia

Este documento demonstra o algoritmo do "tempo de escape" do Julia em ação. Usaremos uma constante `C` e dois pontos `Z` iniciais diferentes para ver como a sequência se comporta.

-   **Constante `C` escolhida:** `C = -0.8 (cr) + 0.156 (ci)`
-   **`max_iter` (máximo de iterações):** `10` para simplificar.

A fórmula-chave é a mesma do Mandelbrot: `Z_{n+1} = Z_n^2 + C`. A diferença é que `C` é fixo e `Z` começa no ponto do pixel.

**Condição de escape:** `zr^2 + zi^2 > 4`

---

## Exemplo 1: Um Ponto DENTRO do Conjunto (Provavelmente)

Vamos testar um ponto `Z` inicial que está próximo da origem.
- **`Z_0 = 0.2 (zr) + 0.1 (zi)`**

**Objetivo:** Ver se o valor de `Z` permanece pequeno e não "escapa".

**Tabela de Iterações:** (`cr` = -0.8, `ci` = 0.156)

| Iteração (i) | `zr` (inicial) | `zi` (inicial) | `zr_new = zr²-zi²+cr` | `zi_new = 2*zr*zi+ci` | `zr²+zi² > 4`? | `Z` (final) |
|:------------:|:--------------:|:--------------:|:-------------------------:|:-----------------------:|:---------------:|:----------------------:|
| **0** | `0.2` | `0.1` | 0.2²-0.1²-0.8 = **-0.77** | 2*0.2*0.1+0.156 = **0.196** | `0.2²+0.1²=0.05`. Não. | `(-0.77, 0.196)` |
| **1** | `-0.77` | `0.196` | (-0.77)²-0.196²-0.8 = **-0.245** | 2*(-0.77)*0.196+0.156 = **-0.146**| `(-0.77)²+0.196²=0.63`. Não.| `(-0.245, -0.146)`|
| **2** | `-0.245`| `-0.146`| (-0.245)²-(-0.146)²-0.8 = **-0.761**| 2*(-0.245)*(-0.146)+0.156 = **0.227**| `(-0.245)²+(-0.146)²=0.08`.Não| `(-0.761, 0.227)`|
| **...** | ... | ... | ... | ... | ... | ... |
| **9** | ... | ... | (continua pequeno) | (continua pequeno) | Não. | ... |
| **10**| ... | ... | (loop termina) | (loop termina) | Não. | ... |

**Conclusão para o Ponto 1:**
A condição de escape nunca foi atingida. O loop completou as `10` iterações. A função `julia_iters` retornaria `10`. O programa colore este pixel com a cor "interior" (geralmente preto).

---

## Exemplo 2: Um Ponto FORA do Conjunto

Agora, vamos testar um ponto `Z` inicial mais distante.
- **`Z_0 = 1.5 (zr) + 1.5 (zi)`**

**Objetivo:** Ver como e quando o valor de `Z` "escapa" (cresce rapidamente).

**Tabela de Iterações:** (`cr` = -0.8, `ci` = 0.156)

| Iteração (i) | `zr` (inicial) | `zi` (inicial) | `zr_new = zr²-zi²+cr` | `zi_new = 2*zr*zi+ci` | `zr²+zi² > 4`? | `Z` (final) |
|:------------:|:--------------:|:--------------:|:-------------------------:|:-----------------------:|:----------------:|:--------------------:|
| **0** | `1.5` | `1.5` | 1.5²-1.5²-0.8 = **-0.8** | 2*1.5*1.5+0.156 = **4.656** | `1.5²+1.5²=4.5`. **SIM!**| `(-0.8, 4.656)` |

**Conclusão para o Ponto 2:**
Já na **primeira verificação** (iteração `i = 0`), o valor de `|Z|^2` era `4.5`, que é maior que `4`. A condição de escape foi atingida imediatamente. O loop é interrompido (`break`).

A função `julia_iters` retornaria o valor atual de `i`, que é `0`. O programa usa esse valor para escolher uma cor, indicando que o ponto está fora do conjunto e escapou muito rapidamente.

---

## Mapeamento de Pixels para Z

O mapeamento de pixels funciona da mesma forma que no Mandelbrot, mas desta vez, os valores `cr` e `ci` calculados a partir do pixel `(x, y)` são usados como os valores **iniciais** para `zr` e `zi`, respectivamente.

```c
// Em render_fractal, para cada pixel (x, y)
double zr_inicial = (x - d->w / 2.0) * scale / d->zoom + d->shift_x;
double zi_inicial = (y - d->h / 2.0) * scale / d->zoom + d->shift_y;

// Estes valores são passados para a função de iteração
int i = julia_iters(d, zr_inicial, zi_inicial, &zr_out, &zi_out);
```

A constante `C` (`d->julia_re` e `d->julia_im`) é fixa e lida de dentro da função `julia_iters` em cada passo.
