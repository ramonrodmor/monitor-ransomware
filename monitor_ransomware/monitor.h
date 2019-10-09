#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <thread>
#include "idmonitores.h"
#include "controlenotificacao.h"
#include "monitordisco.h"
#include "monitorentropia.h"
#include "monitorhoneypot.h"
#include "QMessageBox"

namespace Ui {
class Monitor;
}

class Monitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = nullptr);
    ~Monitor();
    void atualiza_honeypot(string);
    void atualiza_entropia(string);
    class ControleNotificacao * controleNotif;

private slots:
    void on_actionIniciar_Monitores_triggered();

private:
    Ui::Monitor *ui;
    void iniciar_threads();
    void encerrar_threads();
    void desenha_grafico();
    class thread * thread_disco;
    class thread * thread_honeypot;
    class thread * thread_entropia;
    bool threads_off;
};

#endif // MONITOR_H
