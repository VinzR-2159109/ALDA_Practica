#include "basestrategy.h"
#include <iostream>

BaseStrategy::~BaseStrategy()
{}

void BaseStrategy::setData(GraphData *data)
{
    m_data = data;
}
