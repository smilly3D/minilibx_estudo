# Guia: Entendendo o Fractal de Julia em C

Este documento explica a diferença fundamental entre os conjuntos de Mandelbrot e Julia e como o algoritmo é adaptado para desenhar um fractal de Julia.

## 1. A Matemática: O que é o Conjunto de Julia?

Assim como Mandelbrot, o conjunto de Julia também é um conjunto de **números complexos** gerado por uma fórmula de iteração. A fórmula é idêntica:

- `Z_{n+1} = Z_n^2 + C`

A diferença crucial está em como `Z` e `C` são definidos:

- **Para Mandelbrot**:
    - `Z` sempre começa em `0` (`Z_0 = 0`).
    - `C` é o número complexo correspondente à coordenada `(x, y)` de **cada pixel**.

- **Para Julia**:
    - `C` é um **número complexo constante** para a imagem inteira. Ele não muda de pixel para pixel. Esse `C` é o que define "qual" conjunto de Julia estamos vendo.
    - `Z` começa com o valor do número complexo correspondente à coordenada `(x, y)` de **cada pixel**.

Em resumo:
- No Mandelbrot, você testa muitos `C`s e começa `Z` do zero.
- No Julia, você escolhe **um** `C` e testa muitos `Z`s iniciais.

**A condição de escape** é a mesma: se em algum momento o módulo de `Z` (`|Z|`) exceder 2, o ponto é considerado fora do conjunto.

## 2. Traduzindo para o Código

A tradução dos números complexos e da fórmula `Z^2 + C` é exatamente a mesma do Mandelbrot.

- `C = julia_re + julia_im*i` (uma constante para todo o fractal)
- `Z = zr + zi*i` (o valor inicial muda para cada pixel)

O cálculo em cada iteração permanece:
- **Nova parte real (`zr_new`)**: `(zr^2 - zi^2) + julia_re`
- **Nova parte imaginária (`zi_new`)**: `(2*zr*zi) + julia_im`

E a condição de escape em C também: `(zr*zr + zi*zi) > 4.0`.

## 3. O Algoritmo "Escape Time" para Julia em C

O algoritmo para um único pixel `(x, y)` funciona assim:

1.  **Escolha um `C` constante**: `julia_re` e `julia_im` são definidos uma vez no início do programa.
2.  **Determine o `Z` inicial**: `zr` e `zi` são calculados a partir da posição `(x, y)` do pixel.
3.  **Inicie o contador**: `int i = 0;`
4.  **Loop**: Repita enquanto `i < max_iter`:
    a. Calcule os novos `zr` e `zi` usando o `C` constante:
       ```c
       double zr_new = zr*zr - zi*zi + d->julia_re;
       double zi_new = 2*zr*zi + d->julia_im;
       ```
    b. Atualize `Z`:
       ```c
       zr = zr_new;
       zi = zi_new;
       ```
    c. Verifique a condição de escape:
       ```c
       if (zr*zr + zi*zi > 4.0)
           break; // O ponto escapou!
       ```
    d. Incremente o contador: `i++;`
5.  **Retorne o resultado**: O valor `i` é usado para colorir o pixel, da mesma forma que no Mandelbrot.

Isso é o que a função `julia_iters` faz:

```c
// d->julia_re e d->julia_im são as constantes para o fractal
int	julia_iters(t_data *d, double zr, double zi,
					double *zr_out, double *zi_out)
{
	int i = 0;
	while (i < d->max_iter)
	{
		// Passo 4.a e 4.b
		double zr2 = zr * zr - zi * zi + d->julia_re;
		double zi2 = 2 * zr * zi + d->julia_im;
		zr = zr2;
		zi = zi2;

		// Passo 4.c
		if (zr * zr + zi * zi > 4.0)
			break ;
		i++;
	}
	*zr_out = zr;
	*zi_out = zi;
	return (i); // Passo 5
}
```

## 4. Mapeando Pixels para Números Complexos (Z inicial)

Em `render_fractal`, o mapeamento que antes definia `C` agora define o valor inicial de `Z`.

```c
// O mapeamento de pixel para o plano complexo
double zr_init = (x - d->w/2.0) * scale / d->zoom + d->shift_x;
double zi_init = (y - d->h/2.0) * scale / d->zoom + d->shift_y;

// O valor inicial de Z (zr_init, zi_init) é passado para a função
int it = julia_iters(d, zr_init, zi_init, &zr_out, &zi_out);
```

O `C` constante (`d->julia_re`, `d->julia_im`) é lido de dentro da função `julia_iters`, garantindo que o mesmo valor seja usado para cada pixel na tela.
