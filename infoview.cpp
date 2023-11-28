//Vinz Roosen & Lars Gielen
#include "infoview.h"

InfoView::InfoView()
    : m_searchTimeSum{0}
    , m_searchAmount{0}
    , m_loadTimeSum{0}
    , m_loadAmount{0}
{
    m_loadedProducts = new QLabel("Products inserted: 0");
    m_lastLoadTime = new QLabel("Last insert time: ? µs");
    m_averageLoadTime = new QLabel("Average insert tile (total): ?");
    m_lastSearchTime = new QLabel("Last search time: ? ms");
    m_averageSearchTime = new QLabel("average search time: ? µs");
    m_loadingTime = new QLabel("Loading time: 0 ms");

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(m_loadedProducts);
    layout->addWidget(m_lastLoadTime);
    layout->addWidget(m_averageLoadTime);
    layout->addWidget(m_lastSearchTime);
    layout->addWidget(m_averageSearchTime);
    layout->addWidget(m_loadingTime);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout);

}

void InfoView::setInsertedProduct(long long loadTime)
{
    m_loadAmount++;
    m_loadTimeSum += loadTime;

    m_loadedProducts->setText(QString("Products inserted: %1").arg(m_loadAmount));
    m_lastLoadTime->setText(QString("Last insert time: %1 µs").arg(loadTime));
    m_averageLoadTime->setText(QString("Average insert time: %1 µs").arg(m_loadTimeSum / m_loadAmount));

    setLoadingTime();
}

void InfoView::setLastSearchTime(int searchTime)
{
    m_searchAmount++;
    m_searchTimeSum += searchTime;

    m_lastSearchTime->setText(QString("Last search time %1 µs").arg(searchTime));
    m_averageSearchTime->setText(QString("Average search time: %1 µs").arg(m_searchTimeSum / m_searchAmount));
}

void InfoView::startedLoading()
{
    m_startTime = QTime::currentTime();
    setLoadingTime();
}

void InfoView::stoppedLoading()
{
    setLoadingTime();
}

void InfoView::setLoadingTime()
{
    int timeDifference = m_startTime.msecsTo(QTime::currentTime());
    m_loadingTime->setText(QString("Loading time: %1").arg(QTime::fromMSecsSinceStartOfDay(timeDifference).toString("hh:mm:ss")));
}

void InfoView::setError(QString errorMessage)
{
    m_loadedProducts->setText(errorMessage);
    m_lastLoadTime->setText(errorMessage);
    m_averageLoadTime->setText(errorMessage);
    m_lastSearchTime->setText(errorMessage);
    m_averageSearchTime->setText(errorMessage);
    m_loadingTime->setText(errorMessage);
}
