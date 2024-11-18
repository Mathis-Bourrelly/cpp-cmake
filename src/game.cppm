module;
#include <cmath>
#include <random>
#include <chrono>
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
    int& getMaxPrice();
    void setMaxPrice(int price);


private:
    int paperclip_count;
    int unsold_paperclips;
    float price;
    float public_demand;
    float funds;

    // Wire-specific variables
    float wire_price;
    int wire_stock;
    bool wire_buyer;

    // Marketing and auto-clipper variables
    int marketing_level;
    int autoclipper_level;
    float marketing_cost;
    float autoclipper_cost;
    int minimum_stock;
    int max_price;

};

Game::Game() :
    paperclip_count(0),
    unsold_paperclips(0),
    price(0.10f),
    public_demand(0.16f),
    funds(0.0),
    wire_price(20.0f),
    wire_stock(1000),
    wire_buyer(false),
    marketing_level(0),
    autoclipper_level(0),
    marketing_cost(200.0f),
    autoclipper_cost(5.0f),
    minimum_stock(500),
    max_price(20)
{
    calculatePublicDemand();
}


void Game::makePaperclip(const int number)
{
    paperclip_count+= number;
    unsold_paperclips+= number;
    wire_stock -= number;
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

void Game::buyWire() {
    if (funds >= wire_price) {
        funds -= wire_price;
        wire_stock += 1000;
    }
}

void Game::buyWireBuyer() {
    if (wire_buyer == false)
    {
        if (funds >= 1) {
            funds -= 1;
            wire_buyer = true;
        }
    }
}

void Game::calculatePublicDemand()
{
    public_demand = std::pow(1.1, marketing_level) * (8.001f / price);
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
int& Game::getMaxPrice() { return max_price; }
void Game::setMaxPrice(int price) { max_price = price; }