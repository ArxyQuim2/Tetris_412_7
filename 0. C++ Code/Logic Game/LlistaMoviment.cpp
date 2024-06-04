#include "LlistaMoviment.h"

LlistaMoviment::~LlistaMoviment()
{
	while (m_primer != nullptr)
		limpiar();
}

LlistaMoviment::LlistaMoviment(const LlistaMoviment& l)
{
	m_primer = nullptr;
	m_ultim = nullptr;
	NodeMoviment* aux = l.m_primer;
	NodeMoviment* aux_nova = m_primer;
	while (aux != nullptr)
	{
		aux_nova = insereix(aux->getValor());
		aux = aux->getSiguiente();
	}

}

LlistaMoviment& LlistaMoviment::operator=(const LlistaMoviment& l)
{
	if (this != &l)
	{
		while (m_primer != nullptr)
			limpiar();
		NodeMoviment* aux = l.m_primer;
		NodeMoviment* aux_nova = m_primer;
		while (aux != nullptr)
		{
			aux_nova = insereix(aux->getValor());
			aux = aux->getSiguiente();
		}
	}
	return *this;
}

NodeMoviment* LlistaMoviment::insereix(const TipusMoviment& valor)
{
	NodeMoviment* aux = new NodeMoviment;
	if (aux != nullptr)
	{
		aux->setValor(valor);
		aux->setSiguiente(nullptr);
		if (m_primer == nullptr)
		{
			m_primer = aux;
		}
		else
		{
			m_ultim->setSiguiente(aux);
		}
		m_ultim = aux;
	}

	return aux;
}

void LlistaMoviment::limpiar()
{
	NodeMoviment* aux;
	if (m_primer == m_ultim)
	{
		delete m_primer;
		m_primer = nullptr;
		m_ultim = nullptr;
	}
	else
	{
		aux = m_primer->getSiguiente();
		delete m_primer;
		m_primer = aux;
	}
}

int LlistaMoviment::getNElements() const
{
	int nElements = 0;
	NodeMoviment* aux = m_primer;
	while (aux != NULL)
	{
		nElements++;
		aux = aux->getSiguiente();
	}

	return nElements;
}
