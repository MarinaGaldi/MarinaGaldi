#include <stdio.h>

int mdc(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a; 
}

int inverso_modular(int g, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = g;

    printf("Iniciando algoritmo estendido de Euclides para encontrar o inverso modular...\n\n");

    while (novo_r != 0) {
        int quociente = r / novo_r;

        printf("quociente = %d, t = %d, novo_t = %d, r = %d, novo_r = %d\n",
               quociente, t, novo_t, r, novo_r);

        int temp = t;
        t = novo_t;
        novo_t = temp - quociente * novo_t;

        temp = r;
        r = novo_r;
        novo_r = temp - quociente * novo_r;
    }

    if (r > 1) return -1;

    if (t < 0) t += n;

    return t;
}

int primo(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int tot(int n) {
    int resultado = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            resultado -= resultado / p;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
    return resultado;
}

int exp_modular(int base, int expoente, int mod) {
    int resultado = 1;
    base = base % mod;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        expoente = expoente / 2;
    }
    return resultado;
}

int main() {
    int H, G, n, x, n1;

    printf("====================================================\n");
    printf("    CALCULADORA MODULAR EXPLICATIVA PASSO A PASSO   \n");
    printf("====================================================\n\n");
    printf("Este programa realiza a operação modular H ⊘ G em Zn,\n");
    printf("e calcula a^x mod n1 com base nos teoremas de Fermat ou Euler.\n\n");

    printf("Digite os valores de H, G, n, x e n1 (separados por espaço): \n");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);
    printf("Valores escolhidos: H = %d, G = %d, n = %d, x = %d, n1 = %d.\n", H, G, n, x, n1);

    printf("\n1. Verificando se G e n são coprimos...\n");
    if (mdc(G, n) != 1) {
        printf("G e n NÃO são coprimos. A divisão modular não é possível.\n");
        return 1;
    } else {
        printf("G e n são coprimos pois mdc(%d, %d) = 1.\n", G, n);
        printf("Portanto, é possível realizar a divisão H ⊘ G em Z%d.\n", n);
    }

    printf("\n2. Calculando o inverso modular de G em Zn usando o algoritmo de Euclides estendido...\n");
    int inverso_de_G_em_Zn = inverso_modular(G, n);
    if (inverso_de_G_em_Zn == -1) {
        printf("\nO inverso modular não existe. A divisão não é possivel.\n");
        return 1;
    } else {
        printf("\nInverso modular encontrado: G⁻¹ = %d\n", inverso_de_G_em_Zn);
        printf("Isso significa que %d * %d ≡ 1 mod %d\n", G, inverso_de_G_em_Zn, n);
    }

    int a = (H * inverso_de_G_em_Zn) % n;
    printf("\n3. Calculando a = H * G⁻¹ mod n...\n");
    printf("a = (%d * %d) mod %d = %d\n", H, inverso_de_G_em_Zn, n, a);
    printf("Esse valor 'a' será usado como base da exponenciação a^x mod n1.\n");

    printf("\n4. Verificando se a e n1 são coprimos...\n");
    if (mdc(a, n1) != 1) {
        printf("a e n1 NÃO são coprimos. Teoremas de Fermat/Euler não se aplicam.\n");
        return 1;
    } else {
        printf("a e n1 são coprimos pois mdc(%d, %d) = 1.\nSeguimos com a aplicação do teorema adequado.\n", a, n1);
    }

    int x1;
    printf("\n5. Verificando se n1 é primo...\n");
    if (primo(n1)) {
        printf("n1 é primo, então aplicamos o Pequeno Teorema de Fermat:\n");
        printf("a^(n1 - 1) ≡ 1 mod n1, logo x1 = %d - 1 = %d\n", n1 ,n1 - 1);
        x1 = n1 - 1;
    } else {
        printf("n1 NÃO é primo, aplicamos o Teorema de Euler:\n");
        x1 = tot(n1);
        printf("φ(%d) = %d, então x1 = %d\n", n1, x1, x1);
    }

    int q = x / x1;
    int r = x % x1;
    printf("\n6. Decompondo x na forma x = x1 * q + r:\n");
    printf("Isso nos permite reescrever a^x de modo a facilitar o cálculo modular.\n");
    printf("%d = %d * %d + %d\n", x, x1, q, r);

    printf("\n7. Calculando a^x mod n1 usando a decomposição:\n");
    printf("Utilizando propriedades de potência modular: a^x ≡ (a^x1)^q * a^r mod n1\n");
    printf("Isso evita operações com expoentes muito grandes, tornando o cálculo eficiente.\n\n");

    int ax1 = exp_modular(a, x1, n1);
    int ax1q = exp_modular(ax1, q, n1);
    int ar = exp_modular(a, r, n1);
    int resultado = (ax1q * ar) % n1;

    printf("a^%d mod %d = %d\n", x1, n1, ax1);
    printf("(a^%d)^%d mod %d = %d\n", x1, q, n1, ax1q);
    printf("a^%d mod %d = %d\n", r, n1, ar);

    printf("\n8. Resultado final:\n");
    printf("a^%d mod %d = %d\n", x, n1, resultado);

    printf("\nResumo dos passos:\n");
    printf("1. Verificação de coprimalidade entre G e n.\n");
    printf("2. Cálculo do inverso modular de G em Zn.\n");
    printf("3. Cálculo da base a = H * G⁻¹ mod n.\n");
    printf("4. Verificação de coprimalidade entre a e n1.\n");
    printf("5. Determinação de x1 com base em Fermat ou Euler.\n");
    printf("6. Decomposição de x = x1 * q + r para facilitar a exponenciação.\n");
    printf("7. Aplicação de exponenciação modular para calcular a^x mod n1.\n");

    return 0;
}