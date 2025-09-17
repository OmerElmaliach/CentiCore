#include "ExpenseChart.hpp"

ExpenseChart::ExpenseChart(const std::vector<double>& expenses, QWidget* parent) : QChartView(parent) {
    setupChart(expenses);
    setupStyling();
}

void ExpenseChart::setupChart(const std::vector<double>& expenses) {
    // Create and configure chart
    QChart* chart = new QChart();
    chart->setTitle("Monthly Expenses");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create bar series with data
    QBarSet* expenseSet = createBarSet(expenses);
    QBarSeries* series = new QBarSeries();
    series->append(expenseSet);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QBarSeries::LabelsOutsideEnd);
    chart->addSeries(series);
    
    setupAxes(chart, series);
    applyChartStyling(chart);
    setChart(chart);
}

QBarSet* ExpenseChart::createBarSet(const std::vector<double>& expenses) {
    QBarSet* expenseSet = new QBarSet("Expenses");
    for (double value : expenses)
        *expenseSet << value;
    
    // Style the bar set
    expenseSet->setColor(QColor("#ff6d170c"));
    expenseSet->setLabelColor(Qt::white);
    
    return expenseSet;
}

void ExpenseChart::setupAxes(QChart* chart, QBarSeries* series) {
    const QStringList months = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    
    // X-axis
    QBarCategoryAxis* xAxis = new QBarCategoryAxis();
    xAxis->append(months);
    xAxis->setLabelsColor(Qt::white);
    xAxis->setGridLineColor(QColor("#444444"));
    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);
    
    // Y-axis
    QValueAxis* yAxis = new QValueAxis();
    yAxis->setRange(0, 200);
    yAxis->setLabelsColor(Qt::white);
    yAxis->setGridLineColor(QColor("#444444"));
    yAxis->setLabelFormat("%.0f");
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);
}

void ExpenseChart::applyChartStyling(QChart* chart) {
    chart->setBackgroundVisible(false);
    chart->setTitleBrush(QBrush(Qt::white));

    QLegend* legend = chart->legend();
    legend->setVisible(true);
    legend->setLabelColor(Qt::white);
    legend->setBackgroundVisible(false);
}

void ExpenseChart::setupStyling() {
    setRenderHint(QPainter::Antialiasing);
    setStyleSheet("border-radius: 4px; background: transparent;");
    setContentsMargins(0, 0, 0, 0);
}