#include "vertex.h"


Vertex::Vertex(const QString &name)
    : Vertex(name, false)
{}

Vertex::Vertex(const QString &name, bool infected)
    : m_name(name)
    , m_infected(infected)
{}

QString Vertex::getName() const
{
    return m_name;
}

bool Vertex::getIsInfected() const
{
    return m_infected;
}

void Vertex::setInfected(bool newInfected)
{
    m_infected = newInfected;
}
