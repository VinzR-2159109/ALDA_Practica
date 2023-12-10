#ifndef GRAPHCONTEXT_H
#define GRAPHCONTEXT_H

#include "basegraphstrategy.h"

class GraphContext
{
public:
    GraphContext(BaseGraphStrategy *strategy);

    BaseGraphStrategy *getStrategy() const;

private:
    BaseGraphStrategy *m_strategy;
};

#endif // GRAPHCONTEXT_H
