#include "strategyfactory.h"

#include "strategies/topologicalorder.h"
#include <bfs.h>
#include <reachablematrix.h>

BaseStrategy *StrategyFactory::getStrategy(AllStrategies strategy)
{
    switch (strategy) {
        case AllStrategies::Topologicalorder:
            return new topologicalOrder();
        case AllStrategies::Bfs:
            return new BFS();
        case AllStrategies::ReachableMatrix:
            return new ReachableMatrix();
    }
    //throw std::exception("Strategy not implemented");
}
