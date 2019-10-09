#ifndef MONITORENTROPIA_H
#define MONITORENTROPIA_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> // para criação de stream de texto
#include <windows.h>
#include <math.h>
#include "controlenotificacao.h"
#include "notificacao.h"
#include "idmonitores.h"

using namespace std;

const int ASCII = 127;

struct vetor_freq {
    int total;
    int cont_simbolos[ASCII];
};

class MonitorEntropia
{
public:
    static void iniciar_monitor(string, ControleNotificacao*);
    static float calcula_entropia(vetor_freq);
    static vetor_freq abrir_arquivo(string);
};

#endif // MONITORENTROPIA_H
