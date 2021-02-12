#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Dependente{

    char nome[20];
    int idade;

};


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


void menu();
void cadastro_assoc(int *cont, struct Associado assoc[]);
void cadastro_dep(int cont, struct Associado assoc[]);
void list_assoc(int cont, struct Associado assoc[]);
void verif_idade(struct Associado age[], int cont);
bool faz_modalidade(char sim_nao);




int main(){

    int opc, cont=0;

    struct Associado assoc[9999];




    do{

        menu();
        scanf("%d", &opc);
        printf("\n\n");

        switch(opc){

            case 1:

                system("cls || clear");

                cadastro_assoc(&cont, assoc);
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
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:

                printf("Opcao Invalida! Digite novamente! ");
                printf("\n\n");



        }

    }while(opc != 7);












    return 0;
}

void menu(){

    printf("Escolha uma das opcoes: \n\n\n");

    printf("1. Cadastrar associado\n");
    printf("2. Cadastrar dependente\n");
    printf("3. Listar associados\n");
    printf("4. Listar associados por modalidade\n");
    printf("5. Pesquisar associados\n");
    printf("6. Gerar relatorio de associados\n");
    printf("7. Finalizar Programa\n");





}

void cadastro_assoc(int *cont, struct Associado assoc[]){

    int i;
    char sim_nao;

    printf("Insira abaixo: \n\n");

    printf("Id: ");
    scanf("%d", &assoc[*cont].id);

    printf("Nome: ");
    scanf("  %[^\n]s", assoc[*cont].nome);

    printf("Idade: ");
    scanf("%d", &assoc[*cont].idade);
    verif_idade(assoc, *cont);

    printf("Quantos dependentes: ");
    scanf("%d", &assoc[*cont].qtdDep);

        if(assoc[*cont].qtdDep > 0){

            for(i=0; i<assoc[*cont].qtdDep; i++){

                printf("\nInsira o %d dependente: \n", (i+1));

                printf("Nome: ");
                scanf(" %[^\n]s", assoc[*cont].dep[i].nome );

                printf("Idade: ");
                scanf("%d", &assoc[*cont].dep[i].idade );

            }

        }


    printf("Faz natacao(s/n)?: ");
    scanf(" %c", &sim_nao);

    assoc[*cont].natacao = faz_modalidade(sim_nao);

    printf("Faz futsal(s/n)?: ");
    scanf(" %c", &sim_nao);

    assoc[*cont].futsal = faz_modalidade(sim_nao);

    printf("Faz tenis(s/n)?: ");
    scanf(" %c", &sim_nao);

    assoc[*cont].tenis = faz_modalidade(sim_nao);

    (*cont)++;

}






void cadastro_dep(int cont, struct Associado assoc[]){

    int busca, cadast, ident, ndep, ver=0;

    printf("Insira o numero de identificacao do associado ao qual deseja cadastrar o/os dependentes: ");
    scanf("%d", &ident);



    printf("Quantos dependentes deseja registrar(max de 3 por associado)?: \n");
    scanf("%d", &ndep);

    do{

        if(ndep < 0 || ndep > 3){

            printf("Quantidade invalida! Insira novamente: ");
            scanf("%d", &ndep);

        }

    }while(ndep < 0 || ndep > 3);


    for(busca=0; busca<cont; busca++){

        if(ident == assoc[busca].id){

            ver = 1;

            if((ndep + assoc[busca].qtdDep) <= 3 && (ndep + assoc[busca].qtdDep) >= 0){

                for(cadast=assoc[busca].qtdDep; cadast <= 2; cadast++ ){

                    printf("Nome do %d dependente do associado %s: ",  (cadast+1), assoc[busca].nome);
                    scanf(" %[^\n]s", assoc[busca].dep[cadast].nome);
                    printf("\n");

                    printf("Idade do %d dependente do associado %s: ", (cadast+1), assoc[busca].nome);
                    scanf("%d", &assoc[busca].dep[cadast].idade);

                }

                assoc[busca].qtdDep = assoc[busca].qtdDep + ndep;

            }else{

                printf("O numero maximo de associados foi alcancado!\n\n\n");

            }



            printf("Dependentes do Associado %s: \n\n", assoc[busca].nome);

            for(cadast=0; cadast<= (assoc[busca].qtdDep - 1); cadast++){

                printf("%s - %d\n", assoc[busca].dep[cadast].nome, assoc[busca].dep[cadast].idade);

            }


        }

    }

    if(ver == 0){

        printf("Identificador nao encontrado!\n\n\n");

    }

}







void list_assoc(int cont, struct Associado assoc[]){

    int lista;

    for(lista=0; lista<cont; lista++){


        printf("%d - %s - %d - %d - ", assoc[lista].id, assoc[lista].nome, assoc[lista].idade, assoc[lista].qtdDep);


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

void verif_idade(struct Associado age[], int cont){

    do{

        if(age[cont].idade < 0){

            printf("Idade Invalida! Insira novamente: ");
            scanf("%d", &age[cont].idade);

        }

    }while (age[cont].idade < 0);

}

bool faz_modalidade(char sim_nao){


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


}


