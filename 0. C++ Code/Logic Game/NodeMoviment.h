#include <stdlib.h>
#include "InfoJoc.h"


class NodeMoviment
{
public:
    NodeMoviment() { m_siguiente = nullptr; };
    ~NodeMoviment() {};
    NodeMoviment(const TipusMoviment& valor) { m_valor = valor; m_siguiente = nullptr; }
    NodeMoviment* getSiguiente() { return m_siguiente; }
    void setSiguiente(NodeMoviment* siguiente) { m_siguiente = siguiente; }
    TipusMoviment getValor() { return m_valor; }
    void setValor(const TipusMoviment& valor) { m_valor = valor; }
private:
    TipusMoviment m_valor;
    NodeMoviment* m_siguiente;
};
