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
#include <QSettings>
#include <QLineSeries>

/**
 * @class ExpenseChart
 * @brief A custom QChartView widget that displays monthly expense data as a styled bar chart
 * 
 * This widget creates a dark-themed bar chart showing expense values across 12 months.
 */
class ExpenseChart : public QChartView {
    Q_OBJECT
    
private:
    QBarSet* m_expenseSet;

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

public:
    /**
     * @brief Constructs an ExpenseChart with the given expense data
     * @param expenses Vector of 12 double values representing monthly expenses (Jan-Dec)
     * @param parent Optional parent widget (default: nullptr)
     */
    ExpenseChart(const std::vector<double>& expenses, QWidget* parent = nullptr);

    /**
     * @brief Updates the expense value for a specific month in the chart.
     *
     * This function modifies the value of the bar corresponding to the given
     * month in the chart’s QBarSet. After calling this function, the chart
     * will automatically reflect the updated value.
     *
     * @param month The month index to update (0-based). For example:
     *              0 = January, 1 = February, ..., 11 = December.
     * @param amount The new expense amount for the given month.
     */
    void refreshMonth(int month ,double amount);
};