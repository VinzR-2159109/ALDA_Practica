#include <gtest/gtest.h>

#include <QDir>
#include <QVector>
#include <StrategyContext.h>

#include <graphdata.h>
#include <Repository.h>
#include <StrategyFactory.h>
#include <basestrategy.h>

TEST(Test_Strategy1, Normal) {

    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Strategy1);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/Test_Normal.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    // Check if result is correct
    if (result.size() != 1)
        FAIL() << "Result does not have the correct amount of Vertices";

    for (const auto &resultVertex : result) {
        if (!QString("C").contains(resultVertex->getName())) {
            FAIL() << "Result is not the correct solution";
            break;
        }
    }

    delete data;
}

TEST(Test_Strategy1, Disconnected_Graph) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Strategy1);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/Test_DisconnectedGraph.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    if (result.size() != 3)
        FAIL() << "Result does not have the correct amount of Vertices";

    for (const auto &resultVertex : result) {
        if (!QString("A, B, C").contains(resultVertex->getName())) {
            FAIL() << "Result is not the correct solution";
            break;
        }
    }

    delete data;
}

TEST(Test_Strategy1, Lowest_Number_Of_Solutions) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Strategy1);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/Test_LowestNumberOfSolutions.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    if (result.size() != 1)
        FAIL() << "Result does not have the correct amount of Vertices";

    for (const auto &resultVertex : result) {
        if (!QString("A").contains(resultVertex->getName())) {
            FAIL() << "Result is not the correct solution";
            break;
        }
    }
}
