#ifndef CONTROLENOTIFICACAO_H
#define CONTROLENOTIFICACAO_H

#include <iostream>
#include <sstream>
#include "notificacao.h"
#include "idmonitores.h"
#include "ui_monitor.h"
#include "qcustomplot.h"

using namespace std;

class ControleNotificacao
{
private:
    int contador_honeypot; // contador para monitor honeypot
    int contador_disco; // contador para monitor disk
    int contador_entropia; // contador para monitor entropy
    QListWidget * listHoney;
    QListWidget * listEntropia;
    QCustomPlot * graficoDisco;

    bool exibir_notificacao; // controle de definição de impressão de notificações
public:
    ControleNotificacao(QListWidget*, QListWidget*, QCustomPlot*);
    ~ControleNotificacao();
    void notificar(Notificacao); // método chamado pelos monitores para gerar a notificação
    void notificar(long, long); // método chamado pelos monitores para gerar a notificação
    void set_contador_honeypot(Notificacao); // incremento do contador de honeypot
    void atualiza_grafico(long, long); // incremento do contator de disco
    void set_contador_entropia(Notificacao); // incremento do contator de entropia
    void set_exibir_notificacao(bool); // alteração do parâmetro de impressão
};

#endif // CONTROLENOTIFICACAO_H
