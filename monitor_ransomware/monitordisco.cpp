#include "monitordisco.h"

// TODO: trabalhar monitor de disco
/*
https://docs.microsoft.com/en-us/previous-versions/aa394308(v%3Dvs.85)
https://docs.microsoft.com/pt-br/windows/win32/wmisdk/example--getting-wmi-data-from-the-local-computer
https://www.google.com/search?sxsrf=ACYBGNTYZ7Rvr8gEKT2NRAAMlteE2loVNA%3A1569957989007&ei=ZaiTXcQHyZvk5Q-mw564Aw&q=DiskReadsPerSec+c%2B%2B&oq=DiskReadsPerSec+c%2B%2B&gs_l=psy-ab.3...6274.7034..7281...0.0..0.197.704.0j4......0....1..gws-wiz.c-rDjmAfecw&ved=0ahUKEwiEzvyh5fvkAhXJDbkGHaahBzcQ4dUDCAs&uact=5
*/

static ControleNotificacao * controleNotificacao;

void MonitorDisco::iniciar_monitor(ControleNotificacao * controle) {
    controleNotificacao = controle;
    disco disco_monitorado = consulta_disco();
    while (true) {
        disco_monitorado = atualiza_disco(disco_monitorado);
        long long leitura = disco_monitorado.novo.read;
        long long escrita = disco_monitorado.novo.write;
        controleNotificacao->notificar(leitura, escrita);
        Sleep(1000);
    }
}

disco MonitorDisco::atualiza_disco(disco disc) {
    disco novo_disc;
    novo_disc.antigo.read = disc.novo.read;
    novo_disc.antigo.write = disc.novo.write;
    disc = consulta_disco();
    novo_disc.novo.read = disc.novo.read;
    novo_disc.novo.write = disc.novo.write;
    return novo_disc;
}

disco MonitorDisco::consulta_disco() {
    LPCWSTR path = L"\\\\.\\C:";
    HANDLE dev = CreateFile(path,
        FILE_READ_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    DISK_PERFORMANCE disk_info{ };
    DWORD bytes;

    if (dev == INVALID_HANDLE_VALUE) {
        cerr << "Error opening disk\n";
    }

    if (!DeviceIoControl(dev,
        IOCTL_DISK_PERFORMANCE,
        NULL,
        0,
        &disk_info,
        sizeof(disk_info),
        &bytes,
        NULL)) {
        cerr << "Failure in DeviceIoControl\n";
    }

    cout.imbue(std::locale(""));

    //cout << "------- INICIO -------" << endl;

    disco disco_monitorado;
    disco_monitorado.novo.read = disk_info.IdleTime.QuadPart;
    disco_monitorado.novo.write = disk_info.QueryTime.QuadPart;
    //disco_monitorado.novo.read = disk_info.ReadCount;
    //disco_monitorado.novo.read = disk_info.BytesRead.QuadPart/1024;
    //disco_monitorado.novo.write = disk_info.WriteCount;
    //disco_monitorado.novo.write = disk_info.BytesWritten.QuadPart/1024;

    return disco_monitorado;
}
