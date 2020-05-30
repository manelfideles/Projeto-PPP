/*--------------------------------*/
/*Operacoes a respeito dos users*/
struct user_node* NEW(struct user *Aluno) {
  struct user_node *l = malloc(sizeof(struct user_node));
  memcpy(&(l->Aluno), Aluno, sizeof(struct user));
  l -> prox = NULL;
  return l;
}
void print_aluno(struct user *Aluno) {
  printf("%s, %s, %d, %d.%d.%d\n",
  Aluno->nome, Aluno->morada, Aluno->n_telemovel,
  Aluno->aniversario.dia, Aluno->aniversario.mes, Aluno->aniversario.ano);
}
void print_list(struct user_node *head) {
  struct user_node* c;
  for (c=head; c!=NULL; c=c->prox) {
    print_aluno(&(c->Aluno));
  }
}
struct user_node* insertEnd(struct user_node *head, struct user *Aluno) {
  struct user_node *x;
  if (head == NULL) {
    return NEW(Aluno);
  }
  for (x = head; x->prox != NULL; x = x->prox)
    ;
  x->prox = NEW(Aluno);
  return head;
}
struct user_node* insertBegin(struct user_node *head, struct user *Aluno) {
  struct user_node* x = NEW(Aluno);
  x->prox = head;
  return x;
}
int readline_from_file(FILE *f, struct user* Aluno) {
  //lê do file e escreve em Aluno
  char line[MAX], DoB[MAX];
  fgets(line, MAX, f);
  char *token;
  token = strtok(line, ",");
  int count = 1;
  while (count < 5) {
    if(!token) return 1;
    switch(count) {
      case 1: strcpy(Aluno->nome, token);break;
      case 2: strcpy(Aluno->morada, token);break;
      case 3: Aluno->n_telemovel = atoi(token);break;
      case 4: strcpy(DoB, token);
    }
    token = strtok(NULL, ",");
    count ++;
  }
  sscanf(DoB, "%d.%d.%d", &(Aluno->aniversario.dia), &(Aluno->aniversario.mes), &(Aluno->aniversario.ano));
  return 0;
}
struct user_node* load_users(char *file) {
  //carrega users para uma
  //linked list em memoria
  FILE *f = fopen(file, "r");
  if (f == NULL) {
    printf("Ficheiro '%s' inexistente.\n", file);
  }
  int i;
  struct user_node *head = NULL;
  for(i=0; feof(f) != 1; i++) {
    struct user *Aluno = criaAluno();
    if(readline_from_file(f, Aluno)) break;
    head = insertEnd(head, Aluno);
  }
  return head;
}
void cria_ficheiros(struct user* Aluno) {
  append_user_to_database("User_DataBase.txt", Aluno);
  create_user_file(Aluno);
}
struct user* lookup(struct user_node *head, int num) {
  //procura o *Aluno em *lista
  //usando como chave o n_telemovel
  struct user_node *i;
  for(i = head; i != NULL; i = i->prox) {
    if(i->Aluno.n_telemovel == num) {
      return &i->Aluno;
    }
  }
  return NULL;
}

void delete_user_list(struct user_node *headAlunos) {
  struct user_node *i;
  while(headAlunos != NULL) {
     i = headAlunos;
    headAlunos = headAlunos->prox;
    free(i);
  }
}
/*----------------------------------*/
/*Operacoes a respeito dos locais/pdis*/
struct pdi* criaPdi() {
  struct pdi *novoPdi = malloc(sizeof(struct pdi));
  return novoPdi;
}
struct site* criaSite() {
  struct site* novoSite = malloc(sizeof(struct site));
  return novoSite;
}

struct site_node* NEW_site(struct site *Site) {
  struct site_node *l = malloc(sizeof(struct site_node));
  memcpy(&(l->Site), Site, sizeof(struct site));
  l->prox = NULL;
  return l;
}
struct pdi_node* NEW_pdi(struct pdi *Pdi) {
  struct pdi_node *l = malloc(sizeof(struct pdi_node));
  memcpy(&(l->Pdi), Pdi, sizeof(struct pdi));
  l->prox = NULL;
  return l;
}

void print_pdi(struct pdi *Pdi) {
  printf("Nome: %s\nHorario: %s\nDescricao: %s\nPopularidade: %d\n",
  Pdi->nome_pdi, Pdi->horario_pdi,
  Pdi->descricao_pdi, Pdi->pdi_hot_count);
}
void print_site(struct site *Site) {
  //imprime o nome do Site e cada pdi dentro de arrayPdi
  int i;
  printf("Local: %s, Id: #%d, Indice de Popularidade: %d\n", Site->nome_site, Site->site_id, Site->site_hot_count);
  for(i=0; i<3; i++) {
    printf("%d > %s, %s, %s, %d\n",
    i,
    Site->arrayPdi[i].nome_pdi,
    Site->arrayPdi[i].horario_pdi,
    Site->arrayPdi[i].descricao_pdi,
    Site->arrayPdi[i].pdi_hot_count);
  }
  printf("\n");
}
void print_site_list(struct site_node *head) {
  //imprime os nomes dos locais
  struct site_node* c;
  printf("Nome - Popularidade\n");
  printf("-------------------\n");
  for (c=head; c!=NULL; c=c->prox) {
    printf("#%d > %s - %d\n", c->Site.site_id, c->Site.nome_site, c->Site.site_hot_count);
  }
}

