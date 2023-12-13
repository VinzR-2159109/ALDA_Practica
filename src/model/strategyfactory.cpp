#include "strategyfactory.h"

#include "strategy1.h"

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Strategy1: return new Strategy1();
    }
    throw std::exception("Strategy not implemented");
}
