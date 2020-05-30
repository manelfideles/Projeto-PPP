
#ifndef OPERACOES_LISTAS_LIGADAS_H
#define OPERACOES_LISTAS_LIGADAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "structs_projeto.h"

/*--------------------------------*/
/*Operacoes a respeito dos users*/
struct user_node* NEW(struct user *Aluno);
void print_aluno(struct user *Aluno);
void print_list(struct user_node *head);
struct user_node* insertEnd(struct user_node *head, struct user *Aluno);
struct user_node* insertBegin(struct user_node *head, struct user *Aluno);
int readline_from_file(FILE *f, struct user* Aluno);
struct user_node* load_users(char *file);
void cria_ficheiros(struct user* Aluno);
struct user* lookup(struct user_node *head, int num);
void delete_user_list(struct user_node *headAlunos);
/*----------------------------------*/
/*Operacoes a respeito dos locais/pdis*/
struct pdi* criaPdi();
struct site* criaSite();
struct site_node* NEW_site(struct site *Site);
struct pdi_node* NEW_pdi(struct pdi *Pdi);

void print_pdi(struct pdi *Pdi);
void print_site(struct site *Site);
void print_site_list(struct site_node *head);
struct site_node* insertBegin_site(struct site_node *head, struct site *Site);
struct site_node* insertEnd_site(struct site_node *head, struct site *Site);
struct pdi_node* insertBegin_pdi(struct pdi_node *head, struct pdi *Pdi);
struct pdi_node* insertEnd_pdi(struct pdi_node*head, struct pdi *Pdi);
int len_ListaDePdis(struct pdi_node *head);
int len_ListaDeSites(struct site_node *head);
struct site* lookup_site(struct site_node *head, int id);
struct pdi* lookup_pdi_in_fav (struct user *Aluno, int c);
struct site_node* delete_site_node(struct user *Aluno, struct site *Site);
struct pdi_node* delete_pdi_node(struct user *Aluno, struct pdi *Pdi);
int read_site(FILE *f, struct site *Site);
struct site_node* load_sites(char *file_name);
int write_site_file_sorted(char *file_name, struct site_node *head);
int read_site_sorted(FILE *f, struct site *Site);
struct site_node* load_sites_sorted (char *file_name);

void delete_site_list(struct site_node *headSites);
void delete_pdi_list(struct pdi_node *headPdis);
/*------------------------------------*/

#endif /*OPERACOES_LISTAS_LIGADAS_H*/
