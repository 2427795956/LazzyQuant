#ifndef CHAOS2_H
#define CHAOS2_H

#include "addon_trailingstop.h"
#include "../indicator/mql5_indicator.h"

class DivergentBar;
class Fractal;
class Chaos2;

class WiseMan : public EnterSignalNeedConfirm {
protected:
    Chaos2 * outerChaos2;
public:
    int type;
    WiseMan(bool direction, int type, Chaos2 *chaos2);

    QString toString() {
        QString ret = QString("WiseMan%1").arg(type);
        ret += getDirection() ? " Up: " : " Down: ";
        ret += QString("Trigger=%1;Cancel=%2").arg(triggerPrice).arg(cancelPrice);
        return ret;
    }
};

class WiseMan3 : public WiseMan {
    using WiseMan::WiseMan;
    bool confirm(double price) const override;
};

class AOSignal {
    Chaos2 *outerChaos2;

    bool allowLong = false;
    bool allowShort = false;

    double lowestAO = DBL_MAX;
    double highestAO = -DBL_MAX;

public:
    bool upSignal = false;
    bool dnSignal = false;

    AOSignal(Chaos2 *chaos2) : outerChaos2(chaos2) {
    }

    void update(double aoValue);
};

class Chaos2 : public AddOnTrailingStop
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit Chaos2(const QString &id, const QString &instrumentID, int timeFrame, QObject *parent = nullptr);
    friend class WiseMan;
    friend class WiseMan3;
    friend class AOSignal;

    void setParameter(const QVariant &param1, const QVariant &param2, const QVariant &param3,
                      const QVariant &param4, const QVariant &param5, const QVariant &param6,
                      const QVariant &param7, const QVariant &param8, const QVariant &param9) override;
    void setParameter(double AFstep, double AFmax, int openVol, int addOn1Vol, int BBPeriod, double BBDeviations, double stdDevThreshold);

protected:
    double stdDevThreshold;

    MQL5Indicator *bb;
    DivergentBar *divergentBar;
    MQL5Indicator *jawsMA;
    MQL5Indicator *teethMA;
    MQL5Indicator *lipsMA;
    MQL5Indicator *ao;
    Fractal *fractal;

    IndicatorBuffer<double> bbTop;
    IndicatorBuffer<double> bbMiddle;
    IndicatorBuffer<double> bbBottom;
    IndicatorBuffer<double> bbStdDev;
    IndicatorBuffer<bool>   bullishDivergent;
    IndicatorBuffer<bool>   bearishDivergent;
    IndicatorBuffer<double> jaws;
    IndicatorBuffer<double> teeth;
    IndicatorBuffer<double> lips;
    IndicatorBuffer<double> aoBuffer;
    IndicatorBuffer<double> upperFractal;
    IndicatorBuffer<double> lowerFractal;
    IndicatorBuffer<int>    confirmedUpIndex;
    IndicatorBuffer<int>    confirmedDnIndex;

    AOSignal aoSignal;

    void prepareBuffers();
    double getWiseManTriggerPrice(bool direction, int type) const;
    double getWiseManCancelPrice(bool direction, int type) const;
    bool checkWiseMan1Buy()  const;
    bool checkWiseMan1Sell() const;
    bool checkAOUpSignal()   const;
    bool checkAODnSignal()   const;
    bool checkWiseMan3Buy()  const;
    bool checkWiseMan3Sell() const;
    QList<EnterSignalNeedConfirm*> getOpenSignals() override;
    QList<EnterSignalNeedConfirm*> getAddOnSignals() override;

    void onNewBar() override;
};

#endif // CHAOS2_H
