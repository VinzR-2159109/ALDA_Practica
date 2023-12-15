#include <gtest/gtest.h>

#include <QDir>
#include <QVector>
#include <StrategyContext.h>

#include <graphdata.h>
#include <Repository.h>
#include <StrategyFactory.h>
#include <basestrategy.h>

TEST(Test_Bfs, Normal) {

    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Bfs);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/1_source_in_graph.txt");
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

TEST(Test_Bfs, Disconnected_Graph) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Bfs);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/disconnected_graph.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    if (result.size() != 2)
        FAIL() << "Result does not have the correct amount of Vertices";

    for (const auto &resultVertex : result) {
        if (!QString("AD").contains(resultVertex->getName())) {
            FAIL() << "Result is not the correct solution";
            break;
        }
    }

    delete data;
}

TEST(Test_Bfs, Lowest_Number_Of_Solutions) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Bfs);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/directional_graph.txt");
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

TEST(Test_Bfs, Infected_Vertex_Out_Of_Range) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Bfs);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/infected_vertex_out_of_range.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    if (result.size() != 2)
        FAIL() << "Result does not have the correct amount of Vertices";

    for (const auto &resultVertex : result) {
        if (!QString("BE").contains(resultVertex->getName())) {
            FAIL() << "Result is not the correct solution";
            break;
        }
    }
}

TEST(Test_Bfs, No_Connections) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Bfs);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/no_connections.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    if (result.size() != 3)
        FAIL() << "Result does not have the correct amount of Vertices";

    for (const auto &resultVertex : result) {
        if (!QString("ABC").contains(resultVertex->getName())) {
            FAIL() << "Result is not the correct solution";
            break;
        }
    }
}

TEST(Test_Bfs, No_Solutions) {
    // Create strategy
    BaseStrategy *currentStrategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Bfs);
    StrategyContext context;

    // Give data to strategy
    context.setStrategy(currentStrategy);

    // Load data
    QString filePath = QDir::currentPath().append("/data/no_solution.txt");
    GraphData *data = Repository().LoadFile(filePath).graphData;
    context.getStrategy()->setData(data);

    // Run strategy
    auto result = context.runStrategy();

    // Check if result is correct
    if (result.size() != 0)
        FAIL() << "Result has a solution";
}
