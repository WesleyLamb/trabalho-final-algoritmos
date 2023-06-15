#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define BUFFER_SIZE 4096

struct RoI {
	int ci;
	int li;
	int cf;
	int lf;
};

/**
 * Função recursiva que procura determinada palavra na sequência, se todas as letras forem encontradas na ordem, retorna true, senão, retorna false;
*/
bool _recursiveLocate(char **grade, const int dimensoesGrade, const char *palavra, const int length, const int currentChar, const int lastI, const int lastJ, const int stepI, const int stepJ, int *finalX, int *finalY) {
    // Primeiro verifica se a letra que está sendo buscada não está violando as margens da grade
    if ((lastI + stepI >= 0) && 
            (lastI + stepI < dimensoesGrade) && 
            (lastJ + stepJ >= 0) && 
            (lastJ + stepJ < dimensoesGrade)) {
        // Depois verifica se a letra a ser buscada é igual
        if ((palavra[currentChar] == grade[lastI + stepI][lastJ + stepJ])) {
            // Se a letra a ser buscada é a última letra da palavra, significa que todas as demais letras estão certas e só falta essa letra
            // Se não for, chama a função novamente para procurar a próxima letra
            if (currentChar == length - 1) {
                *finalX = lastJ + stepJ;
                *finalY = lastI + stepI;
                return true;
            } else {
                return _recursiveLocate(grade, dimensoesGrade, palavra, length, currentChar + 1, lastI + stepI, lastJ + stepJ, stepI, stepJ, finalX, finalY);
            }
        }
    }
    return false;
}

/**
 * Lê uma linha do stdin e retorna um ponteiro para a string
 * Fonte: https://www.youtube.com/watch?v=4_2BEgOFd0E
*/
char* getLn() {
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    int length = 0;

    // Lê a linha
    fgets(buffer, BUFFER_SIZE, stdin);
    length = strlen(buffer);
    // Remove a quebra de linha e substitui por \0
    buffer[length - 1] = '\0';
    return buffer;
}

/**
 * Conta quantas vezes o caractere needle aparece na string haystack
*/
int strCount(char *haystack, char needle) {
    int count = 0;
    int length = strlen(haystack);
    for (int i = 0; i < length; i++) {
        if (haystack[i] == needle)
            count++;
    }
    return count;
}

/**
 * Separa a string haystack em substrings, usando o caractere needle como separador
 * Retorna um vetor de strings e o tamanho do vetor em length
*/
char** strSplit(char *haystack, const char needle, int *length) {
    char **result = 0;
	char *token;
	int count = strCount(haystack, needle), i = 0;

	result = malloc(count * sizeof(char*));
    token = strtok(haystack, &needle);
    while (token != NULL) {
        result[i] = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(result[i], token);
        token = strtok(NULL, &needle);
        i++;
    }
    *length = i;
    return result;
}

/**
 * Procura por ocorrências de needle em haystack e os substitui por replace
*/
void strReplace(char *haystack, const char needle, const char replace) {
    for (int i = 0; i < strlen(haystack); i++) {
        if (haystack[i] == needle)
            haystack[i] = replace;
    }
}

/**
 * Converte uma string em uppercase
*/
void strUpper(char *haystack) {
    for (int i = 0; i < strlen(haystack); i++)
        haystack[i] = (char) toupper((int) haystack[i]);
}

void padronizar(char *haystack) {
    strReplace(haystack, ' ', '-');
    strUpper(haystack);
}

/**
 * Verifica se um número é quadrado perfeito
*/
bool sqrtIsInt(int n) {
    int i = 1;
    while (i * i < n) {
        i++;
    }
    return i * i == n;
}

