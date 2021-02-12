#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Struct dos dependentes
struct Dependente{
    char nome[20];
    int idade;
};

//Struct dos associados
struct Associado{
    int id;
    char nome[20];
    int idade;
    int qtdDep;
    struct Dependente dep[3];
    bool natacao;
    bool futsal;
    bool tenis;
};


//Funcoes utilizadas, em ordem de criacao
void menu();
void menu_modalidade();
void cadastro_assoc(int *cont, struct Associado assoc[]);
void cadastro_dep(int cont, struct Associado assoc[]);
void list_assoc(int cont, struct Associado assoc[]);
void list_modal(struct Associado assoc[], int cont);
void pesqui_assoc(struct Associado assoc[], int cont);
void relatorio_geral(struct Associado assoc[], int cont);
int qtdmodal(struct Associado assoc[], int cont);
float valor_mensalidade(struct Associado assoc[], int i);
void total_mensalidade(struct Associado assoc[], int cont);
float max_mensalidade(struct Associado assoc[], int cont);
void faz_mais_aulas(struct Associado assoc[], int cont);
int verif_idade(int age);
bool faz_modalidade(char sim_nao);


//Variaveis Globais
int totalDep=0, totalNatacao=0, totalFutsal=0, totalTenis=0;
float totalMensal=0;



int main()
{

    int opc, cont=0;
    struct Associado assoc[9999];

    printf("----- Projeto -----");
    printf("\n\n\n");
    printf("<Gerenciador de Associados>");
    printf("\n\n\n");

    do{
        menu();
        scanf("%d", &opc);
        printf("\n\n");

        switch(opc){//switch para escolha do menu principal
            case 1:
                system("cls || clear");
                cadastro_assoc(&cont, assoc);
                system("cls || clear");
                break;

            case 2:
                system("cls || clear");
                cadastro_dep(cont, assoc);
                break;

            case 3:
                system("cls || clear");
                list_assoc(cont, assoc);
                break;

            case 4:
                system("clear || cls");
                list_modal(assoc, cont);
                break;

            case 5:
                system("cls || clear");
                pesqui_assoc(assoc, cont);
                break;

            case 6:
                system("cls || clear");
                relatorio_geral(assoc, cont);
                break;

            case 7:
                break;

            default:
                system("cls || clear");
                printf("Opcao Invalida! ");
                printf("\n\n");
                break;
        }
    }while(opc != 7);

    system("cls || clear");
    printf("Ate a proxima!");
    printf("\n");

    return 0;
}


//FUNCOES




//Funcao para imprimir o menu
void menu()
{
    printf("Escolha uma das opcoes: \n\n");

    printf("1. Cadastrar associado\n");
    printf("2. Cadastrar dependente\n");
    printf("3. Listar associados\n");
    printf("4. Listar associados por modalidade\n");
    printf("5. Pesquisar associados\n");
    printf("6. Gerar relatorio de associados\n");
    printf("7. Finalizar Programa\n");
}




//Funcao para imprimir o menu apos escolher a opcao 4 no menu principal
void menu_modalidade()
{
    printf("Selecione uma das modalidades abaixo: \n\n");

    printf("1- Natacao\n");
    printf("2- Futsal\n");
    printf("3- Tenis\n");
}




//Funcao para cadastrar os associados
void cadastro_assoc(int *cont, struct Associado assoc[])
{
    char sim_nao;

    printf("Insira abaixo: \n\n");

    printf("Id: ");
    scanf("%d", &assoc[*cont].id);

    printf("Nome: ");
    scanf("  %[^\n]s", assoc[*cont].nome);

    printf("Idade: ");
    scanf("%d", &assoc[*cont].idade);
    assoc[*cont].idade = verif_idade(assoc[*cont].idade);//Verificando se a idade inserida e positiva

    printf("Faz natacao(s/n)?: ");
    scanf(" %c", &sim_nao);
    assoc[*cont].natacao = faz_modalidade(sim_nao);//Verificando se o associado faz ou nao o esporte baseado na resposta dada

        if(assoc[*cont].natacao == true){
            totalNatacao++;
        }

    printf("Faz futsal(s/n)?: ");
    scanf(" %c", &sim_nao);
    assoc[*cont].futsal = faz_modalidade(sim_nao);//Verificando se o associado faz ou nao o esporte baseado na resposta dada

        if(assoc[*cont].futsal == true){
            totalFutsal++;
        }

    printf("Faz tenis(s/n)?: ");
    scanf(" %c", &sim_nao);
    assoc[*cont].tenis = faz_modalidade(sim_nao);//Verificando se o associado faz ou nao o esporte baseado na resposta dada

        if(assoc[*cont].tenis == true){
            totalTenis++;
        }

    (*cont)++;
}




