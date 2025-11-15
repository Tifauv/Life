#ifndef StatsGraph_hpp
#define StatsGraph_hpp

#include <QObject>
#include <QLineSeries>


class StatsGraph : public QObject {
    Q_OBJECT

    Q_PROPERTY(QLineSeries* changesSeries   READ changesSeries   WRITE setChangesSeries   NOTIFY changesSeriesChanged   FINAL)
    Q_PROPERTY(uint         maxChanges      READ maxChanges                               NOTIFY maxChangesChanged      FINAL)
    Q_PROPERTY(QLineSeries* durationSeries  READ durationSeries  WRITE setDurationSeries  NOTIFY durationSeriesChanged  FINAL)
    Q_PROPERTY(qint64       maxDuration     READ maxDuration                              NOTIFY maxDurationChanged     FINAL)

public:
    explicit StatsGraph(QObject* p_parent = nullptr);

    QLineSeries* changesSeries()  const;
    QLineSeries* durationSeries() const;

    uint maxChanges() const;
    qint64 maxDuration() const;

    void setChangesSeries(QLineSeries* p_series);
    void setDurationSeries(QLineSeries* p_series);

    void appendSlice(uint p_stepId, uint p_changes, qint64 p_elapsed);
    void clearSeries();

public Q_SLOTS:
    void onAddSlice(uint p_stepId, uint p_changes, qint64 p_elapsed);
    void onClearSeries();

Q_SIGNALS:
    void changesSeriesChanged();
    void durationSeriesChanged();

    void maxChangesChanged(uint);
    void maxDurationChanged(qint64);

protected:
    void updateMaxChanges(uint);
    void updateMaxDuration(qint64);

private:
    QLineSeries* m_changesSeries;
    QLineSeries* m_durationSeries;

    uint   m_maxChanges;
    qint64 m_maxDuration;
};

#endif
