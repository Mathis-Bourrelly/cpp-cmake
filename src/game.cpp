module;
#include <cmath>
#include <random>
#include <chrono>
import upgrade;

export module game;


export class Game
{
public:
    Game();

    void makePaperclip(int number);
    void increasePrice();
    void decreasePrice();
    void calculatePublicDemand();
    void autoSellPaperclips();
    int& getPaperclipCount();
    int& getUnsoldPaperclips();
    float& getPrice();
    float& getPublicDemand();
    float& getFunds();

    void buyMarketing();
    void buyAutoClipper();
    void buyWire();
    void buyWireBuyer();

    int getMarketingLevel() const;
    int& getAutoClipperLevel();

    float getMarketingCost() const;
    float getAutoClipperCost() const;

    void setWirePrice(float price);
    float getWirePrice() const;
    int getWireStock() const;
    bool getWireBuyerState() const;
    int& getMinimumStock();
    void setMinimumStock(int stock);
    int& getMaxPrice();
    void setMaxPrice(int price);
    void setAutoclipperPerformance(int perf);
    int getAutoclipperPerformance() const;
    std::string getEventText();
    bool isUpgradePurchased(int id) const;
    bool purchaseUpgrade(std::shared_ptr<upgrade::Upgrade> upgrade);
    void buyTrading();
    bool& getTradingStatus();
    float& getTradingCash();
    float& getTradingStocks();
    float& getTradingTotal();
    float& getProfitLossRatio();
    int& getTradingRiskLevel();
    int& getTradingEngineLevel();
    std::vector<float>& getStockPrices();

private:
    int paperclip_count;
    int unsold_paperclips;
    float price;
    float public_demand;
    float funds;
    std::string event;

    // Wire-specific variables
    float wire_price;
    int wire_stock;
    bool wire_buyer;
    int minimum_stock;
    int max_price;

    // Marketing and auto-clipper variables
    int marketing_level;
    int autoclipper_level;
    float marketing_cost;
    float autoclipper_cost;
    int autoclipper_performance;

    std::vector<int> purchased_upgrades;

    bool trading_status;
    float trading_cash; // Argent liquide pour le trading
    float trading_stocks; // Valeur des actions
    float trading_total; // Total (cash + stocks)
    float profit_loss_ratio; // Ratio de profit/perte
    int trading_risk_level; // Niveau de risque
    int trading_engine_level; // Niveau de l'engin de trading
    std::vector<float> stock_prices; // Liste des prix des actions
};

Game::Game() :
    paperclip_count(0),
    unsold_paperclips(0),
    price(0.10f),
    public_demand(0.16f),
    funds(50.0),
    event("Welcome to Paperclip Game !"),
    wire_price(20.0f),
    wire_stock(1000),
    wire_buyer(false),
    minimum_stock(500),
    max_price(20),
    marketing_level(0),
    autoclipper_level(0),
    marketing_cost(50.0f),
    autoclipper_cost(5.0f),
    autoclipper_performance(0),
    trading_cash(0),
    trading_stocks(0),
    trading_total(0),
    profit_loss_ratio(0.5f),
    trading_risk_level(7),
    trading_engine_level(0)
{
    calculatePublicDemand();
}


void Game::makePaperclip(const int number)
{
    if (wire_stock > 0)
    {
        paperclip_count += number;
        unsold_paperclips += number;
        wire_stock -= number;
    }
    switch (paperclip_count)
    {
    case 3000:
        event = "3000 paperclip created! New upgrade unlocked!";
        break;
    case 5000:
        event = "5000 paperclip created! New upgrade unlocked!";
        break;
    case 10000:
        event = "10000 paperclip created! New upgrade unlocked!";
        break;
    default:
        if (paperclip_count % 100000 == 0 && paperclip_count >= 100000)
        {
            event = std::to_string(paperclip_count) + " paperclips created!";
        }
        else if (paperclip_count % 10000 == 0 && paperclip_count >= 10000)
        {
            event = std::to_string(paperclip_count) + " paperclips created!";
        }
        else if (paperclip_count % 1000 == 0)
        {
            event = std::to_string(paperclip_count) + " paperclips created!";
        }
        break;
    }
}


