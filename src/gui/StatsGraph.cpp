#include "StatsGraph.hpp"

#include <QDebug>
#include <QColor>


StatsGraph::StatsGraph(QObject* p_parent):
QObject(p_parent),
m_changesSeries(new QLineSeries),
m_durationSeries(new QLineSeries) {
    m_changesSeries->setColor(QColorConstants::Svg::dodgerblue);
    m_durationSeries->setColor(QColorConstants::Svg::darkorange);
}


QLineSeries* StatsGraph::changesSeries() const {
    return m_changesSeries;
}


QLineSeries* StatsGraph::durationSeries() const {
    return m_durationSeries;
}


uint StatsGraph::maxChanges() const {
    return m_maxChanges;
}


qint64 StatsGraph::maxDuration() const {
    return m_maxDuration;
}


void StatsGraph::setChangesSeries(QLineSeries* p_series) {
    if (m_changesSeries != p_series) {
        m_changesSeries = p_series;
        Q_EMIT changesSeriesChanged();
    }
}


void StatsGraph::setDurationSeries(QLineSeries* p_series) {
    if (m_durationSeries != p_series) {
        m_durationSeries = p_series;
        Q_EMIT durationSeriesChanged();
    }
}

void StatsGraph::appendSlice(uint p_stepId, uint p_changes, qint64 p_elapsed) {
    m_changesSeries->append(p_stepId, p_changes);
    updateMaxChanges(p_changes);

    m_durationSeries->append(p_stepId, p_elapsed);
    updateMaxDuration(p_elapsed);
}


void StatsGraph::clearSeries() {
    m_changesSeries->clear();
    m_maxChanges = 0;
    m_durationSeries->clear();
    m_maxDuration = 0;
}


// PUBLIC SLOTS
void StatsGraph::onAddSlice(uint p_stepId, uint p_changes, qint64 p_elapsed) {
    appendSlice(p_stepId, p_changes, p_elapsed);
}


void StatsGraph::onClearSeries() {
    clearSeries();
}


// INTERNAL METHODS
void StatsGraph::updateMaxChanges(uint p_changes) {
    if (p_changes > m_maxChanges) {
        m_maxChanges = p_changes;
        Q_EMIT maxChangesChanged(m_maxChanges);
    }
}


void StatsGraph::updateMaxDuration(qint64 p_duration) {
    if (p_duration > m_maxDuration) {
        m_maxDuration = p_duration;
        Q_EMIT maxDurationChanged(m_maxDuration);
    }
}
