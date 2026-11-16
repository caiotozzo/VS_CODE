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
    Conta novaConta, contaExistente;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Numero da conta: ");
    scanf("%ld", &novaConta.numero);

    if (buscarConta(arquivo, novaConta.numero, &contaExistente))
    {
        printf("Essa conta ja existe.\n");
        fclose(arquivo);
        return;
    }

    printf("Titular: ");
    scanf("%s", novaConta.titular);
    printf("CPF: ");
    scanf("%s", novaConta.cpf);
    novaConta.saldo = 0;
    novaConta.situacao = CONTA_ATIVA;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&novaConta, sizeof(Conta), 1, arquivo);
    printf("Conta cadastrada.\n");

    fclose(arquivo);
}

void consultarConta(void)
{
    Conta conta;
    long numeroConta;
    FILE *arquivo = fopen("contas.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Numero da conta: ");
    scanf("%ld", &numeroConta);

    if (buscarConta(arquivo, numeroConta, &conta))
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
    int deuCerto = 0;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
        return 0;

    if (valor > 0 && buscarConta(arquivo, numeroConta, &conta) && conta.situacao == CONTA_ATIVA)
    {
        conta.saldo = conta.saldo + valor;
        deuCerto = atualizarConta(arquivo, &conta);
    }

    fclose(arquivo);
    return deuCerto;
}

int sacar(long numeroConta, double valor)
{
    Conta conta;
    int deuCerto = 0;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
        return 0;

    if (valor > 0 && buscarConta(arquivo, numeroConta, &conta) &&
        conta.situacao == CONTA_ATIVA && conta.saldo >= valor)
    {
        conta.saldo = conta.saldo - valor;
        deuCerto = atualizarConta(arquivo, &conta);
    }

    fclose(arquivo);
    return deuCerto;
}

int transferir(long contaOrigem, long contaDestino, double valor)
{
    Conta dadosOrigem, dadosDestino;
    FILE *arquivo;

    if (contaOrigem == contaDestino || valor <= 0)
        return 0;

    arquivo = fopen("contas.dat", "rb");
    if (arquivo == NULL)
        return 0;

    /* verifica tudo antes de mexer nos saldos */
    if (!buscarConta(arquivo, contaOrigem, &dadosOrigem) ||
        !buscarConta(arquivo, contaDestino, &dadosDestino) ||
        dadosOrigem.situacao != CONTA_ATIVA ||
        dadosDestino.situacao != CONTA_ATIVA ||
        dadosOrigem.saldo < valor)
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
    int deuCerto = 0;
    FILE *arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL)
        return 0;

    if (buscarConta(arquivo, numeroConta, &conta) &&
        conta.situacao == CONTA_ATIVA && conta.saldo == 0)
    {
        conta.situacao = CONTA_ENCERRADA;
        deuCerto = atualizarConta(arquivo, &conta);
    }

    fclose(arquivo);
    return deuCerto;
}

int main(void)
{
    int opcao;
    long numeroConta, contaOrigem, contaDestino;
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
            scanf("%ld", &numeroConta);
            printf("Valor: ");
            scanf("%lf", &valor);
            if (depositar(numeroConta, valor))
                printf("Deposito realizado.\n");
            else
                printf("Nao foi possivel depositar.\n");
        }
        else if (opcao == 4)
        {
            printf("Conta: ");
            scanf("%ld", &numeroConta);
            printf("Valor: ");
            scanf("%lf", &valor);
            if (sacar(numeroConta, valor))
                printf("Saque realizado.\n");
            else
                printf("Nao foi possivel sacar.\n");
        }
        else if (opcao == 5)
        {
            printf("Conta de origem: ");
            scanf("%ld", &contaOrigem);
            printf("Conta de destino: ");
            scanf("%ld", &contaDestino);
            printf("Valor: ");
            scanf("%lf", &valor);
            if (transferir(contaOrigem, contaDestino, valor))
                printf("Transferencia realizada.\n");
            else
                printf("Nao foi possivel transferir.\n");
        }
        else if (opcao == 6)
            listarContas();
        else if (opcao == 7)
        {
            printf("Conta: ");
            scanf("%ld", &numeroConta);
            if (encerrarConta(numeroConta))
                printf("Conta encerrada.\n");
            else
                printf("Nao foi possivel encerrar.\n");
        }
        else if (opcao != 0)
            printf("Opcao invalida.\n");

    } while (opcao != 0);

    return 0;
}