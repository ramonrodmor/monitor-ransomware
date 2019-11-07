#include "controlenotificacao.h"

static QVector<double> tempo, valor1, valor2;

ControleNotificacao::ControleNotificacao(QListWidget * listH, QListWidget * listE, QCustomPlot * grafico) {
    contador_disco = 0;
    contador_entropia = 0;
    contador_honeypot = 0;
    exibir_notificacao = true;
    listHoney = listH;
    listEntropia = listE;
    graficoDisco = grafico;
}

// função que gera impressão em tela e incrementa contador - recebe uma Notificacao
void ControleNotificacao::notificar(Notificacao obj) {
    // escolha com base no tipo monitor que gerou a notificação
    switch (obj.get_monitor()) {
    case HONEYPOT:
        set_contador_honeypot(obj); // incrementa contador honeypot
        break;
    case ENTROPIA:
        set_contador_entropia(obj); // incrementa contator da entropia
        break;
    default:
        break;
    }
}

void ControleNotificacao::notificar(double tempoDisco) {
    atualiza_grafico(tempoDisco);
}

// função que implementa contador e imprime a notificação do monitor honeypot
void ControleNotificacao::set_contador_honeypot(Notificacao obj) {
    contador_honeypot++; // contabilização da notificação

    stringstream ss;
    ss << "----- Notificacao recebida - nr " << contador_honeypot << "-----" << endl << obj.get_noti();
    QString qstr = QString::fromStdString(ss.str());
    listHoney->insertItem(0, qstr);
}

// função que atualiza o gráfico do monitor de disco
void ControleNotificacao::atualiza_grafico(double tempoDisco) {

    contador_disco++;

    // set data:
    tempo  << contador_disco;
    valor1 << int(tempoDisco);
    graficoDisco->graph(0)->setData(tempo, valor1);
    stringstream ss;
    ss << "Tempo de atividade (%): " << int(tempoDisco);
    string texto = ss.str();
    graficoDisco->graph(0)->setName(texto.c_str());

    graficoDisco->xAxis->setRange(contador_disco-60, contador_disco);
    graficoDisco->yAxis->setRange(0, 100);
    graficoDisco->replot(QCustomPlot::rpQueuedReplot);
}

// função que implementa contador e imprime a notificação do monitor de entropia
void ControleNotificacao::set_contador_entropia(Notificacao obj) {
    contador_entropia++; // contabilização da notificação

    stringstream ss;
    ss << "----- Notificacao recebida - nr " << contador_entropia << "-----" << endl << obj.get_noti();
    QString qstr = QString::fromStdString(ss.str());
    listEntropia->insertItem(0, qstr);
}

// define se as notificações recebidas serão impressas em tela ou não
void ControleNotificacao::set_exibir_notificacao(bool print) {
    exibir_notificacao = print;
}
