#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H

#include "basestrategy.h"

#include <QObject>

class StrategyFactory : public QObject
{
    Q_OBJECT

public:
    enum class AllStrategies {
        Strategy1,
        MatrixExponentiation
    };
    Q_ENUM(AllStrategies)

    BaseStrategy *getStrategy(AllStrategies strategy);
};

#endif // STRATEGYFACTORY_H
