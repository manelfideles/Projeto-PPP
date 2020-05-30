#ifndef STRUCTS_PROJETO_H
#define STRUCTS_PROJETO_H

struct pdi {
  char nome_pdi[MAX];
  char horario_pdi[MAX];
  char descricao_pdi[MAX];
  int pdi_hot_count;
};
struct pdi_node {
  struct pdi Pdi;
  struct pdi_node *prox;
};

struct site {
  char nome_site[MAX];
  /*
  struct pdi_node *ListaDePdis;
  */
  struct pdi arrayPdi[3];
  int site_hot_count;
  int site_id;
};
struct site_node {
  struct site Site;
  struct site_node *prox;
};

struct data_de_aniversario {
  int dia, mes, ano;
};
struct user {
  char nome[MAX];
  char morada[MAX];
  int n_telemovel;
  struct data_de_aniversario aniversario;

  //preferencias
  struct site_node *Sites_favoritos;
  struct pdi *pdi_Hot;
  struct pdi_node *ListaPdisFavoritos;
};
struct user_node {
  struct user Aluno;
  struct user_node *prox;
};

#endif /*STRUCTS_PROJETO_H*/
