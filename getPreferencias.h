#ifndef FUNCAO_PREFERENCIAS_H
#define FUNCAO_PREFERENCIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs_projeto.h"

void printPDIsFavoritos(struct user *Aluno);
void printSitesFavoritos(struct user *Aluno);

int SiteInFavorites(struct site *Site, struct site_node* head);
struct site_node* addSiteToFavorites(struct user* Aluno, struct site *Site, struct site_node *head);
struct site_node* removeSiteFromFavorites(struct user* Aluno, int id2, struct site_node *headListaSites);

void addPdiToHot(struct user *Aluno, struct pdi *Pdi);
int PdiInFavorites(struct user *Aluno, struct pdi *Pdi);
struct pdi_node* addPdiToFavorites(struct user* Aluno, struct pdi *Pdi);
struct pdi_node* removePdiFromFavorites(struct user *Aluno, int i, struct site_node *headListaSites);

void writePref(struct user *Aluno);
void readPref(struct user *Aluno, struct site_node *lista_Sites_sorted);

void readPrefUsers(struct user_node *headAlunos, struct site_node *lista_Sites_sorted);

void imprime_viagem(struct user *Aluno);

#endif /*FUNCAO_PREFERENCIAS_H*/
