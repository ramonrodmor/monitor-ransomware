#include "monitorhoneypot.h"

static int meu_codigo = HONEYPOT;
static ControleNotificacao * controleNotificacao;

// inicializa monitor
void MonitorHoneypot::iniciar_monitor(LPTSTR caminho, ControleNotificacao * controle) {

    controleNotificacao = controle;
    stringstream ss;
    ss << "Monitor honeypot iniciado observando: " << converter_lptstr(caminho) << " <dir>";
    string note = ss.str();
    // criação da notificação
    Notificacao a{ meu_codigo, note };
    controleNotificacao->notificar(a);
    a.~Notificacao();
    // inicializa observação no diretório especificado
    observar_diretorio(caminho);
}

// observação do diretório
void MonitorHoneypot::observar_diretorio(LPTSTR diretorio) {

    // variáveis de controle
    DWORD dwWaitStatus;
    HANDLE dwChangeHandles[2];
    TCHAR lpDrive[4];
    TCHAR lpFile[_MAX_FNAME];
    TCHAR lpExt[_MAX_EXT];
    _tsplitpath_s(diretorio, lpDrive, 4, NULL, 0, lpFile, _MAX_FNAME, lpExt, _MAX_EXT);
    lpDrive[2] = (TCHAR)'\\';
    lpDrive[3] = (TCHAR)'\0';

    // criação de função de notificação de diretório
    dwChangeHandles[0] = FindFirstChangeNotification(
        diretorio, // diretório observado
        FALSE, // para não observar subdiretórios
        FILE_NOTIFY_CHANGE_FILE_NAME); // observa mudança no nome de arquivos

    // saída de falha da função
    if (dwChangeHandles[0] == INVALID_HANDLE_VALUE) {
        cout << endl << "ERRO: Primeiro observador falhou." << endl;
        ExitProcess(GetLastError());
    }

    // criação da função de notificação de subdiretórios
    dwChangeHandles[1] = FindFirstChangeNotification(
        lpDrive, // diretório observado
        TRUE, // para observar subdiretórios
        FILE_NOTIFY_CHANGE_DIR_NAME); // observa mudança de nome de diretórios

    // saída de falha na função
    if (dwChangeHandles[1] == INVALID_HANDLE_VALUE) {
        cout << endl << "ERRO: Primeiro observador falhou." << endl;
        ExitProcess(GetLastError());
    }

    // validação final para os dois "observadores"
    if ((dwChangeHandles[0] == NULL) || (dwChangeHandles[1] == NULL)) {
        cout << endl << "ERRO: NULL inexperado no primeiro observador." << endl;
        ExitProcess(GetLastError());
    }

    // realiza observação e atualização dos diretórios
    while (TRUE) {
        // estado da observação
        dwWaitStatus = WaitForMultipleObjects(2, dwChangeHandles,
            FALSE, INFINITE);

        // tomada de decisões com base no estado da observação
        switch (dwWaitStatus) {
        case WAIT_OBJECT_0:
            // um arquivo foi criado ou deletado no diretório
            // atualiza o diretório e reinicia a notificação
            atualiza_diretorio(diretorio);
            if (FindNextChangeNotification(dwChangeHandles[0]) == FALSE) {
                cout << endl << "ERRO: Primeiro observador falhou." << endl;
                ExitProcess(GetLastError());
            }
            break;

        case WAIT_OBJECT_0 + 1:
            // um diretório foi criado ou deletado
            // atualiza a arvore do diretório e reinica a notificação
            atualiza_caminho(lpDrive);
            if (FindNextChangeNotification(dwChangeHandles[1]) == FALSE) {
                cout << endl << "ERRO: Primeiro observador falhou." << endl;
                ExitProcess(GetLastError());
            }
            break;

        case WAIT_TIMEOUT:
            // ocorre timeout quando for definido um valor de tempo de observação
            cout << endl << "Nada foi alterado na janela de tempo especificada." << endl;
            break;

        default:
            // estado inexperado na observação
            cout << endl << "ERRO: Estado sem tratamento." << endl;
            ExitProcess(GetLastError());
            break;
        }
    }
}

// atualização no diretório
void MonitorHoneypot::atualiza_diretorio(LPTSTR diretorio) {
    // criação da mensagem
    stringstream ss;
    ss <<"Um arquivo foi criado ou deletado no diretorio " << converter_lptstr(diretorio);
    string note = ss.str();
    // criação da notificação
    Notificacao a{ meu_codigo, note };
    controleNotificacao->notificar(a);
}

// atualização na árvore
void MonitorHoneypot::atualiza_caminho(LPTSTR lpDrive) {
    // criação da mensagem
    stringstream ss;
    ss << "Uma pasta foi criada ou deletada no diretorio " << converter_lptstr(lpDrive);
    string note = ss.str();
    // criação da notificação
    Notificacao a{ meu_codigo, note };
    controleNotificacao->notificar(a);
}

// conversão de LPTSTR para string
string MonitorHoneypot::converter_lptstr (LPTSTR paraString) {

    uint size = wcslen(paraString);
    stringstream ss;
    for (uint i=0; i<size; i++) {
        if (char(paraString[i] == '\\')) {
            ss << '\\';
        } else {
            ss << char(paraString[i]);
        }
    }
    string st;
    ss >> st;
    return st;
}
