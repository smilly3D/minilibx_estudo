# Subject 02: Cores Psicodélicas

Com a interatividade dominada, o próximo passo é fazer nosso fractal ficar ainda mais bonito. O gradiente de cores linear que usamos é funcional, mas podemos fazer melhor.

## Objetivos

1.  **Implementar "Smooth Coloring"**: O método atual cria "bandas" de cor. Pesquise e implemente um algoritmo de coloração suave ("smooth coloring"). Isso envolve usar o valor final de `Z` para calcular uma parte fracionária do número de iterações, resultando em gradientes perfeitos.

2.  **Cores Dinâmicas**: Crie um esquema de cores mais interessante. Uma técnica popular é usar funções de seno e cosseno para gerar cores que mudam suavemente, criando um efeito psicodélico.

3.  **Interação de Cor**: Adicione um hook de teclado (por exemplo, a tecla `C`) que mude o esquema de cores em tempo real. Isso pode ser feito alterando uma variável de "phase shift" que é usada nos cálculos de seno/cosseno.

4.  **Linkar a Biblioteca Matemática**: Funções como `sin`, `log` e `sqrt` exigem a inclusão de `<math.h>` e a linkagem com a biblioteca matemática. Você precisará adicionar `-lm` aos flags do seu compilador no `Makefile`.

## Dicas

- A fórmula para a iteração suave (`smooth_i`) é:
  `i + 1 - log(log(sqrt(zr*zr + zi*zi))) / log(2.0)`
- Brinque com as frequências e fases das funções `sin` para criar paletas de cores únicas.
- Lembre-se de setar a `flag dirty` quando a cor for alterada para forçar o redesenho.
