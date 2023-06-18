# Caça-palavras

## Introdução

Código desenvolvido em C como trabalho para conclusão da matéria de algoritmos, a pedido do professor [@manassesribeiro](https://github.com/manassesribeiro).

## Finalidade

O algoritmo apresentado é uma ferramenta que pode ser utilizada para descobrir a posição das palavras em uma matriz quadrada, procurando em todas as direções, inclusive diagonais.

## Execução

É necessário dois argumentos que são requisitados ao usuário ao executar o programa:
* `Grade de letras`: Texto plano com o conteúdo da grade. Cada caractere é considerado um caractere na grade.
* `Palavras`: Texto plano com as palavras que devem ser localizadas. Informe quantas palavras quiser, separando as com `,`.

## Considerações

O algoritmo converterá as ocorrências de `espaço` para `-` e converterá todas as letras em maiúsculo, a fim de evitar incoerrências.

## Documentação dos métodos

**bool _locateRecursive**:
Esta função é utilizada para verificar se a palavra está presente em uma determinada direção.
A função procura pelo caractere `currentChar` de `palavra` em `grade` na posição `lastI + stepI` e `lastJ + stepJ`, se o caractere é correspondente, a função segue dois rumos: se o caractere de currentChar é o último caractere de palavra, a função escreve nos ponteiros `finalX` e `finalY` a posição atual, se não for a última letra, a função invoca a sí mesmo aumentando a variável `currentChar`, acrescentando `stepI` a `lastI` e `stepJ` a `lastJ` e passando adiante as demais variáveis, que não se alteram.

No programa, esta função é acionada dentro de dois loops for, onde o primeiro manipula a variável `stepI` com os valores -1, 0 e 1, que fazem a função procurar a palavra para a esquerda, mantendo-se na coluna e para a direita, respectivamente e o segundo manipula a variável `stepJ` com os mesmos valores, que fazem a função procurar a palavra para cima, mantendo-se na linha e para baixo, respectivamente.

Comportamento da função conforme os valores de `stepI` e `stepJ`, respectivamente:
![Demonstração do comportamento da função](https://i.imgur.com/hKPeTDd.png)

**char **getLn**:
Esta função serve para ler o conteúdo string recebido em stdin, [baseado neste vídeo](https://www.youtube.com/watch?v=4_2BEgOFd0E).

**int strCount**:
Conta a quantidade de ocorrências de `needle` em `haystack`.

**char **strSplit**:
Separa `haystack` a cada ocorrência de `needle` e escreve em `length` a quantidade de separações.

**void strReplace**: 
Substitui em `haystack` toda ocorrência de `needle` por `replace`.

**void strUpper**:
Transforma `haystack` em UpperCase.

**void padronizar**:
Executa os métodos **strReplace** e **strUpper** em `haystack`.

**bool sqrtIsInt**:
Verifica se a raíz quadrada de `n` é inteira.

**char montarGrade**:
Cria uma matriz de `dimensoesGrade` x `dimensoesGrade` e, em cada posição, coloca um caractere de `grade`.

**struct RoI localizarPalavra**: 
Procura por `palavra` em `grade` de tamanho `dimensoesGrade` x `dimensoesGrade`.
Esta função procura a ocorrência da primeira letra de `palavra` em `grade`. Quando localizar, chama a função **_recursiveLocate** para ver se as próximas letras da palavra estão em alguma direção. Este método retorna uma struct RoI com as posições correspondentes, Caso não encontrar, o Struct retornará zerado.


**void desenharGrade**:
Método utilizado para desenhar a matriz no console.

**void listarResultados**:
Método utilizado para imprimir as palavras e suas localizações.