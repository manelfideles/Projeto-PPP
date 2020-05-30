void printPDIsFavoritos(struct user *Aluno) {
  struct pdi_node* c;
  printf("\n");
  printf("Os seus PDIs favoritos:\n");
  int count = 1;
  for (c = Aluno->ListaPdisFavoritos; c != NULL; c = c->prox) {
    printf("---\n#%d\n", count);
    print_pdi(&c->Pdi);
    count++;
  }
  printf("\n");
}
void printSitesFavoritos(struct user *Aluno) {
  printf("Os seus sitios preferidos: \n");
  struct site_node* i;
  for(i=Aluno->Sites_favoritos; i != NULL; i=i->prox) {
    printf("---\n");
    printf("#%d  %s, %d\n", i->Site.site_id, i->Site.nome_site, i->Site.site_hot_count);
  }
  printf("\n");
}

int SiteInFavorites(struct site *Site, struct site_node* head) {
  struct site_node *i;
  for(i=head; i!=NULL; i=i->prox) {
    if(strcmp(i->Site.nome_site, Site->nome_site) == 0) {
      return 1;
    }
  }
  return 0;
}
struct site_node* addSiteToFavorites(struct user* Aluno, struct site *Site, struct site_node *head) {
  int len = len_ListaDeSites(head);
  if (len < 4 && SiteInFavorites(Site, head) == 0) {
    Site->site_hot_count++;
    printf("Adicionou '%s' aos seus locais favoritos!\n", Site->nome_site);
    head = insertEnd_site(head, Site);
    len = len_ListaDeSites(head);
    printf("Tem %d locais favoritos\n", len);
    return head;
  }
  else printf("Ja tem 3 lugares selecionados ou esse lugar ja esta nos seus favoritos.\n");
}
struct site_node* removeSiteFromFavorites(struct user* Aluno, int id2, struct site_node *headListaSites) {
  int len = len_ListaDeSites(Aluno->Sites_favoritos);
  struct site *SiteInserido = lookup_site(Aluno->Sites_favoritos, id2);
  struct site_node *j;
  for(j=headListaSites; j != NULL; j = j->prox) {
    if(j->Site.site_id == SiteInserido->site_id && len > 0) {
      j->Site.site_hot_count--;
      printf("Eliminou '%s' dos seus locais favoritos\n", j->Site.nome_site);
      Aluno->Sites_favoritos = delete_site_node(Aluno, &j->Site);
      len = len_ListaDeSites(Aluno->Sites_favoritos);
      printf("Tem %d locais favoritos\n", len);
      return Aluno->Sites_favoritos;
    }
  }
  return NULL;
}

void addPdiToHot(struct user *Aluno, struct pdi *Pdi) {
  Aluno->pdi_Hot = Pdi;
  printf("'%s' e o seu PDI HOT!\n", Aluno->pdi_Hot->nome_pdi);
  Pdi->pdi_hot_count++;
}
int PdiInFavorites(struct user *Aluno, struct pdi *Pdi) {
  struct pdi_node *i;
  for(i=Aluno->ListaPdisFavoritos; i != NULL; i=i->prox) {
    if(strcmp(i->Pdi.nome_pdi, Pdi->nome_pdi) == 0) {
      return 1;
    }
  }
  return 0;
}
struct pdi_node* addPdiToFavorites(struct user* Aluno, struct pdi *Pdi) {
  if(PdiInFavorites(Aluno, Pdi) == 0) {
    Pdi->pdi_hot_count++;
    Aluno->ListaPdisFavoritos = insertEnd_pdi(Aluno->ListaPdisFavoritos, Pdi);
    printf("Adicionou '%s' a lista de PDIs favoritos!\n");
    return Aluno->ListaPdisFavoritos;
  }
}
struct pdi_node* removePdiFromFavorites(struct user *Aluno, int i, struct site_node *headListaSites) {
  int len = len_ListaDePdis(Aluno->ListaPdisFavoritos);
  struct pdi *PdiInserido = lookup_pdi_in_fav(Aluno, i);
  struct site_node *j;
  int count;
  for(j=headListaSites; j!=NULL; j=j->prox) {
    for(count=0; count<3; count++) {
      if(strcmp(j->Site.arrayPdi[count].nome_pdi, PdiInserido->nome_pdi) == 0 && len > 0) {
        j->Site.arrayPdi[count].pdi_hot_count--;
        printf("Eliminou '%s' dos seus PDIs favoritos\n", j->Site.arrayPdi[count].nome_pdi);
        Aluno->ListaPdisFavoritos = delete_pdi_node(Aluno, &j->Site.arrayPdi[count]);
        len = len_ListaDePdis(Aluno->ListaPdisFavoritos);
        return Aluno->ListaPdisFavoritos;
      }
    }
  }
}

