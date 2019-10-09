#include "notificacao.h"

// construtor que recebe o tipo de monitor que lançou a notificação e seu conteúdo
Notificacao::Notificacao(int monitor_name, string note) {
    set_monitor (monitor_name);
    set_noti (note);
}

Notificacao::~Notificacao() {
}

// gets e sets
int Notificacao::get_monitor() {
    return this->monitor;
}

void Notificacao::set_monitor(int monitor) {
    this->monitor = monitor;
}

string Notificacao::get_noti() {
    return string(this->noti);
}

void Notificacao::set_noti(string noti) {
    this->noti = noti;
}

