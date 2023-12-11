#include "basestrategy.h"

BaseStrategy::~BaseStrategy()
{ }

void BaseStrategy::setData(const GraphData &data)
{
    m_data = data;
}
