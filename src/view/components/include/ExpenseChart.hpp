#pragma once

#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLegend>
#include <QBrush>
#include <QColor>
#include <vector>

/**
 * @class ExpenseChart
 * @brief A custom QChartView widget that displays monthly expense data as a styled bar chart
 * 
 * This widget creates a dark-themed bar chart showing expense values across 12 months.
 */
class ExpenseChart : public QChartView {
    Q_OBJECT

public:
    /**
     * @brief Constructs an ExpenseChart with the given expense data
     * @param expenses Vector of 12 double values representing monthly expenses (Jan-Dec)
     * @param parent Optional parent widget (default: nullptr)
     */
    ExpenseChart(const std::vector<double>& expenses, QWidget* parent = nullptr);
    
private:
    /**
     * @brief Main chart setup method that orchestrates the chart creation
     * @param expenses The expense data to display
     */
    void setupChart(const std::vector<double>& expenses);
    
    /**
     * @brief Configures the X and Y axes for the chart
     * @param chart Pointer to the chart to configure
     * @param series Pointer to the bar series to attach axes to
     */
    void setupAxes(QChart* chart, QBarSeries* series);
    
    /**
     * @brief Applies styling to the chart (background, title, legend)
     * @param chart Pointer to the chart to style
     */
    void applyChartStyling(QChart* chart);
    
    /**
     * @brief Configures the chart view styling and rendering options
     */
    void setupStyling();
    
    /**
     * @brief Creates and configures the bar set with expense data
     * @param expenses Vector of expense values to add to the bar set
     * @return Pointer to the configured QBarSet with styling applied
     */
    QBarSet* createBarSet(const std::vector<double>& expenses);
};