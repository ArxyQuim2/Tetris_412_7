#include <stdlib.h>
#include "InfoJoc.h"


class NodeFigura
{
public:
    NodeFigura() { m_siguiente = nullptr; }
    ~NodeFigura() {}
    NodeFigura(const InfoFigura& valor) { m_valor = valor; m_siguiente = nullptr; }
    NodeFigura* obtenerSiguiente() { return m_siguiente; }
    void setSiguiente(NodeFigura* siguiente) { m_siguiente = siguiente; }
    InfoFigura getValor() const { return m_valor; }
    void setValor(const InfoFigura& valor) { m_valor = valor; }
private:
    InfoFigura m_valor;
    NodeFigura* m_siguiente;
};
