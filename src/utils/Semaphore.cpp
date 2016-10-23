#include "Semaphore.h"

#include <string>

Semaphore::Semaphore(const std::string &nombre, const int valorInicial) :
        instance(Semaforo(nombre, valorInicial)) {
}

Semaphore::~Semaphore() { }

int Semaphore::p() {
    return instance.p();
}

int Semaphore::v() {
    return instance.v();
}

void Semaphore::erase() const {
    instance.eliminar();
}