struct site_node* insertBegin_site(struct site_node *head, struct site *Site) {
  struct site_node *x = NEW_site(Site);
  x->prox = head;
  return x;
}
struct site_node* insertEnd_site(struct site_node *head, struct site *Site) {
  struct site_node *x;
  if (head == NULL) {
    return NEW_site(Site);
  }
  for (x = head; x->prox != NULL; x = x->prox)
    ;
  x->prox = NEW_site(Site);
  return head;
}
struct pdi_node* insertBegin_pdi(struct pdi_node *head, struct pdi *Pdi) {
  struct pdi_node *x = NEW_pdi(Pdi);
  x->prox = head;
  return x;
}
struct pdi_node* insertEnd_pdi(struct pdi_node*head, struct pdi *Pdi) {
  struct pdi_node *x;
  if (head == NULL) {
    return NEW_pdi(Pdi);
  }
  for (x = head; x->prox != NULL; x = x->prox)
    ;
  x->prox = NEW_pdi(Pdi);
  return head;
}

int len_ListaDePdis(struct pdi_node *head) {
  struct pdi_node *i = head;
  int len = 0;
  while(i != NULL) {
    ++len;
    i=i->prox;
  }
  return len;
}
int len_ListaDeSites(struct site_node *head) {
  struct site_node *i = head;
  int len = 0;
  while(i!= NULL) {
    ++len;
    i=i->prox;
  }
  return len;
}
struct site* lookup_site(struct site_node *head, int id) {
  //Esta função procura o Site inserido
  //na lista de Sites previamente carregada
  struct site_node *i;
  for(i=head; i!=NULL; i=i->prox) {
    if(i->Site.site_id == id) {
      return &i->Site;
    }
  }
}
struct pdi* lookup_pdi_in_fav (struct user *Aluno, int c) {
  struct pdi_node *head = Aluno->ListaPdisFavoritos;
  struct pdi_node *i;
  int count = 1;
  for(i=head; i!=NULL; i=i->prox) {
    if(c == count) {
      return &i->Pdi;
    }
    count++;
  }
}
struct site_node* delete_site_node(struct user *Aluno, struct site *Site) {
  struct site_node *head = Aluno->Sites_favoritos;
  struct site_node *atual;
  struct site_node *prev;
  for(atual=head, prev=NULL; atual!=NULL; prev=atual,atual=atual->prox) {
    /*
    printf("-----\n");
    printf("t->Site.site_id = %d\n", t->Site.site_id);
    printf("Site->site_id = %d\n", Site->site_id);
*/
    if(atual->Site.site_id == Site->site_id) {
      if (atual==head) head = atual->prox;
      else prev->prox = atual->prox;
      //free(atual->Site);
      //free(atual);
    }
  }
  return head;
}
struct pdi_node* delete_pdi_node(struct user *Aluno, struct pdi *Pdi) {
  struct pdi_node *head = Aluno->ListaPdisFavoritos;
  struct pdi_node *atual;
  struct pdi_node *prev;
  for(atual=head, prev=NULL; atual!=NULL; prev=atual,atual=atual->prox) {
    /*
    printf("-----\n");
    printf("t->Site.site_id = %d\n", t->Site.site_id);
    printf("Site->site_id = %d\n", Site->site_id);
*/
    if(strcmp(atual->Pdi.nome_pdi, Pdi->nome_pdi) == 0) {
      if (atual==head) head = atual->prox;
      else {
        prev->prox = atual->prox;
      }
      // free(atual->Site);
      // free(atual);
    }
  }
  return head;
}

int read_site(FILE *f, struct site *Site) { /*le ficheiro desordenado*/
  char site[MAX];
  fgets(site, MAX, f);
  int st = strlen(site) - 1;
  if (*site && site[st] == '\n') site[st] = '\0'; //retira \n de line
  char *token = strtok(site, ",");
  int t_count = 1;
  while(token != NULL) {
    if(t_count == 1) strcpy(Site->nome_site,token);
    if(t_count == 2) Site->site_hot_count = atoi(token);
    token = strtok(NULL, ",");
    t_count++;
  }

  /*le todos os pdis de um site*/
  int i;
  for(i=0; i<3; i++) {
    char pdi[MAX];
    fgets(pdi, MAX, f);
    int p = strlen(pdi) - 1;
    if (*pdi && pdi[p] == '\n') pdi[p] = '\0'; //retira \n de pdi
    char *t = strtok(pdi, ",");
    int j = 0;
    while(t != NULL) {
      if (!t) return 1;
      switch(j) {
        case 0: strcpy(Site->arrayPdi[i].nome_pdi, t); break;
        case 1: strcpy(Site->arrayPdi[i].horario_pdi, t); break;
        case 2: strcpy(Site->arrayPdi[i].descricao_pdi, t); break;
        case 3: Site->arrayPdi[i].pdi_hot_count = atoi(t); break;
      }
      j++;
      t = strtok(NULL, ",");
    }
  }
  return 0;
}
struct site_node* load_sites(char *file_name) {
  /*ESTA FUNCAO LE E ORDENA A LISTA LIGADA*/

