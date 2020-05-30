int find_in_array(int n, int array[]){
  int i = 0;
  do {
    if (n == array[i++]) {
      return n;
    }
  } while (array[i] != EOF);
  return -1;
} /*funcao usada em opcao_num*/

int opcao_s_n (){
  int controlo = 1;
  char opcao[50];
  do {
    scanf("%s", &opcao); fflush(stdin);
    /*SO UMA LETRA OU NUMERO*/
    if (strlen(opcao) == 1){
      if (*opcao == 'y' || *opcao == 's' || *opcao == 'S' || *opcao == '1') return 1;

      if (*opcao == 'n' || *opcao == 'N' || *opcao == '0')  return 0;

      else{
        printf("Input invalido\n");
        controlo = 0;
        printf("Insira outra vez:\n");
      }
    }
    /*PALAVRAS*/
    if (strlen(opcao) != 1){
      if (strcmp(opcao, "sim") == 0 || strcmp(opcao, "Sim") == 0 || strcmp(opcao, "SIM") == 0 ||
      strcmp(opcao, "yes") == 0 || strcmp(opcao, "Yes") == 0 || strcmp(opcao, "YES") == 0)  return 1;

      if (strcmp(opcao, "nao") == 0 || strcmp(opcao, "Nao") == 0 || strcmp(opcao, "NAO") == 0 ||
      strcmp(opcao, "no") == 0 || strcmp(opcao, "No") == 0 || strcmp(opcao, "NO") == 0) return 0;

      else{
        printf("Input invalido\n");
        controlo = 0;
        printf("Insira outra vez:\n");
      }
    }
  } while (controlo == 0);
} /*é executada até devolver 1 se SIM ou 0 se NÃO*/

int opcao_num (int lista_opcoes[]){
  int num, res;
  do {
    scanf("%d", &num); fflush(stdin);
    res = find_in_array(num, lista_opcoes);
    if (res != -1){
      return num;
    }
    else {
      res = -1;
      printf("Input invalido\nInsira outra vez:");
    }
  } while (res == -1);
} /*é executada até devolver o número da opção se estiver no array de opções do argumento da função*/

int deteta_problema_data(int dia,int mes,int ano){
    if (ano<0)
        return 1; /*primeiro tipo de erro:ano negativo */
    if((mes<1 || mes>12))
        return 2; /*segundo tipo de erro:mes fora do limite */
    if(dia>0 && dia<32){
        if(mes==2){
            if ((dia>29 && ano%4 == 0 && ano%100!=0 && ano%400==0) || ((dia>28 && ano%4 != 0) || (dia>28 && (ano%100==0 && ano%400!=0))))
                    return 3; /*terceiro tipo de erro: dia fora do limite */
        }
        if(mes==4){
            if (dia>30)
                return 3;
        }
       if(mes==6){
            if (dia>30)
                return 3;
        }
        if(mes==9){
            if (dia>30)
                return 3;
        }
        if(mes==11){
            if (dia>30)
                return 3;
        }

    }
    if (dia<1 || dia>31)
        return 3;
    return 0; /*sem erros*/
}
/*return 0 se nao tiver erros, return 1,2 ou 3 dependendo do tipo de erro*/
