#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

void salvar_pessoa(Pessoa p) {
    FILE *f = fopen("pessoa.bin", "ab");
    if (f) {
        fwrite(&p, sizeof(Pessoa), 1, f);
        fclose(f);
    }
}

void salvar_tipo_pet(TipoPet t) {
    FILE *f = fopen("tipo_pet.bin", "ab");
    if (f) {
        fwrite(&t, sizeof(TipoPet), 1, f);
        fclose(f);
    }
}

void salvar_pet(Pet p) {
    FILE *f = fopen("pet.bin", "ab");
    if (f) {
        fwrite(&p, sizeof(Pet), 1, f);
        fclose(f);
    }
}

Pessoa* buscar_pessoa(int codigo) {
    FILE *f = fopen("pessoa.bin", "rb");
    if (!f) return NULL;
    
    Pessoa *p = malloc(sizeof(Pessoa));
    while (fread(p, sizeof(Pessoa), 1, f)) {
        if (p->codigo == codigo) {
            fclose(f);
            return p;
        }
    }
    
    fclose(f);
    free(p);
    return NULL;
}

TipoPet* buscar_tipo_pet(int codigo) {
    FILE *f = fopen("tipo_pet.bin", "rb");
    if (!f) return NULL;
    
    TipoPet *t = malloc(sizeof(TipoPet));
    while (fread(t, sizeof(TipoPet), 1, f)) {
        if (t->codigo == codigo) {
            fclose(f);
            return t;
        }
    }
    
    fclose(f);
    free(t);
    return NULL;
}

Pet* buscar_pet(int codigo) {
    FILE *f = fopen("pet.bin", "rb");
    if (!f) return NULL;
    
    Pet *p = malloc(sizeof(Pet));
    while (fread(p, sizeof(Pet), 1, f)) {
        if (p->codigo == codigo) {
            fclose(f);
            return p;
        }
    }
    
    fclose(f);
    free(p);
    return NULL;
}
