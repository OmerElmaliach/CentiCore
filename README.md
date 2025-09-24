# CentiCore 🦌

A comprehensive financial dashboard application for tracking expenses, managing investment portfolios, and monitoring market performance in real-time.

## Features

### 📊 Dashboard Overview
- **Financial Summary Cards**: Monthly Balance, Available Cash, and Net Worth tracking
- **Monthly Expense Tracking**: Visual charts showing expenses vs budget limits
- **Market Leaders**: Real-time display of top performing stocks
- **Expense Categorization**: Detailed breakdown by categories (Utilities, Food, Entertainment, etc.)

### 💰 Investment Portfolio Management
- **Real-time Stock Tracking**: Monitor your stock positions with live price updates
- **Cryptocurrency Support**: Track Bitcoin, Ethereum, and other crypto investments
- **Portfolio Analytics**: 
  - Total portfolio value
  - Daily profit/loss calculations
  - Individual asset performance metrics
  - Percentage and dollar change tracking

### 📈 Market Data Integration
- Live stock prices and market data
- Daily change percentages and dollar amounts
- Portfolio performance visualization
- Market trend indicators

## Screenshots

### Dashboard View
![Dashboard](screenshot1.png)
*Main dashboard showing financial overview, monthly expenses, and market leaders*

### Portfolio Management
![Portfolio](screenshot2.png)
*Detailed view of stock and cryptocurrency holdings with real-time valuations*

## Installation & Setup

### Prerequisites
- Qt6 framework
- C++ compiler (GCC, Clang, or MSVC)
- CMake (3.16 or higher) or qmake
- Finnhub API account for market data

### Environment Configuration

Create an environment file at `src/view/resources/config/app.env` with the following variables:

```env
FINNHUB_API_KEY=your_finnhub_api_key_here
AVAILABLE_CASH=your_available_cash_amount
```

#### Getting Your Finnhub API Key
1. Visit [Finnhub.io](https://finnhub.io)
2. Sign up for a free account
3. Navigate to your dashboard to find your API key
4. Copy the API key to your `app.env` file

### Installation Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/centicore.git
   cd centicore
   ```

2. **Start the application**
   ```bash
   cd src
   ./start.sh
   ```

## Usage

### Navigation
- **Dashboard**: Overview of your financial status and recent market activity
- **Stocks/Crypto**: Detailed portfolio management and asset tracking
- **Statistics**: Historical data and performance analytics
- **Settings**: Application configuration and preferences

### Adding Investments
1. Navigate to the "Stocks/Crypto" section
2. Click the "+" button to add new positions
3. Enter the stock symbol and quantity details
4. Your portfolio will automatically update with real-time data

### Expense Tracking
- Monthly expenses are automatically categorized and displayed
- Set budget limits to monitor spending against targets

## Configuration

### Supported Assets
- **Stocks**: All major US stocks (NASDAQ, NYSE)
- **Cryptocurrencies**: Bitcoin (BTCUSDT), Ethereum (ETHUSDT), and other major pairs

### Data Sources
- Market data powered by Finnhub API
- Real-time price updates
- Historical data for trend analysis

## Technologies Used

- **Framework**: Qt6 with C++
- **GUI**: Qt Widgets for native desktop interface
- **API Integration**: Finnhub for market data via Qt Network module
- **Real-time Updates**: Live market data streaming with Qt timers and network requests

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

## Acknowledgments

- [Finnhub.io](https://finnhub.io) for providing market data API

---

⚡ **Built for modern investors who want real-time insights into their financial portfolio**