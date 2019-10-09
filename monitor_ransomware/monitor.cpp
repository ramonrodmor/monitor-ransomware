#include "monitor.h"
#include "ui_monitor.h"

Monitor::Monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);
    threads_off = true;
    controleNotif = new ControleNotificacao(ui->listHoney, ui->listEntropia, ui->customPlot);
    desenha_grafico();
}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::iniciar_threads() {

    // Diretório honeypot
    string diretorio_honeypot("C:\\teste");
    int size_diretorio_honeypot = int(diretorio_honeypot.size()+1);
    LPTSTR diretorioL = new TCHAR[size_diretorio_honeypot];
    for (int i=0; i < size_diretorio_honeypot; i++) {
        diretorioL[i] = diretorio_honeypot[i];
    }
    thread_honeypot = new class thread (MonitorHoneypot::iniciar_monitor, diretorioL, controleNotif);

    // Diretório entropia
    string diretorio_entropia = "C:\\teste\\#######armadilha.txt";
    thread_entropia = new class thread (MonitorEntropia::iniciar_monitor, diretorio_entropia, controleNotif);

    // Disco
    thread_disco = new class thread (MonitorDisco::iniciar_monitor, controleNotif);
}

void Monitor::encerrar_threads() {

    thread_disco->~thread();
    thread_entropia->~thread();
    thread_honeypot->~thread();

    threads_off = true;
}

void Monitor::on_actionIniciar_Monitores_triggered()
{
    if (threads_off) {
        iniciar_threads();
        threads_off = false;
        QMessageBox::about(this, "Sucesso", "Os monitores foram iniciados e já estão observando.");
    } else {
        QMessageBox::about(this, "Falha", "Os monitores já estão em funcionamento.");
    }
}

void Monitor::desenha_grafico()
{
    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(2.5);

    // Gráfico de escrita
    pen.setColor(QColor(255, 0, 0, 200));
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(0)->setPen(pen);
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(255, 0, 0,70)));
    ui->customPlot->graph(0)->setName("Número de operações de escrita");

    // Gráfico de leitura
    pen.setColor(QColor(0, 0, 255, 200));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setPen(pen);
    ui->customPlot->graph(1)->setBrush(QBrush(QColor(0, 0, 255,70)));
    ui->customPlot->graph(1)->setName("Número de operações de leitura");

    // axis configurations:
    ui->customPlot->xAxis->setLabel("Tempo de monitoramento (s)");
    ui->customPlot->yAxis->setLabel("Número de operações de leitura/escrita");
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setSubTicks(false);
    ui->customPlot->yAxis2->setSubTicks(false);
    // setup legend:
    ui->customPlot->legend->setFont(QFont(font().family(), 7));
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}
