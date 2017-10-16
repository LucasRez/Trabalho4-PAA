#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>

int a,b,c,d,e,f,g,n, nivel_atual = 0, nivel_max = 0;
clock_t tempo_inicial, tempo_final;
float tempo_total;
double tempo_teorico;
char exit_msg[] = "Tempo maximo de execucao excedido, saindo...";
int exit_signal = 0;
float *tempos = NULL;
int *chamadas = NULL;
char cham_filename[200], tempos_filename[200], tempo_tot_filename[200];

int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    
    return result;
}

//metodo meste a valido b valido e c tem que ser 0
//c ou d != 0 metodo mestre nao se aplica
//metodo mestre so pode ter uma das funcoes deles e nao os dois
void metodo_mestre(){
    if (c != 0 || d != 0 || a < 1 || b < 2)
    {
        printf("O metodo mestre nao se aplica\n");
        return;
    }
    printf("T(n) = %dT(n/%d) + n^%d\n", a, b, g);
    printf("b = %d, a = %d, f(n) = n^%d\n", b, a ,g);
    double log_val = log(a) / log(b);
    printf("Log de %d na base %d = %lf\n", a, b, log_val);
    double e_val = g - log_val;
    if (e_val == 0.0) {
        printf("f(n) = n^%d = Teta(n^%.0lf) -> Caso 2 do metodo mestre\n", g, log_val);
        printf("T(n) = Teta(n^%.0lf log(n))\n", log_val);
        tempo_teorico = (ipow(n, (int) log_val) * log2(n)) / 1000000.0;
    } else if (e_val < 0){
        printf("f(n) = n^%d = O(n^(%.0lf - e)), para e = %lf -> Caso 1 do metodo mestre\n", g, log_val, -e_val);
        printf("T(n) = Teta(n^%.0lf)\n", log_val);
        tempo_teorico = ipow(n, (int) log_val) / 1000000.0;
    } else {
        printf("f(n) = n^%d = Omega(n^(%.0lf + e)), para e = %lf -> Caso 3 do metodo mestre\n", g, log_val, e_val);
        if (a/b < 1) {
            printf("T(n) = Teta(n^%d)\n", g);
            tempo_teorico = ipow(n, g) / 1000000.0;
        }
        else printf("O metodo mestre nao pode ser aplicado\n");
    }
    return;
}

void sair() {
    exit_signal = 1;
}

int calculate_f (int n, int g) // conta numero iterações de f(n).
{
    
    int resultado = ipow(n,g);
    return resultado ; // retorna n^g
}

void calcula_nivel_atual_arvore(void){
    if (nivel_atual > nivel_max)
    {
        nivel_max = nivel_atual;
    }
}

void registra_trabalho_nivel_atual_arvore(float diff){
    tempos[nivel_atual] += diff;
}

void registra_trabalho_por_n(int chamadas_rec){
    chamadas[nivel_atual] += chamadas_rec;
}

void registra_trabalho_por_f_n(void){
}


void func_t (int n) // simula a recorrencia
{
    int chamadas_rec = 0;
    if (n<=1) {
        calcula_nivel_atual_arvore();
        registra_trabalho_nivel_atual_arvore(0.0);
        registra_trabalho_por_n(chamadas_rec);
        registra_trabalho_por_f_n();
    	return;
    }
    
    for (int cont=1; cont<=a; cont++){ // faz a chamadas de tamanho (n/b) - c
        chamadas_rec++;
        nivel_atual++;
        func_t( (n/b) - c );
        nivel_atual--;
    }
    
    for (int cont=1; cont<=d; cont++){ // faz d chamadas de tamanho (n/e) - f
        chamadas_rec++;
        nivel_atual++;
        func_t( (n/e) - f );
        nivel_atual--;
    }
    
    
    tempo_inicial = clock();
    // simula o tempo de f(n) no nível atual
    for (int cont=1; cont<= calculate_f(n,g) && !exit_signal; )
    {
        if (exit_signal)
        {
            printf("%s\n", exit_msg);
            break;
        }
        cont++;
    }
    tempo_final = clock();
    float diff = ((float)(tempo_final - tempo_inicial) / 1000000.0F );
    tempo_total += diff;
    
    
    calcula_nivel_atual_arvore();
    registra_trabalho_nivel_atual_arvore(diff);
    registra_trabalho_por_n(chamadas_rec);
    registra_trabalho_por_f_n();
}

int main(int argc, char const *argv[])
{
	if (argc != 9)
	{
		printf("Argumentos incorretos! Uso correto: \n");
		printf("\tcalcula_recorrencia a b c d e f g n\n");
	} else {
        signal(SIGALRM, sair);

		a = atoi(argv[1]);
		b = atoi(argv[2]);
		c = atoi(argv[3]);
		d = atoi(argv[4]);
		e = atoi(argv[5]);
		f = atoi(argv[6]);
		g = atoi(argv[7]);
		n = atoi(argv[8]);

        sprintf(cham_filename, "chamadas_%d%d%d%d%d%d%d%d", a, b, c, d, e, f, g, n);
        sprintf(tempos_filename, "tempos_%d%d%d%d%d%d%d%d", a, b, c, d, e, f, g, n);
        sprintf(tempo_tot_filename, "tempo_tot_%d%d%d%d%d%d%d%d", a, b, c, d, e, f, g, n);

		tempo_total = 0;
        tempo_teorico = -1;

        int tam_arvore = (int) ceil(log2(n));
        tempos = (float *) calloc(tam_arvore, sizeof(float));
        chamadas = (int *) calloc(tam_arvore, sizeof(int));
		
        metodo_mestre();
        alarm(360);
		func_t(n);
        alarm(0);

        FILE *cham_fp = fopen(cham_filename, "a+");
        FILE *tempos_fp = fopen(tempos_filename, "a+");
        FILE *tempo_tot_fp = fopen(tempo_tot_filename, "a+");

        if (exit_signal)
        {
            tempo_total = 360.0f;
        }

    	fprintf(tempo_tot_fp, "%f %lf ", tempo_total, tempo_teorico);
        for (int i = 0; i < tam_arvore; ++i)
        {
            fprintf(tempos_fp, "%f ", tempos[i]);
            fprintf(cham_fp, "%d ", chamadas[i]);
        }
        
        fprintf(tempos_fp, "\n");
        fprintf(cham_fp, "\n");
        free(tempos);
        free(chamadas);
        fclose(cham_fp);
        fclose(tempos_fp);
        fclose(tempo_tot_fp);
	}
	return 0;
}