  //le de "f.txt" e escreve numa lista ligada
  FILE *f = fopen(file_name, "r");
  if (f==NULL) {
    printf("Ficheiro '%s' inexistente\n", file_name);
  }
  struct site_node *temp;
  struct site *Site = criaSite();
  struct site_node *new_head = NULL;

  while(!feof(f)) {
    struct site *Site = criaSite();
    struct site_node *head = new_head;
    struct site_node *ant = NULL;
    read_site(f,Site);
    while (head!= NULL && strcmp((head->Site.nome_site), (Site->nome_site))<0) {
      ant = head;
      head = head->prox;
    }
    if (ant != NULL) {
      ant->prox = NEW_site(Site);
      ant->prox->prox = head;
    }
    else {
      new_head = NEW_site(Site);
      new_head->prox = head;
    }
  }
  fclose(f);
  return new_head;
}
int write_site_file_sorted(char *file_name, struct site_node *head) {
  FILE *f = fopen(file_name, "w");
  if (f == NULL){
    return 1;
  }
  int id = 1;
  while (head != NULL) {
    fprintf(f, "%d\n", id);
    id++;
    fprintf(f, "%s,%d\n", head->Site.nome_site, head->Site.site_hot_count);
    int i;
    for (i=0; i<3; i++){
      fprintf(f, "%s,%s,%s,%d",
        head->Site.arrayPdi[i].nome_pdi,
        head->Site.arrayPdi[i].horario_pdi,
        head->Site.arrayPdi[i].descricao_pdi,
        head->Site.arrayPdi[i].pdi_hot_count);
        if (i == 0 || i == 1){
          fprintf(f, "\n");
        }
    }
    if (head->prox != NULL){
      fprintf(f, "\n");
    }
    head = head->prox;
  }
  fclose(f);
  return 0;
}
int read_site_sorted(FILE *f, struct site *Site) {
  /*le id*/
  char id[MAX];
  fgets(id, MAX, f);
  sscanf(id, "%d", &Site->site_id);
  /*le nome_site e site_hot_count*/
  char site[MAX];
  fgets(site, MAX, f);
  int st = strlen(site) - 1;
  if (*site && site[st] == '\n') site[st] = '\0'; //retira \n de line
  char *token = strtok(site, ",");
  int t_count = 1;
  while(token != NULL) {
    if(t_count == 1) strcpy(Site->nome_site,token);
    if(t_count == 2) Site->site_hot_count = atoi(token);
    token = strtok(NULL, ",");
    t_count++;
  }

  /*le todos os pdis de um site*/
  int i;
  for(i=0; i<3; i++) {
    char pdi[MAX];
    fgets(pdi, MAX, f);
    int p = strlen(pdi) - 1;
    if (*pdi && pdi[p] == '\n') pdi[p] = '\0'; //retira \n de pdi
    char *t = strtok(pdi, ",");
    int j = 0;
    while(t != NULL) {
      if (!t) return 1;
      switch(j) {
        case 0: strcpy(Site->arrayPdi[i].nome_pdi, t); break;
        case 1: strcpy(Site->arrayPdi[i].horario_pdi, t); break;
        case 2: strcpy(Site->arrayPdi[i].descricao_pdi, t); break;
        case 3: Site->arrayPdi[i].pdi_hot_count = atoi(t); break;
      }
      j++;
      t = strtok(NULL, ",");
    }
  }
  return 0;
}
struct site_node* load_sites_sorted (char *file_name) {
  FILE *f = fopen(file_name, "r");
  if (f==NULL) {
    printf("Ficheiro '%s' inexistente\n", file_name);
    return NULL;
  }
  struct site_node *head = NULL;
  while(!feof(f)) {
    struct site *Site = criaSite();
    if(read_site_sorted(f,Site)) break;
    head = insertEnd_site(head, Site);
  }
  fclose(f);
  return head;
}

void delete_site_list(struct site_node *headSites) {
  struct site_node *i;
  while(headSites != NULL) {
     i = headSites;
    headSites = headSites->prox;
    free(i);
  }
}
void delete_pdi_list(struct pdi_node *headPdis) {
  struct pdi_node *i;
  while(headPdis != NULL) {
     i = headPdis;
    headPdis = headPdis->prox;
    free(i);
  }
}
/*------------------------------------*/
