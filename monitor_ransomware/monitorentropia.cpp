#include "monitorentropia.h"

static int meu_codigo = ENTROPIA;
static string caminho;
static ControleNotificacao * controleNotificacao;

void MonitorEntropia::iniciar_monitor(string arquivo, ControleNotificacao * controle)
{

    caminho = arquivo;
    controleNotificacao = controle;

    vetor_freq vetor;
    float entropia_antiga, entropia_nova;
    vetor = abrir_arquivo(caminho);
    if (vetor.total != -1) {
        entropia_antiga = calcula_entropia(vetor);
        stringstream ss;
        ss << "Monitor iniciado observando " << caminho << ". ";
        string note = ss.str();
        // criação da notificação
        Notificacao a{ meu_codigo, note };
        controleNotificacao->notificar(a);
        a.~Notificacao();
    }
    else {
        entropia_antiga = 0;
    }

    while (true) {
        vetor = abrir_arquivo(caminho);

        if (vetor.total != -1) {
            entropia_nova = calcula_entropia(vetor);

            if (entropia_nova != entropia_antiga) {
                // criação da mensagem
                stringstream ss;
                ss << "Mudanca na entropia! Diferenca de " << entropia_nova - entropia_antiga
                    << ". A nova entropia e " << entropia_nova;
                string note = ss.str();
                // criação da notificação
                Notificacao a{ meu_codigo, note };
                controleNotificacao->notificar(a);
                a.~Notificacao();
            }
        }
        else {
            entropia_nova = 0;
        }

        Sleep(2000);
        entropia_antiga = entropia_nova;
    }
}

float MonitorEntropia::calcula_entropia(vetor_freq vetor) {
    float freq = 0;
    float entropia = 0.0;
    for (int i = 0; i < ASCII; i++) {
        if (vetor.cont_simbolos[i] > 0) {
            freq = (float)vetor.cont_simbolos[i] / (float)vetor.total;
            entropia += ((-1) * freq * log2(freq));
        }
    }

    return entropia;
}

vetor_freq MonitorEntropia::abrir_arquivo(string diretorio) {
    ifstream fin;
    fin.open(diretorio);
    if (!fin.is_open())	{
        stringstream ss;
        ss << "Nao foi possivel abrir o arquivo " << diretorio << "." << endl
            << "O arquivo pode ter sido deletado!";
        string note = ss.str();
        // criação da notificação
        Notificacao a{ meu_codigo, note };
        controleNotificacao->notificar(a);
        a.~Notificacao();

        vetor_freq vetor_de_erro;
        vetor_de_erro.total = -1;

        return vetor_de_erro;
    }

    vetor_freq vetor;
    vetor.total=0;
    for (int i=0; i<ASCII; i++) {
        vetor.cont_simbolos[i]=0;
    }

    char ch;
    fin.get(ch);

    while (!fin.eof()) {
        vetor.total++;
        vetor.cont_simbolos[(int)ch]++;

        fin.get(ch);
    }

    fin.close();

    return vetor;
}
