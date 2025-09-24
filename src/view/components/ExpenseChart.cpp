#include "ExpenseChart.hpp"

ExpenseChart::ExpenseChart(const std::vector<double>& expenses, QWidget* parent) : QChartView(parent) {
    setupChart(expenses);
    setupStyling();
}

void ExpenseChart::refreshMonth(int month ,double amount) {
    m_expenseSet->replace(month, amount);
}

void ExpenseChart::setupChart(const std::vector<double>& expenses) {
    // Create and configure chart
    QChart* chart = new QChart();
    chart->setTitle("Monthly Expenses");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create bar series with data
    m_expenseSet = createBarSet(expenses);
    QBarSeries* series = new QBarSeries();
    series->append(m_expenseSet);
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
    QSettings settings(":/config/config/app.conf", QSettings::IniFormat);
    settings.beginGroup("Finance");
    double budget = settings.value("monthly_budget").toDouble();

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
    yAxis->setRange(0, budget + 50);
    yAxis->setLabelsColor(Qt::white);
    yAxis->setGridLineColor(QColor("#444444"));
    yAxis->setLabelFormat("%.0f");
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    // Add threshhold line
    QLineSeries* line = new QLineSeries();
    line->setName("Budget Limit");
    line->append(-1, budget);
    line->append(12, budget);

    QPen pen(Qt::red);
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
    line->setPen(pen);

    chart->addSeries(line);
    line->attachAxis(xAxis);
    line->attachAxis(yAxis);
    
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
    setStyleSheet("background: transparent;");
    setContentsMargins(0, 0, 0, 0);
}