void writePref(struct user *Aluno) {
  char user_file_name[strlen(Aluno->nome) + 4];
  sprintf(user_file_name, "%s.txt", Aluno->nome); //cria a string "nome_do_aluno.txt"
  FILE *f = fopen(user_file_name, "w+");
  if (f == NULL) printf("Ficheiro '%s' inexistente\n", user_file_name);

  struct site_node *i;
  struct site_node *headSites = Aluno->Sites_favoritos;
  fputs("#\n", f);
  fprintf(f, "%s\n", Aluno->pdi_Hot->nome_pdi);
  fputs("#\n", f);

  fputs(">\n", f);
  for(i=headSites; i!=NULL; i=i->prox) {
    fprintf(f, "%d\n", i->Site.site_id);
  }
  fputs(">\n", f);
  struct pdi_node *headPdis = Aluno->ListaPdisFavoritos;
  struct pdi_node *j = headPdis;
  fputs("*\n", f);
  for(j = headPdis; j != NULL; j=j->prox) {
    fprintf(f, "%s\n", j->Pdi.nome_pdi);
  }
  fputs("*", f);
  fclose(f);
}
void readPref(struct user *Aluno, struct site_node *lista_Sites_sorted) {
  char user_file_name[strlen(Aluno->nome) + 4];
  sprintf(user_file_name, "%s.txt", Aluno->nome); //cria a string "nome_do_aluno.txt"
  FILE *f = fopen(user_file_name, "r");
  if(f == NULL) printf("Ficheiro '%s' inexistente\n", user_file_name);
  char line[MAX];
  int pdi_hot_preenchido = 0;
  while(!feof(f)) {
    fgets(line, MAX, f);
    int len = strlen(line);
    int id_recebido;
    if (len > 0 && line[len-1] == '\n') line[--len] = '\0';
    if(line[0] == '>' || line[0] == '*' || line[0] == '#') continue;

    //le pdi hot
    if(line[0] != '#' && isdigit(line[0]) == 0 && pdi_hot_preenchido == 0) {
      struct site_node *a;
      int c;
      for(a=lista_Sites_sorted; a!=NULL; a=a->prox) {
        for(c=0; c<10; c++) {
          if(strcmp(a->Site.arrayPdi[c].nome_pdi, line) == 0) {
             addPdiToHot(Aluno, &a->Site.arrayPdi[c]);
             pdi_hot_preenchido = 1;
             break;
          }
        }
      }
    }
    //le sitios favoritos
    if(line[0] != '>' && isdigit(line[0]) != 0) {
      sscanf(line, "%d", &id_recebido);
      struct site *SitePref = lookup_site(lista_Sites_sorted, id_recebido);
      Aluno->Sites_favoritos = addSiteToFavorites(Aluno, SitePref, Aluno->Sites_favoritos);
    }
    //le pdis favoritos
    if(line[0] != '*' && isdigit(line[0]) == 0 && pdi_hot_preenchido == 1) {
      struct site_node *j;
      int count;
      for(j=lista_Sites_sorted; j != NULL; j=j->prox) {
        for(count=0; count < 10; count++) {
          if(strcmp(j->Site.arrayPdi[count].nome_pdi, line) == 0 && strcmp(j->Site.arrayPdi[count].nome_pdi, Aluno->pdi_Hot->nome_pdi) != 0) {
             Aluno->ListaPdisFavoritos = addPdiToFavorites(Aluno, &j->Site.arrayPdi[count]);
          }
        }
      }
    }
  }
  fclose(f);
}

void readPrefUsers(struct user_node *headAlunos, struct site_node *lista_Sites_sorted) {
  struct user_node* i;
  for(i=headAlunos; i!=NULL; i=i->prox) {
    i->Aluno.Sites_favoritos = NULL;
    i->Aluno.ListaPdisFavoritos = NULL;
    readPref(&i->Aluno, lista_Sites_sorted);
  }
}

void imprime_viagem(struct user *Aluno) {
  struct site_node *i;
  struct pdi_node *j;
  int a, count = 0;
  for(i=Aluno->Sites_favoritos; i!=NULL; i=i->prox) {
    printf("#%d '%s':\n", ++count, i->Site.nome_site);
    for(a=0; a < 3; a++) {
      for (j=Aluno->ListaPdisFavoritos; j!=NULL; j=j->prox) {
        if (strcmp(j->Pdi.nome_pdi, i->Site.arrayPdi[a].nome_pdi) == 0)
          printf("> (!) %s\n", i->Site.arrayPdi[a].nome_pdi);
        else {
          printf("> %s\n", i->Site.arrayPdi[a].nome_pdi);
        }
        break;
      }
    }
    printf("-------\n");
  }
}
