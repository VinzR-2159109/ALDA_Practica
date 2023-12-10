#include "graphcontext.h"


GraphContext::GraphContext(BaseGraphStrategy *strategy) : m_strategy(strategy)
{}

BaseGraphStrategy *GraphContext::getStrategy() const
{
    return m_strategy;
}
