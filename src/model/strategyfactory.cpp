#include "strategyfactory.h"

#include <bfs.h>
#include <reachablematrix.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Bfs:
            return new BFS();
        case AllStrategies::ReachableMatrix:
            return new ReachableMatrix();
    }
    throw std::exception("Strategy not implemented");
}
