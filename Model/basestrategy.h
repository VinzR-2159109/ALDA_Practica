#ifndef BASESTRATEGY_H
#define BASESTRATEGY_H

#include "Model/graphdata.h"
class BaseStrategy
{
public:
    virtual ~BaseStrategy();

    void setData(const GraphData &data);

    /**
     * @brief executes the strategy
     * @return a list of vertices that are the source
     */
    virtual QVector<Vertex*> execute() = 0;

protected:
    GraphData m_data;
};

#endif // BASESTRATEGY_H
