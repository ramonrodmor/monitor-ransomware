#ifndef MONITORDISCO_H
#define MONITORDISCO_H

#include <windows.h>
#include <iostream>
#include <sstream> // para criação de stream de texto
#include "notificacao.h"
#include "idmonitores.h"
#include "controlenotificacao.h"

using namespace std;

struct antigo_disco {
    long long read;
    long long write;
};

struct novo_disco {
    long long read;
    long long write;
};

struct disco {
    antigo_disco antigo;
    novo_disco novo;
};

class MonitorDisco
{
private:
    static disco consulta_disco();
    static disco atualiza_disco(disco);
public:
    static void iniciar_monitor(ControleNotificacao*);
};


#endif // MONITORDISCO_H
