#include <stdio.h>

typedef enum
{
    CONTA_ENCERRADA,
    CONTA_ATIVA
} SituacaoConta;

typedef struct
{
    long numero;
    char titular[100];
    char cpf[15];
    double saldo;
    SituacaoConta situacao;
} Conta;

int buscarConta(FILE *arquivo, long numeroConta, Conta *conta)
{
    fseek(arquivo, 0, SEEK_SET);
    while (fread(conta, sizeof(Conta), 1, arquivo) == 1)
    {
        if (conta->numero == numeroConta)
            return 1;
    }
    return 0;
}

int atualizarConta(FILE *arquivo, const Conta *conta)
{
    fseek(arquivo, -(long)sizeof(Conta), SEEK_CUR);
    return fwrite(conta, sizeof(Conta), 1, arquivo) == 1;
}

void cadastrarConta(void)
{
    Conta conta, existente;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Numero da conta: ");
    scanf("%ld", &conta.numero);

    if (buscarConta(arquivo, conta.numero, &existente))
    {
        printf("Essa conta ja existe.\n");
        fclose(arquivo);
        return;
    }

    printf("Titular: ");
    scanf("%s", conta.titular);
    printf("CPF: ");
    scanf("%s", conta.cpf);
    conta.saldo = 0;
    conta.situacao = CONTA_ATIVA;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&conta, sizeof(Conta), 1, arquivo);
    printf("Conta cadastrada.\n");

    fclose(arquivo);
}

void consultarConta(void)
{
    Conta conta;
    long numero;
    FILE *arquivo = fopen("contas.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Numero da conta: ");
    scanf("%ld", &numero);

    if (buscarConta(arquivo, numero, &conta))
    {
        printf("Numero: %ld\n", conta.numero);
        printf("Titular: %s\n", conta.titular);
        printf("CPF: %s\n", conta.cpf);
        printf("Saldo: R$ %.2f\n", conta.saldo);
        if (conta.situacao == CONTA_ATIVA)
            printf("Situacao: ATIVA\n");
        else
            printf("Situacao: ENCERRADA\n");
    }
    else
        printf("Conta nao encontrada.\n");

    fclose(arquivo);
}

int depositar(long numeroConta, double valor)
{
    Conta conta;
    int ok = 0;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
        return 0;

    if (valor > 0 && buscarConta(arquivo, numeroConta, &conta) && conta.situacao == CONTA_ATIVA)
    {
        conta.saldo = conta.saldo + valor;
        ok = atualizarConta(arquivo, &conta);
    }

    fclose(arquivo);
    return ok;
}

int sacar(long numeroConta, double valor)
{
    Conta conta;
    int ok = 0;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
        return 0;

    if (valor > 0 && buscarConta(arquivo, numeroConta, &conta) &&
        conta.situacao == CONTA_ATIVA && conta.saldo >= valor)
    {
        conta.saldo = conta.saldo - valor;
        ok = atualizarConta(arquivo, &conta);
    }

    fclose(arquivo);
    return ok;
}

int transferir(long contaOrigem, long contaDestino, double valor)
{
    Conta origem, destino;
    FILE *arquivo;

    if (contaOrigem == contaDestino || valor <= 0)
        return 0;

    arquivo = fopen("contas.dat", "rb");
    if (arquivo == NULL)
        return 0;

    /* verifica tudo antes de mexer nos saldos */
    if (!buscarConta(arquivo, contaOrigem, &origem) ||
        !buscarConta(arquivo, contaDestino, &destino) ||
        origem.situacao != CONTA_ATIVA ||
        destino.situacao != CONTA_ATIVA ||
        origem.saldo < valor)
    {
        fclose(arquivo);
        return 0;
    }
    fclose(arquivo);

    sacar(contaOrigem, valor);
    depositar(contaDestino, valor);
    return 1;
}

void listarContas(void)
{
    Conta conta;
    FILE *arquivo = fopen("contas.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&conta, sizeof(Conta), 1, arquivo) == 1)
    {
        printf("%ld - %s - %s - R$ %.2f - ", conta.numero, conta.titular, conta.cpf, conta.saldo);
        if (conta.situacao == CONTA_ATIVA)
            printf("ATIVA\n");
        else
            printf("ENCERRADA\n");
    }

    fclose(arquivo);
}

int encerrarConta(long numeroConta)
{
    Conta conta;
    int ok = 0;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
        return 0;

    if (buscarConta(arquivo, numeroConta, &conta) &&
        conta.situacao == CONTA_ATIVA && conta.saldo == 0)
    {
        conta.situacao = CONTA_ENCERRADA;
        ok = atualizarConta(arquivo, &conta);
    }

    fclose(arquivo);
    return ok;
}

int main(void)
{
    int opcao;
    long numero, destino;
    double valor;
    FILE *arquivo = fopen("contas.dat", "ab");

    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }
    fclose(arquivo);

    do
    {
        printf("\n1 - Cadastrar conta\n");
        printf("2 - Consultar conta\n");
        printf("3 - Realizar deposito\n");
        printf("4 - Realizar saque\n");
        printf("5 - Realizar transferencia\n");
        printf("6 - Listar contas\n");
        printf("7 - Encerrar conta\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
            cadastrarConta();
        else if (opcao == 2)
            consultarConta();
        else if (opcao == 3)
        {
            printf("Conta: ");
            scanf("%ld", &numero);
            printf("Valor: ");
            scanf("%lf", &valor);
            if (depositar(numero, valor))
                printf("Deposito realizado.\n");
            else
                printf("Nao foi possivel depositar.\n");
        }
        else if (opcao == 4)
        {
            printf("Conta: ");
            scanf("%ld", &numero);
            printf("Valor: ");
            scanf("%lf", &valor);
            if (sacar(numero, valor))
                printf("Saque realizado.\n");
            else
                printf("Nao foi possivel sacar.\n");
        }
        else if (opcao == 5)
        {
            printf("Conta de origem: ");
            scanf("%ld", &numero);
            printf("Conta de destino: ");
            scanf("%ld", &destino);
            printf("Valor: ");
            scanf("%lf", &valor);
            if (transferir(numero, destino, valor))
                printf("Transferencia realizada.\n");
            else
                printf("Nao foi possivel transferir.\n");
        }
        else if (opcao == 6)
            listarContas();
        else if (opcao == 7)
        {
            printf("Conta: ");
            scanf("%ld", &numero);
            if (encerrarConta(numero))
                printf("Conta encerrada.\n");
            else
                printf("Nao foi possivel encerrar.\n");
        }
        else if (opcao != 0)
            printf("Opcao invalida.\n");

    } while (opcao != 0);

    return 0;
}