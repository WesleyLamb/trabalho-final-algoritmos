#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

/**
 * Lê uma linha do stdin e retorna um ponteiro para a string
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

int main() {
    char **strings;
    char *helper;
    int length = 0;

    printf("Informe palavras separadas por virgula:");
    helper = getLn();
    strings = strSplit(helper, ',', &length);
    for (int i = 0; i < length; i++) {
        printf("strings[%d] = %s\n", i, strings[i]);
    }
    printf("\n");

    return 0;
}