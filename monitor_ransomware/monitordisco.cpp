#include "monitordisco.h"

static ControleNotificacao * controleNotificacao;
static PDH_HQUERY query;
static PDH_HCOUNTER counter;

void MonitorDisco::iniciar_monitor(ControleNotificacao * controle) {

    controleNotificacao = controle;

    PdhOpenQuery(NULL, 0, &query);
    PdhAddCounterA(query, "\\PhysicalDisk(*)\\% Disk Time", 0, &counter);
    PdhCollectQueryData(query);
    double diskUsage;

    while (true) {
        diskUsage = getDiskTime();
        controleNotificacao->notificar(long(diskUsage), long(diskUsage));

        cout << "Valor na consulta: " << diskUsage << endl;
        Sleep(1000);
    }
}

double MonitorDisco::getDiskTime() {
    PDH_FMT_COUNTERVALUE fmtCounter;
    PdhCollectQueryData(query);
    PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, 0, &fmtCounter);

    return fmtCounter.doubleValue;
};
