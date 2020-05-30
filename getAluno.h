
    #ifndef FUNCAO_GETALUNO_H
    #define FUNCAO_GETALUNO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "structs_projeto.h"
    #include <ctype.h>

    struct user* criaAluno();
    FILE* create_file(char *file_name);

    void append_user_to_database(char *file_name, struct user *Aluno);
    void create_user_file(struct user *Aluno);

    void getNome(struct user* Aluno);
    void getMorada(struct user* Aluno);
    void getNumero(struct user* Aluno);
    void getData(struct user* Aluno);

    void getAluno(struct user *Aluno);
    void alteraDados(struct user *Aluno);

    #endif /*FUNCAO_GETALUNO_H*/