/**
 * Monta uma matriz quadrada a partir de uma string
*/
char** montarGrade(const char *grade, int *dimensaoGrade) {
    char **matGrade;

    *dimensaoGrade = (int) sqrt(strlen(grade));
    matGrade = (char **) malloc((*dimensaoGrade) * sizeof(char*));
    for (int i = 0; i < (*dimensaoGrade); i++) {
        matGrade[i] = (char * ) malloc((*dimensaoGrade) * sizeof(char));
    }
    
    for (int i = 0; i < (*dimensaoGrade); i++) {
        for (int j = 0; j < (*dimensaoGrade); j++) {
            matGrade[i][j] = grade[i * (*dimensaoGrade) + j];
        }
    }
    return matGrade;
}

struct RoI localizarPalavra(char **grade, const int dimensoesGrade, const char *palavra) {
    struct RoI result;
    int contLetras = strlen(palavra), i, j, k, iAux, jAux, passoI = 0, passoJ = 0;
    bool encontrou = false;

    // Localiza a primeira letra da palavra
    for (int i = 0; (i < dimensoesGrade) && (!encontrou); i++) {
        for (int j = 0; (j < dimensoesGrade) && (!encontrou); j++) {
            if ((grade[i][j] == palavra[0])) {
                result.ci = j;
                result.li = i;

                for (passoI = -1; (passoI <= 1) && (!encontrou); passoI++){
                    for (passoJ = -1; (passoJ <= 1) && (!encontrou); passoJ++) {
                        encontrou = _recursiveLocate(grade, dimensoesGrade, palavra, contLetras, 1, i, j, passoI, passoJ, &result.cf, &result.lf);
                    }
                }

                if (!encontrou)
                    result.ci = result.cf = result.li = result.lf = 0;
            }
        }
    }

    return result;
}

/**
 * Exibe a grade desenhada no console
*/
void desenharGrade(char **grade, const int dimensoesGrade) {
    for (int i = 0; i < dimensoesGrade; i++) {
        for (int j = 0; j < dimensoesGrade; j++) {
            printf("%c ", grade[i][j]);
        }
        printf("\n");
    }
}

/**
 * Exibe as palavras e suas localizaçòes no console
*/
void listarResultados(struct RoI *regioes, char **palavras, const int contPalavras) {
    printf("Palavra => li, ci, lf, cf\n");
    for (int i = 0; i < contPalavras; i++) {
        printf("%s => %d, %d, %d, %d\n", palavras[i], regioes[i].li, regioes[i].ci, regioes[i].lf, regioes[i].cf);
    }
}

int main(int argc, char *argv[]) {
    char *entradaGrade, *entradaPalavras, **palavras, **grade;
    int contPalavras = 0, i = 0, dimensoesGrade = 0;
    struct RoI *regioes;

    printf("Digite a grade de letras:\n");
    entradaGrade = getLn();
    if (!sqrtIsInt(strlen(entradaGrade))) {
        fprintf(stderr, "A grade deve ser um quadrado perfeito.\n");
        return 1;
    }
    padronizar(entradaGrade);
    grade = montarGrade(entradaGrade, &dimensoesGrade);

    printf("Digite as palavras a serem encontradas, separadas por virgula:\n");
    entradaPalavras = getLn();
    if (entradaPalavras == "") {
        fprintf(stderr, "Pelo menos uma palavra deve ser informada.\n");
        return 1;
    }
    padronizar(entradaPalavras);
    if (strCount(entradaPalavras, ',') == 0) {
        palavras = (char **) malloc(sizeof(char *));
        palavras[0] = entradaPalavras;
        contPalavras = 1;
    } else {
        palavras = strSplit(entradaPalavras, ',', &contPalavras);
    }

    regioes = malloc(contPalavras * sizeof(struct RoI));
    for (i = 0; i < contPalavras; i++) {
        regioes[i] = localizarPalavra(grade, dimensoesGrade, palavras[i]);
    }

    printf("\n");
    desenharGrade(grade, dimensoesGrade);
    printf("\n");
    listarResultados(regioes, palavras, contPalavras);
    printf("\n");

    // Só pra não fechar o terminal no windolos
    getLn();
    return 0;
}