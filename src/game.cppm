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
    void setMinimumStock(int stock);
    int& getMaxPrice();
    void setMaxPrice(int price);
    std::string getEventText();


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


};

Game::Game() :
    paperclip_count(0),
    unsold_paperclips(0),
    price(0.10f),
    public_demand(0.16f),
    funds(0.0),
    event("Welcome to Paperclip Game !"),
    wire_price(20.0f),
    wire_stock(1000),
    wire_buyer(false),
    minimum_stock(500),
    max_price(20),
    marketing_level(0),
    autoclipper_level(0),
    marketing_cost(200.0f),
    autoclipper_cost(5.0f)
{
    calculatePublicDemand();
}


void Game::makePaperclip(const int number)
{
    if(wire_stock > 0)
    {
        paperclip_count+= number;
        unsold_paperclips+= number;
        wire_stock -= number;
    }
    switch (paperclip_count) {
    case 1000:
        event = "1000 paperclip created! New upgrade unlocked!";
        break;
    case 3000:
        event = "2000 paperclip created! New upgrade unlocked!";
        break;
    case 5000:
        event = "5000 paperclip created! New upgrade unlocked!";
        break;
    case 10000:
        event = "10000 paperclip created! New upgrade unlocked!";
        break;
    case 50000:
        event = "50000 paperclip created! New upgrade unlocked!";
        break;
    default:
        if (paperclip_count % 100000 == 0 && paperclip_count >= 100000) {
            event = std::to_string(paperclip_count) + " paperclips created!";
        } else if (paperclip_count % 10000 == 0 && paperclip_count >= 10000) {
            event = std::to_string(paperclip_count) + " paperclips created!";
        } else if (paperclip_count % 1000 == 0) {
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
void Game::setMinimumStock(int stock ) { minimum_stock = stock; }
int& Game::getMaxPrice() { return max_price; }
void Game::setMaxPrice(int price) { max_price = price; }
std::string Game::getEventText() { return event; }