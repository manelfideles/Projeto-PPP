#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 500
#include "getAluno.h"
#include "structs_projeto.h"
#include "operacoes_listas_ligadas.h"
#include "getPreferencias.h"
#include "user_inputs.h"

//ESTE É O PROGRAMA DE MENU INICIAL

void menu() {
  //carregar dados
  struct site_node *lista_Sites = load_sites("locais2.txt");
  printf("'locais2.txt' ok\n");
  int check = write_site_file_sorted("locais_sorted.txt", lista_Sites);
  printf("'lista_Sites' ok\n");
  struct site_node *lista_Sites_sorted = load_sites_sorted("locais_sorted.txt");
  printf("'lista_Sites_sorted' ok\n");
  struct user_node *lista_Alunos = load_users("User_DataBase.txt");
  printf("'lista_Alunos ok'\n");
  readPrefUsers(lista_Alunos, lista_Sites_sorted);
  printf("'locais_sorted.txt' atualizado\n");
  //sleep(1);
  system("cls");
  struct user *novoAluno;
  //
  printf("------------------Projeto PPP------------------\n");
  printf("AUTORES: Alexandre Tapadinhas & Manuel Fideles\n");
  printf("-----------------------------------------------\n\n");
  printf("Bem vindo ao seu planeador de viagens!\n\n");
  printf("Este e o seu primeiro login? [1-sim/0-nao]\n");
  int a = opcao_s_n();
  if (a == 1) { //SIM
    //primeiro login -> registo -> escolha de preferencias
    printf("REGISTO\n");
    novoAluno = criaAluno();
    getAluno(novoAluno);
    novoAluno->ListaPdisFavoritos = NULL;
    novoAluno->Sites_favoritos = NULL;
    printf("\nREGISTO CONCLUIDO!\n");
    print_aluno(novoAluno);
    printf("\nPressione:\n");
    printf("> 1 para editar os seus dados\n> 0 para continuar\n");
    int opcao;
    printf("A sua opcao: ");
    opcao = opcao_s_n();
    if (opcao == 1) {
      alteraDados(novoAluno);
      int op_altera_dados;
      printf("Deseja alterar mais algum dado? [1-sim/0-nao]\n");
      printf("A sua opcao: ");
      op_altera_dados = opcao_s_n();
      if (op_altera_dados == 1) {
        alteraDados(novoAluno);
      }
      else if (op_altera_dados == 0) {
        cria_ficheiros(novoAluno);
      }
    }
    else if (opcao == 0) {
      cria_ficheiros(novoAluno);
      print_aluno(novoAluno);
    }
  }
  else { //NÃO
    printf("Insira o numero de telemovel associado a sua conta: \n");
    int num;
    scanf("%d", &num); fflush(stdin);
    novoAluno = lookup(lista_Alunos, num);
    novoAluno->ListaPdisFavoritos = NULL;
    novoAluno->Sites_favoritos = NULL;
    if (novoAluno == NULL) {
      printf("User inexistente\n");
      exit(0);
    }
    readPref(novoAluno, lista_Sites_sorted);
    system("cls");
    printf("Bem-vindo %s!\n", novoAluno->nome);
    printf("-------------\n");
    printSitesFavoritos(novoAluno);
    printPDIsFavoritos(novoAluno);
    printf("PDI HOT: \n");
    print_pdi(novoAluno->pdi_Hot);
    if(len_ListaDeSites(novoAluno->Sites_favoritos) == 3) goto label2;
  }
  printf("\n\n");
  printf("Planeie a sua viagem - Escolha um local a visitar\n");
  int sair = 0;
  do {
    label:
    printf("\n");
    print_site_list(lista_Sites_sorted);
    printf("Insira o numero de um local para ver os seus pontos de interesse: ");
    int id; scanf("%d", &id); fflush(stdin);
    struct site *Site_inserido = lookup_site(lista_Sites_sorted, id);

    if(len_ListaDeSites(novoAluno->Sites_favoritos) <= 3) {
    printf("Pretende adicionar '%s' a sua lista de sites favoritos? [1/0]\n", Site_inserido->nome_site);
    int opt; scanf("%d", &opt); fflush(stdin);

    if (opt==1 && len_ListaDeSites(novoAluno->Sites_favoritos) < 4) novoAluno->Sites_favoritos = addSiteToFavorites(novoAluno, Site_inserido, novoAluno->Sites_favoritos);
    }
    //Adicionar preferências
    printf("\n");
    print_site(Site_inserido);
    printf("Insira:\n> 1 para adicionar um PDI aos favoritos\n> 2 para definir o seu PDI HOT\n");
    printf("A sua opcao: ");
    int opt2; scanf("%d", &opt2); fflush(stdin);
    switch(opt2) {
      case 1: {
        int opt3;
        do {
          printf("Insira o numero do PDI que quer adicionar aos favoritos: \n");
          scanf("%d", &opt3); fflush(stdin);
          if(PdiInFavorites(novoAluno, &Site_inserido->arrayPdi[opt3]) != 0) printf("'%s' ja esta na lista de PDIs favoritos\n", &Site_inserido->arrayPdi[opt3].nome_pdi);
        }
        while(PdiInFavorites(novoAluno, &Site_inserido->arrayPdi[opt3]) != 0);
        novoAluno->ListaPdisFavoritos = addPdiToFavorites(novoAluno, &Site_inserido->arrayPdi[opt3]);
      } break;
      case 2: {
        printf("Insira o numero do PDI que quer definir como PDI HOT: \n");
        int opt4; scanf("%d", &opt4); fflush(stdin);
        addPdiToHot(novoAluno, &Site_inserido->arrayPdi[opt4]);
      } break;
    }
    int opt6;
    do {
      label2:
      printf("\n\n");
      printf("Insira:\n> 1 para remover um local da sua lista de favoritos\n> 2 para remover um PDI da sua lista de PDIs favoritos\n> 3 para criar automaticamente a sua viagem\n> 4 para continuar a escolher PDIs/locais\n> 5 para sair\n");
      printf("A sua opcao: ");
      scanf("%d", &opt6); fflush(stdin);
      switch(opt6) {
        case 1: {
          printf("\n");
          printSitesFavoritos(novoAluno);
          printf("Insira o numero do local que quer remover: \n");
          int id2; scanf("%d", &id2); fflush(stdin);
          novoAluno->Sites_favoritos = removeSiteFromFavorites(novoAluno, id2, lista_Sites_sorted);
        } break;
        case 2: {
          printf("\n");
          printPDIsFavoritos(novoAluno);
          printf("Insira o numero do PDI que quer remover: \n");
          int id3; scanf("%d", &id3); fflush(stdin);
          novoAluno->ListaPdisFavoritos = removePdiFromFavorites(novoAluno, id3, lista_Sites_sorted);
        } break;
        case 3: {
          if(len_ListaDeSites(novoAluno->Sites_favoritos) == 3) {
            sair = 1;
          }
          else printf("Escolha 3 locais favoritos\n");
          break;
        }
        case 4: goto label; break;
        case 5: exit(0);
      }
    }
    while((len_ListaDeSites(novoAluno->Sites_favoritos) == 3) && sair != 1 && opt6 != 3);
  }
  while(sair != 1);

  system("cls");
  printf("A sua viagem esta a ser gerada");
  writePref(novoAluno);
  //sleep(1);
  int j;
  // for(j=0; j<3; j++) {
  //   printf("."); sleep(1);
  // }
  printf("\n");
  printf("Feito!\n\n");
  printf("A sua viagem: (PDIs com (!) estao na sua lista de favoritos)\n");
  imprime_viagem(novoAluno);
  printf("Insira:\n> 1 para gerar nova viagem\n> 2 para sair\n");
  int opt5; scanf("%d", &opt5);
  switch(opt5) {
    case 1: goto label;
    case 2: {
      printf("\n\n");
      printf("----------\n");
      delete_site_list(novoAluno->Sites_favoritos);
      printf("Libertou %d\n", novoAluno->Sites_favoritos);
      delete_pdi_list(novoAluno->ListaPdisFavoritos);
      printf("Libertou %d\n", novoAluno->ListaPdisFavoritos);
      delete_user_list(lista_Alunos);
      printf("Libertou %d\n", lista_Alunos);
      delete_site_list(lista_Sites);
      printf("Libertou %d\n", lista_Sites);
      delete_site_list(lista_Sites_sorted);
      printf("Libertou %d\n", lista_Sites_sorted);
      free(novoAluno);
      printf("Libertou %d\n", novoAluno);
      printf("\n");
      exit(0);
    } //liberta todas as listas e sai do programa
  }
}

int main() {
  menu();
  return 0;
}
