#include "strategyfactory.h"

#include <Model/Strategies/strategy1.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
    case AllStrategies::Strategy1: return new Strategy1();
    }
}