//Funcao para cadastrar os dependentes
void cadastro_dep(int cont, struct Associado assoc[])
{
    int busca, cadast, ident, ndep, ver=0;

    printf("Insira o numero de identificacao do associado ao qual deseja cadastrar o/os dependentes: ");
    scanf("%d", &ident);

    for(busca=0; busca<cont; busca++){
        if(ident == assoc[busca].id){
            printf("Quantos dependentes deseja registrar(max de 3 por associado)?: ");
            scanf("%d", &ndep);

            do{
                if(ndep < 0 ||  ndep > 3){
                    printf("Quantidade invalida! Insira novamente: ");
                    scanf("%d", &ndep);
                }
            }while(ndep < 0 || ndep > 3);

            printf("\n\n");
            ver = 1;

            if(ndep + assoc[busca].qtdDep  <= 3 && ndep + assoc[busca].qtdDep >= 0){
                for(cadast=assoc[busca].qtdDep; cadast < assoc[busca].qtdDep + ndep; cadast++ ){
                    printf("Insira o %d dependente:\n", (cadast+1));

                    printf("Nome: ");
                    scanf(" %[^\n]s", assoc[busca].dep[cadast].nome);

                    printf("Idade: ");
                    scanf("%d", &assoc[busca].dep[cadast].idade);
                    assoc[busca].dep[cadast].idade = verif_idade(assoc[busca].dep[cadast].idade);
                    printf("\n");

                    totalDep++;
                }

                assoc[busca].qtdDep += ndep;

            }else if(ndep + assoc[busca].qtdDep > 3 && assoc[busca].qtdDep != 3){
                    printf("A quantidade inserida extrapola o maximo permitido!\n\n\n");//Error quando ainda ha espaco para mais dependentes, porem a quantidade inserida extrapola
                }else{
                    printf("O numero maximo de associados foi alcancado!\n\n\n");//Error para quando os 3 dependentes ja foram preenchidos
                }

            printf("\n");
            printf("Dependentes do Associado %s: \n\n", assoc[busca].nome);

            for(cadast=0; cadast<= (assoc[busca].qtdDep - 1); cadast++){
                printf("%s - %d\n", assoc[busca].dep[cadast].nome, assoc[busca].dep[cadast].idade);
                printf("\n");
            }
        }
    }

    if(ver == 0){
        printf("\n\nIdentificador nao encontrado!\n\n\n");//Error caso o identificador nao seja encontrado
    }
}




//Funcao para listar os associados e suas respectivas informacoes
void list_assoc(int cont, struct Associado assoc[])
{
    int lista;

    for(lista=0; lista<cont; lista++){
        printf("%d - %s - %d anos - %d dependentes - ", assoc[lista].id, assoc[lista].nome, assoc[lista].idade, assoc[lista].qtdDep);

        if(assoc[lista].natacao == true){
            printf("Faz Natacao - ");
        }else{
            printf("Nao faz Natacao - ");
        }


        if(assoc[lista].futsal == true){
            printf("Faz Futsal - ");
        }else{
            printf("Nao faz Futsal - ");
        }


        if(assoc[lista].tenis == true){
            printf("Faz Tenis\n\n");
        }else{
            printf("Nao faz Tenis\n\n");
        }
    }
}




//Funcao para listar os associados por modalidade
void list_modal(struct Associado assoc[], int cont)
{
    int opc, i, ver;

    menu_modalidade();//Utilizacao do menu das modalidades
    scanf("%d", &opc);
    printf("\n");

    switch (opc){
        case 1:
            system("clear || cls");
            ver = 0;

            for(i=0; i<cont; i++){
                if(assoc[i].natacao == true){
                    printf("%d - %s\n", assoc[i].id, assoc[i].nome);
                    ver = 1;
                }
            }

            if(ver == 0){
                printf("Nenhum associado encontrado!");
            }

            printf("\n");
            break;

        case 2:
            system("clear || cls");
            ver=0;

            for(i=0; i<cont; i++){
                if(assoc[i].futsal == true){
                    printf("%d - %s\n", assoc[i].id, assoc[i].nome);
                    ver = 1;
                }
            }

            if(ver == 0){
                printf("Nenhum associado encontrado!\n");
            }

            printf("\n");
            break;

        case 3:
            system("clear || cls");
            ver=0;

            for(i=0; i<cont; i++){
                if(assoc[i].tenis == true){
                    printf("%d - %s\n", assoc[i].id, assoc[i].nome);
                    ver=1;
                }
            }

            if(ver == 0){
                printf("Nenhum associado encontrado!");
            }

            printf("\n");
            break;

        default:
            system("clear || cls");
            printf("Opcao Invalida!");
            printf("\n\n");
            break;
    }
}




