#include "strategyfactory.h"

#include "strategies/topologicalorder.h"
#include <strategy1.h>
#include <MatrixExponentiation.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Strategy1:
            return new Strategy1();
        case AllStrategies::MatrixExponentiation:
            return new MatrixExponentiation();
        case AllStrategies::Topologicalorder:
            return new topologicalOrder();
    }
    //throw std::exception("Strategy not implemented");
}
