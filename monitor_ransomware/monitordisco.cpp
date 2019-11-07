#include "monitordisco.h"

static ControleNotificacao * controleNotificacao;
static HQUERY query;
static HCOUNTER counter;
static PDH_FMT_COUNTERVALUE fmtCounter;
static PDH_STATUS Status;
static DWORD CounterType;

void MonitorDisco::iniciar_monitor(ControleNotificacao * controle) {


    /*
     *
     * PdhCollectQueryData failed with status 0x800007d5.Valor na consulta: 0
     * olhar no programa que funciona no visual studio
     *
     */


    controleNotificacao = controle;
    query = NULL;
    PdhOpenQuery(NULL, 0, &query);
    Status = PdhAddCounter(query, L"\\PhysicalDisk(*)\\% tempo de disco", 0, &counter);
    //Status = PdhAddCounter(query, CounterPathBuffer, 0, &counter);
    Status = PdhCollectQueryData(query);
    if (Status != ERROR_SUCCESS)
    {
        wprintf(L"\nPdhCollectQueryData failed with status 0x%x.", Status);
        EXIT_FAILURE;
    }

    double diskUsage;

    while (true) {
        diskUsage = getDiskTime();
        controleNotificacao->notificar(diskUsage);
        Sleep(1000);
    }
}

double MonitorDisco::getDiskTime() {

    Status = PdhCollectQueryData(query);
    Status = PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, &CounterType, &fmtCounter);

    double diskUsage = fmtCounter.doubleValue;
    //cout << "Valor na consulta: " << diskUsage << endl;

    return diskUsage;
};
