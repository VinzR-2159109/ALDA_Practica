#include "graphcontext.h"


GraphContext::GraphContext(BaseGraphStrategy *strategy) : m_strategy(strategy)
{}

BaseGraphStrategy *GraphContext::getStrategy() const
{
    return m_strategy;
}

void GraphContext::setStrategy(BaseGraphStrategy *newStrategy)
{
    m_strategy = newStrategy;
}
