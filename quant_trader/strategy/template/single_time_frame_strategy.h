#ifndef SINGLE_TIME_FRAME_STRATEGY_H
#define SINGLE_TIME_FRAME_STRATEGY_H

#include "../../indicator/indicator_functions.h"
#include "abstract_strategy.h"
#include "trailing_stop.h"

class SingleTimeFrameStrategy : public IndicatorFunctions, public AbstractStrategy
{
    Q_OBJECT

protected:
    QList<Bar>* barList;
    Bar* lastBar;
    _ListProxy<Bar> bars;

    TrailingStop trailingStop;

    void setPosition(int newPosition);
    void resetPosition();
    void loadStatus() override;
    void saveStatus() override;
    virtual void checkTPSL(double price);
    virtual void onNewBar() = 0;

public:
    explicit SingleTimeFrameStrategy(const QString &id, const QString &instrumentID, int timeFrame, QObject *parent = 0);
    ~SingleTimeFrameStrategy();

    // Should call setBarList after setParameter
    void setBarList(const QMap<int, QPair<QList<Bar>*, Bar*>> &listAndLast) override;

    void checkIfNewBar(int newBarTimeFrame) override;
    void onNewTick(int time, double lastPrice) override;

};

#endif // SINGLE_TIME_FRAME_STRATEGY_H
