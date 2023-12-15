#include "strategyfactory.h"

#include <bfs.h>
#include <MatrixExponentiation.h>
#include <BFSSeperate.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Bfs:
            return new BFS();
        case AllStrategies::BfsSeperate:
            return new BFSSeperate();
        case AllStrategies::ReachableMatrix:
            return new ReachableMatrix();
    }
    throw std::exception("Strategy not implemented");
}
