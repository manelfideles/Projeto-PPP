struct user* criaAluno() {
  struct user* novoAluno = malloc(sizeof(struct user));
  return novoAluno;
}

FILE* create_file(char *file_name) {
  //filename tem que ser do tipo "filename.txt"
  FILE* f = fopen(file_name, "a+");
  if (f == NULL) {
    printf("Ficheiro inexistente.\n");
  }
  return f;
}

void append_user_to_database(char *file_name, struct user *Aluno) {
  //Adiciona os dados de registo de um user
  //À base de dados de users
  //formato -> Nome,morada,n_telemovel,DoB
  FILE *f = create_file(file_name);
  fprintf(f,"%s,%s,%d,%d.%d.%d\n",
  Aluno->nome,Aluno->morada,Aluno->n_telemovel,
  Aluno->aniversario.dia, Aluno->aniversario.mes,Aluno->aniversario.ano
  );
  fclose(f);
}
void create_user_file(struct user *Aluno) {
  //Cria nome_do_user.txt
  //Ficheiro que guarda as preferencias do user
  char user_file_name[strlen(Aluno->nome) + 4];
  sprintf(user_file_name, "%s.txt", Aluno->nome); //cria a string "nome_do_aluno.txt"
  FILE *f = create_file(user_file_name);

  fclose(f);
}

void getNome(struct user* Aluno) {
  printf("Insira o seu nome primeiro e ultimo nome: ");
  char name[MAX];
  fgets(name, MAX, stdin);
  int len1 = strlen(name); //retira \n
  if (len1 > 0 && name[len1-1] == '\n') {
    name[--len1] = '\0';
  }
  strcpy(Aluno->nome, name); //Nota *
}
void getMorada(struct user* Aluno) {
  printf("Insira a sua morada: ");
  char adress[MAX];
  fgets(adress, MAX, stdin);
  int len2 = strlen(adress);
  if (len2 > 0 && adress[len2-1] == '\n') {
    adress[--len2] = '\0';
  }
  strcpy(Aluno->morada, adress);
}
void getNumero(struct user* Aluno) {
  printf("Insira o seu numero de telemovel: ");
  int numero;
  scanf("%d", &numero);
  Aluno->n_telemovel = numero;
  fflush(stdin); //havia um \n preso no buffer, fflush limpa-o
}
void getData(struct user* Aluno) {
  printf("Insira a sua data de nascimento (dd.mm.aaaa): ");
  char aniversario[MAX];
  fgets(aniversario, MAX, stdin);
  sscanf(aniversario, "%d.%d.%d",
    &(Aluno->aniversario.dia),
    &(Aluno->aniversario.mes),
    &(Aluno->aniversario.ano)
  );
}

void getAluno(struct user *Aluno) {
  //lê os dados do aluno
  getNome(Aluno);
  getMorada(Aluno);
  getNumero(Aluno);
  getData(Aluno);
}
void alteraDados(struct user *Aluno) {
  printf("Pressione:\n> 1 para alterar o nome\n> 2 para alterar a morada\n> 3 para alterar o n. de telemovel\n> 4 para alterar a data de nascimento\n> 0 para voltar\n");
  char opt;
  do {
    printf("A sua opcao: ");
    scanf("%c", &opt); fflush(stdin);
    switch(opt) {
      case '1': getNome(Aluno); break;
      case '2': getMorada(Aluno); break;
      case '3': getNumero(Aluno); break;
      case '4': getData(Aluno);
      case '0': append_user_to_database("User_DataBase.txt", Aluno); create_user_file(Aluno); break;
    }
    if (isdigit(opt) == 0) {
      printf("Opcao invalida! Insira um dos numeros acima.\n");
    }
  }
  while (isdigit(opt) == 0);
}
