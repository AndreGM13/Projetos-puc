#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long p = 6399395417ULL; //teste primos com 10 digitos
unsigned long long q = 2196825613ULL;
#define n (p*q) 
unsigned long long e =  65537; //por padrão da industria (pesquisar "hamming weight")
unsigned long long d = 0;

/*
    chave pública = (e , n)
    chave privada = (d , n)
*/

char* encriptarMensagem(char);
char* decriptarMensagem(char);
unsigned long long squareAndMultiply(unsigned long long, unsigned long long);
unsigned long long calcular_d(unsigned long long, unsigned long long);

int main(){
    unsigned long long phi = (p - 1) * (q - 1);
    unsigned long long d = calcular_d(e,phi);
    printf("chave publica: (%d, %d)\n", e, n);
    printf("chave privada: (%d, %d)\n", d , n);
    char mensagem[] = "Hello World!";
    int tamanho = strlen(mensagem);

    printf("\nMensagem original: \"%s\" \n\n", mensagem);

    unsigned long long texto_cifrado[100]; 
    char texto_decriptado[100];

    clock_t inicio = clock();

    for (int i = 0; i < tamanho; i++) {
        unsigned long long m_letra = (unsigned long long)mensagem[i]; 
        
        texto_cifrado[i] = squareAndMultiply(m_letra, e);
        
        printf("Letra '%c' -> %llu\n", mensagem[i], texto_cifrado[i]);
    }
    
    clock_t fim = clock();


    printf("\ntempo de encriptacao da mensagem = %e segundos\n", (double)((fim - inicio)/CLOCKS_PER_SEC));

    //decriptação
    for (int i = 0; i < tamanho; i++) {
        unsigned long long m_original = squareAndMultiply(texto_cifrado[i], d);
        
        texto_decriptado[i] = (char)m_original;
    }
    
    texto_decriptado[tamanho] = '\0'; 
    
    printf("\nMensagem Final: \"%s\"\n", texto_decriptado);

    return 0;
}

unsigned long long squareAndMultiply(unsigned long long m, unsigned long long exp) {
    unsigned long long resultado = 1;
    m = m % n; 
    if (m == 0) return 0;

    while (exp > 0) {
        if (exp & 1) {
            resultado = (unsigned long long)(((unsigned __int128)resultado * m) % n);
        }
        
        m = (unsigned long long)(((unsigned __int128)m * m) % n);
        exp >>= 1;
    }
    return resultado;
}

unsigned long long calcular_d(unsigned long long e, unsigned long long phi) {
    __int128 t = 0, novo_t = 1;
    __int128 r = phi, novo_r = e;
    
    while (novo_r != 0) {
        __int128 quociente = r / novo_r;
        
        __int128 temp_t = t - quociente * novo_t;
        t = novo_t;
        novo_t = temp_t;
        
        __int128 temp_r = r - quociente * novo_r;
        r = novo_r;
        novo_r = temp_r;
    }
    
    if (t < 0) {
        t = t + phi;
    }
    
    return (unsigned long long)t;
}
