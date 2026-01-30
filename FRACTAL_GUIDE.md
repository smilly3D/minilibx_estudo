# Guia: Entendendo o Fractal de Mandelbrot em C

Este documento explica, passo a passo, como a famosa fórmula matemática do conjunto de Mandelbrot é transformada em um programa em C que desenha o fractal.

## 1. A Matemática: O que é o Conjunto de Mandelbrot?

O conjunto de Mandelbrot é um conjunto de **números complexos**. Um número complexo `C` pertence a este conjunto se a sequência definida por:

- `Z_0 = 0`
- `Z_{n+1} = Z_n^2 + C`

**não diverge** (ou seja, não tende ao infinito) à medida que `n` aumenta.

Vamos detalhar:
- **`C`**: É um número complexo. Cada pixel na nossa imagem corresponderá a um número `C` diferente.
- **`Z`**: É outro número complexo, cujo valor muda a cada iteração. A sequência sempre começa com `Z = 0`.
- **Iteração**: Para cada `C` (cada pixel), repetimos o cálculo `Z = Z^2 + C` várias vezes.

A "mágica" está em como `Z` se comporta. Para alguns valores de `C`, o valor de `Z` fica sempre próximo da origem (0,0). Para outros, ele "escapa" e cresce rapidamente para o infinito.

**A condição de escape**: Matematicamente, foi provado que se o módulo (distância até a origem) de `Z` se tornar maior que 2, ele certamente irá para o infinito. É o nosso teste para saber se um ponto `C` está fora do conjunto.

## 2. Traduzindo para o Código

Computadores não trabalham nativamente com "números complexos". Nós os representamos usando dois números de ponto flutuante (doubles): a parte **real** e a parte **imaginária**.

- `C = cr + ci*i` (onde `cr` é a parte real, `ci` é a imaginária)
- `Z = zr + zi*i` (onde `zr` é a parte real, `zi` é a imaginária)

Agora, vamos reescrever a fórmula `Z_{n+1} = Z_n^2 + C` usando essas partes.

#### Calculando `Z^2`

`Z^2 = (zr + zi*i)^2 = zr^2 + 2*zr*zi*i + (zi*i)^2`
Como `i^2 = -1`, temos:
`Z^2 = (zr^2 - zi^2) + (2*zr*zi)i`

- Parte real de `Z^2`: `zr^2 - zi^2`
- Parte imaginária de `Z^2`: `2*zr*zi`

#### Calculando `Z^2 + C`

Agora somamos `C` (`cr + ci`):
- **Nova parte real (`zr_new`)**: `(zr^2 - zi^2) + cr`
- **Nova parte imaginária (`zi_new`)**: `(2*zr*zi) + ci`

Essas são as duas linhas de código mais importantes dentro do loop de iteração.

#### A Condição de Escape em Código

A condição `|Z| > 2` também precisa ser traduzida.
O módulo ao quadrado, `|Z|^2`, é `zr^2 + zi^2`.
Para evitar o cálculo de uma raiz quadrada (que é computacionalmente caro), comparamos o quadrado dos valores:
`|Z|^2 > 4`  é o mesmo que `|Z| > 2`.

Então, a nossa condição de escape em C é `(zr*zr + zi*zi) > 4.0`.

## 3. O Algoritmo "Escape Time" em C

Juntando tudo, o algoritmo para um único pixel (um único `C`) funciona assim:

1.  **Escolha um `C`**: `cr` e `ci` são determinados pela posição (x, y) do pixel na tela.
2.  **Inicialize `Z`**: `zr = 0.0; zi = 0.0;`
3.  **Inicie o contador**: `int i = 0;`
4.  **Loop**: Repita enquanto `i < max_iter` (um limite máximo de iterações):
    a. Calcule os novos `zr` e `zi`:
       ```c
       double zr_new = zr*zr - zi*zi + cr;
       double zi_new = 2*zr*zi + ci;
       ```
    b. Atualize `Z`:
       ```c
       zr = zr_new;
       zi = zi_new;
       ```
    c. Verifique a condição de escape:
       ```c
       if (zr*zr + zi*zi > 4.0)
           break; // O ponto escapou! Pare o loop.
       ```
    d. Incremente o contador: `i++;`
5.  **Retorne o resultado**: O valor final de `i` nos diz "quão rápido" o ponto escapou.
    - Se `i == max_iter`, o ponto provavelmente está **dentro** do conjunto (ele não escapou).
    - Se `i < max_iter`, o ponto está **fora** do conjunto. O valor de `i` pode ser usado para escolher uma cor.

Isso é exatamente o que a função `mandelbrot_iters` faz:

```c
int mandelbrot_iters(double cr, double ci, int max_iter)
{
    double zr = 0, zi = 0;
    int i = 0;
    while (i < max_iter)
    {
        // Passo 4.a e 4.b combinados
        double zr2 = zr*zr - zi*zi + cr;
        double zi2 = 2*zr*zi + ci;
        zr = zr2; zi = zi2;

        // Passo 4.c
        if (zr*zr + zi*zi > 4.0)
            break;
        i++;
    }
    return i; // Passo 5
}
```

## 4. Mapeando Pixels para Números Complexos

A última peça do quebra-cabeça é como `render_fractal` atribui um número complexo `C` para cada pixel `(x, y)`:

```c
// escala para caber a visualização padrão de -2 a 2
double scale = 4.0 / d->w; 
// ...
double cr = (x - d->w/2.0) * scale / d->zoom + d->shift_x;
double ci = (y - d->h/2.0) * scale / d->zoom + d->shift_y;
```
- `(x - d->w/2.0)`: Centraliza a coordenada `x` na origem (0). O resultado varia de `-d->w/2` a `+d->w/2`.
- `* scale`: Ajusta a coordenada para o plano complexo. Agora, a variação vai de -2.0 a +2.0.
- `/ d->zoom + d->shift_x`: Aplica o zoom e o deslocamento para navegação.

O mesmo é feito para `y` e `ci`. Agora, cada pixel corresponde a um ponto `C` único no plano complexo, pronto para ser testado pela função `mandelbrot_iters`.