void Game::increasePrice()
{
    price += 0.01f;
    calculatePublicDemand();
}

void Game::decreasePrice()
{
    price = std::max(0.01f, price - 0.01f);
    calculatePublicDemand();
}

void Game::buyMarketing()
{
    if (funds >= marketing_cost)
    {
        funds -= marketing_cost;
        ++marketing_level;
        marketing_cost *= 2;
        calculatePublicDemand();
    }
}

void Game::buyAutoClipper()
{
    if (funds >= autoclipper_cost)
    {
        funds -= autoclipper_cost;
        ++autoclipper_level;
        autoclipper_cost = pow(1.1f, autoclipper_level) + 5;
        calculatePublicDemand();
    }
}

void Game::buyWire()
{
    if (funds >= wire_price)
    {
        funds -= wire_price;
        wire_stock += 1000;
    }
}

void Game::buyWireBuyer()
{
    if (wire_buyer == false)
    {
        if (funds >= 100)
        {
            funds -= 100;
            wire_buyer = true;
        }
    }
}

void Game::buyTrading()
{
    if (trading_status == false)
    {
        trading_status = true;
    }
}

void Game::calculatePublicDemand()
{
    public_demand = std::pow(1.1, marketing_level) * (8.001f / price);
}

// Vérifie si une amélioration est achetée
bool Game::isUpgradePurchased(int id) const
{
    return std::find(purchased_upgrades.begin(), purchased_upgrades.end(), id) != purchased_upgrades.end();
}

// Achète une amélioration
bool Game::purchaseUpgrade(const std::shared_ptr<upgrade::Upgrade> upgrade)
{
    if (funds >= upgrade->cost && paperclip_count >= upgrade->paperclip_requirement &&
        !isUpgradePurchased(upgrade->id))
    {
        funds -= upgrade->cost;
        purchased_upgrades.push_back(upgrade->id);
        setAutoclipperPerformance(upgrade->perf);
        return true;
    }
    return false;
}

int& Game::getPaperclipCount() { return paperclip_count; }
int& Game::getUnsoldPaperclips() { return unsold_paperclips; }
float& Game::getPrice() { return price; }
int Game::getMarketingLevel() const { return marketing_level; }
int& Game::getAutoClipperLevel() { return autoclipper_level; }
float& Game::getPublicDemand() { return public_demand; }
float& Game::getFunds() { return funds; }
float Game::getMarketingCost() const { return marketing_cost; }
float Game::getAutoClipperCost() const { return autoclipper_cost; }
void Game::setWirePrice(float price) { wire_price = price; }
float Game::getWirePrice() const { return wire_price; }
int Game::getWireStock() const { return wire_stock; }
bool Game::getWireBuyerState() const { return wire_buyer; }
int& Game::getMinimumStock() { return minimum_stock; }
void Game::setMinimumStock(int stock) { minimum_stock = stock; }
int& Game::getMaxPrice() { return max_price; }
void Game::setMaxPrice(int price) { max_price = price; }
void Game::setAutoclipperPerformance(int perf) { autoclipper_performance = perf; }
int Game::getAutoclipperPerformance() const { return autoclipper_performance; }
std::string Game::getEventText() { return event; }
bool& Game::getTradingStatus() { return trading_status; }
float& Game::getTradingCash() { return trading_cash; }
float& Game::getTradingStocks() { return trading_stocks; }
float& Game::getTradingTotal() { return trading_total; }
float& Game::getProfitLossRatio() { return profit_loss_ratio; }
int& Game::getTradingRiskLevel() { return trading_risk_level; }
int& Game::getTradingEngineLevel() { return trading_engine_level; }
std::vector<float>& Game::getStockPrices() { return stock_prices; }
