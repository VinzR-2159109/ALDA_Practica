#include "strategyfactory.h"

#include <Strategy2.h>
#include <bfs.h>
#include <reachablematrix.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Bfs:
            return new BFS();
        case AllStrategies::ReachableMatrix:
            return new ReachableMatrix();
        case AllStrategies::Strategy2:
            return new Strategy2();
    }
    throw std::exception("Strategy not implemented");
}
