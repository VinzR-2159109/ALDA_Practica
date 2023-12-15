#include "strategyfactory.h"

#include "strategy1.h"
#include "reacheblematrix.h"

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Strategy1:
            return new Strategy1();
        case AllStrategies::ReachableMatrix:
            return new ReachableMatrix();
    }
    throw std::exception("Strategy not implemented");
}
