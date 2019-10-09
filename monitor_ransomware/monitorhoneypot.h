#ifndef MONITORHONEYPOT_H
#define MONITORHONEYPOT_H

#include <iostream>
#include <windows.h> // para utilizar LPTSTR
#include <tchar.h> // para utilizar TCHAR
#include <sstream> // para criação de stream de texto
#include "notificacao.h"
#include "controlenotificacao.h"
#include "idmonitores.h" // para código do monitor

using namespace std;

class MonitorHoneypot
{
private:
    static void atualiza_diretorio(LPTSTR); // atualização e criação de notificação para alterações no diretório
    static void atualiza_caminho(LPTSTR); // atualização e criação de notificação para alterações na árvore do diretório
    static void observar_diretorio(LPTSTR); // incicialização da observação do diretório
    static string converter_lptstr(LPTSTR);
public:
    static void iniciar_monitor(LPTSTR, ControleNotificacao*); // inicialização do monitor recebe o diretório que será observado
};

#endif // MONITORHONEYPOT_H
