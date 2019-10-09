#ifndef NOTIFICACAO_H
#define NOTIFICACAO_H

#include <string>

using namespace std;

// modelagem da notificação
class Notificacao
{
private:
    int monitor; // identificação do monitor
    string noti; // texto da notificação lançada
public:
    Notificacao(int, string); // criação da notificação
    ~Notificacao();
    // gets sets dos atributos
    int get_monitor();
    void set_monitor(int);
    string get_noti();
    void set_noti(string);
};

#endif // NOTIFICACAO_H