//Funcao para pesquisar os associados pelo nome
void pesqui_assoc(struct Associado assoc[], int cont)
{
    int i, ver=0;
    char pesquisa[20];

    printf("Qual o nome deseja pesquisar?: ");
    scanf(" %[^\n]s", pesquisa);
    printf("\n");

    for(i=0; i<cont; i++){
        if(strcmp(assoc[i].nome, pesquisa) == 0){
            printf("%d - %s - %d idade - %d dependentes - %d aulas - R$%.2f", assoc[i].id, assoc[i].nome, assoc[i].idade, assoc[i].qtdDep, qtdmodal(assoc, i), valor_mensalidade(assoc, i));

            ver = 1;
        }
    }

    if(ver == 0){
        printf("Associado nao encontrado!");
    }

    printf("\n\n\n");
}




//Funcao para gerar o relatorio geral dos cadastros
void relatorio_geral(struct Associado assoc[], int cont)
{

    total_mensalidade(assoc, cont);

    printf("->Numero total de associados cadastrados: %d\n\n", cont);
    printf("->Numero total de dependentes cadastrados: %d\n\n", totalDep);
    printf("->Numero de associados que fazem aula de Natacao: %d\n\n", totalNatacao);
    printf("->Numero de associados que fazem aula de Futsal: %d\n\n", totalFutsal);
    printf("->Numero de associados que fazem aula de Tenis: %d\n\n", totalTenis);
    printf("->Valor total de todas as mensalidades dos associados: %.2f\n\n", totalMensal);
    printf("->Valor medio das mensalidades dos associados: %.2f\n\n", totalMensal/cont);
    printf("->Valor de mensalidade mais alto pago por um associado: %.2f\n\n", max_mensalidade(assoc, cont));
    printf("->Nome do(s) associado(s) que fazem mais aulas:\n");
        faz_mais_aulas(assoc, cont);
    printf("\n");
}




//Funcao para calcular a quantidade de modalidades realizadas por um associado
int qtdmodal(struct Associado assoc[], int cont)
{
    int qtd=0;

    if(assoc[cont].natacao == true){
        qtd++;
    }

    if(assoc[cont].futsal == true){
        qtd++;
    }

    if(assoc[cont].tenis == true){
        qtd++;
    }

    return qtd;
}




//Funcao para calcular o valor da mensalidade para um associado em especifico
float valor_mensalidade(struct Associado assoc[], int i)
{
    float valor=0;

    valor = 100 + (50 * assoc[i].qtdDep) + (30 * qtdmodal(assoc, i));

    return valor;
}




//Funcao para calcular o total das mensalidades registradas
void total_mensalidade(struct Associado assoc[], int cont)
{
    int i;

    totalMensal = 0;
    for(i=0; i<cont; i++){
        totalMensal += 100 + (50 * assoc[i].qtdDep) + (30 * qtdmodal(assoc, i));
    }
}




//Funcao para verificar qual e a mensalidade mais cara paga por um associado
float max_mensalidade(struct Associado assoc[], int cont)
{
    int i;
    float max=0;

    for(i=0; i<cont; i++){
        if(valor_mensalidade(assoc, i) > max){
            max = valor_mensalidade(assoc, i);
        }
    }

    return max;
}




//Funcao para verificar e imprimir quais associados fazem mais aulas
void faz_mais_aulas(struct Associado assoc[], int cont)
{
    int maxaulas=0, i;

    for(i=0; i<cont; i++){
        if(qtdmodal(assoc, i) > maxaulas){
            maxaulas = qtdmodal(assoc, i);
        }
    }

    for(i=0; i<cont; i++){
        if(qtdmodal(assoc, i) == maxaulas){
            printf("%s\n", assoc[i].nome);
        }
    }
}




//Funcao para verificar se a idade inserida e positiva
int verif_idade(int age)
{
    do{
        if(age < 0){
            printf("Idade Invalida! Insira novamente: ");
            scanf("%d", &age);
        }
    }while (age < 0);

    return age;
}




//Funcao para verificar se o associado faz ou nao um determinado esporte, baseado na respostade "s/n"
bool faz_modalidade(char sim_nao)
{
    do{
        if(sim_nao == 's' || sim_nao == 'S' || sim_nao == 'n' || sim_nao == 'N'){
            if(sim_nao == 's' || sim_nao == 'S' ){
                return true;
            }else{
                return false;
            }

        }else{
            printf("Opcao invalida! Insira novamente: ");
            scanf(" %c", &sim_nao);
        }
    }while(sim_nao != 's' || sim_nao != 'S' || sim_nao != 'n' || sim_nao != 'N');

    return 0;
}
