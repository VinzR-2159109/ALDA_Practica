#include "strategyfactory.h"

#include <strategy1.h>
#include <MatrixExponentiation.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Strategy1:
            return new Strategy1();
        case AllStrategies::MatrixExponentiation:
            return new MatrixExponentiation();
    }
    throw std::exception("Strategy not implemented");
}
