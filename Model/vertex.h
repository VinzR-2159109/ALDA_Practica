#ifndef VERTEX_H
#define VERTEX_H

#include <QString>

class Vertex
{
public:
    Vertex(const QString &name);
    Vertex(const QString &name, bool infected);
    
    QString getName() const;
    bool getIsInfected() const;
    void setInfected(bool newInfected);

private:
    QString m_name;
    bool m_infected;
};

#endif // VERTEX_H
