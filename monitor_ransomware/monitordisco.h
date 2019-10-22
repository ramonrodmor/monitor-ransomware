#ifndef MONITORDISCO_H
#define MONITORDISCO_H

#include <windows.h>
#include <iostream>
#include <sstream> // para criação de stream de texto
#include "notificacao.h"
#include "idmonitores.h"
#include "controlenotificacao.h"
#include <pdh.h>
#include <pdhmsg.h>

using namespace std;

class MonitorDisco
{
private:
    static double getDiskTime();
public:
    static void iniciar_monitor(ControleNotificacao*);
};


#endif // MONITORDISCO_H
