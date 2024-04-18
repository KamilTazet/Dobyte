
#include <algorithm>
#include "DOM_5.h"

DepthOfMarket_5::DepthOfMarket_5() {
    counter = 0;
}

DepthOfMarket_5::~DepthOfMarket_5() {
}

size_t DepthOfMarket_5::add_order(const Order& new_order) {
    size_t index = ++counter; 
    DOM.push_back(std::move(new_order)); 
    DOM.back().set_index(index);
    return index;
}

bool DepthOfMarket_5::edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type) {
    for(auto edit_iter = DOM.begin(); edit_iter < DOM.end(); edit_iter++) {
        if(edit_iter->get_index() == index) {
            edit_iter->set_price(new_price);
            edit_iter->set_amount(new_amount);
            edit_iter->set_type(new_type);
            return true;
        }
    }
    return false;
}

bool DepthOfMarket_5::delete_order(size_t delete_index) {
    for(auto delete_iter = DOM.begin(); delete_iter < DOM.end(); delete_iter++) {
        if(delete_iter->get_index() == delete_index) {    
            DOM.erase(delete_iter);
            return true;
        }
    }
    return false;
}

const Order* DepthOfMarket_5::get_order(size_t order_index) {
    for(auto search_iter = DOM.begin(); search_iter < DOM.end(); search_iter++) {
        if(search_iter->get_index() == order_index) {  
            return &(*search_iter); 
        } 
    }
    return nullptr;
}

std::vector<Order> DepthOfMarket_5::get_DOM() {
    return DOM;
}

void DepthOfMarket_5::set_DOM(std::vector<Order> new_DOM) {
    counter = 0;
    DOM.clear();
    size_t DOM_size = new_DOM.size();
    for(auto new_order: new_DOM) {
        size_t index = ++counter;
        DOM.push_back(std::move(new_order));
        DOM.back().set_index(index);
    }
}

std::pair<std::vector<Order>, std::vector<Order>> DepthOfMarket_5::show_10_best(){
    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;
    std::sort(DOM.begin(), DOM.end());

    std::vector<Order>::iterator iter_sell = DOM.begin();
    std::vector<Order>::reverse_iterator iter_buy = DOM.rbegin();
    while( (iter_sell != DOM.end()) && (iter_buy != DOM.rend()) ) {
        if(sell_orders.size() < 5) {
            if(iter_sell->get_type() == order_book_type::Sell) {
                sell_orders.push_back(*iter_sell);
            }
            iter_sell++;
        }
        if(buy_orders.size() < 5) {
            if(iter_buy->get_type() == order_book_type::Buy) {
                buy_orders.push_back(*iter_buy);
            }
            iter_buy++;
        }
        if((sell_orders.size()==5) && (buy_orders.size()==5)) {
            break;
        }
    }

    std::pair<std::vector<Order>, std::vector<Order>> return_pair = {sell_orders, buy_orders};
    return return_pair; 
}