#include "strategycontext.h"

StrategyContext::StrategyContext() : m_strategy{nullptr}
{ }

StrategyContext::~StrategyContext()
{
    delete m_strategy;
}

BaseStrategy *StrategyContext::getStrategy() const
{
    return m_strategy;
}

void StrategyContext::setStrategy(BaseStrategy *newStrategy)
{
    delete m_strategy;
    m_strategy = newStrategy;
}

QVector<Vertex*> StrategyContext::runStrategy()
{
    return m_strategy->execute();
}
