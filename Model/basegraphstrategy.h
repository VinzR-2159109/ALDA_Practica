#ifndef BASEGRAPHSTRATEGY_H
#define BASEGRAPHSTRATEGY_H


class BaseGraphStrategy
{
public:
    BaseGraphStrategy();

    virtual void execute() const = 0;
};

#endif // BASEGRAPHSTRATEGY_H
