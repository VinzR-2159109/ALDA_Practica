#ifndef STRATEGYCONTEXT_H
#define STRATEGYCONTEXT_H

#include "basestrategy.h"

class StrategyContext
{
public:
    StrategyContext();
    ~StrategyContext();

    BaseStrategy *getStrategy() const;
    void setStrategy(BaseStrategy *newStrategy);

    QVector<Vertex*> runStrategy();

private:
    BaseStrategy *m_strategy;
};

#endif // STRATEGYCONTEXT_H
