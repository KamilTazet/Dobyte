
#include <algorithm>
#include "DOM_2.h"


DepthOfMarket_2::DepthOfMarket_2() {
    counter = 0;
}

DepthOfMarket_2::~DepthOfMarket_2() {
}

size_t DepthOfMarket_2::add_order(const Order& new_order) { 
    size_t index = ++counter;
    std::pair<float, Order> new_pair(new_order.get_price(), std::move(new_order));
    new_pair.second.set_index(index);
    DOM.insert(new_pair);
    return index;
}

bool DepthOfMarket_2::edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type) {
    auto found_iter = DOM.begin();
    for(found_iter; found_iter != DOM.end(); found_iter++) {
        if(found_iter->second.get_index() == index) {
            break;
        }
    }

    if(found_iter != DOM.end()) {
        found_iter->second.set_price(new_price);
        found_iter->second.set_amount(new_amount);
        found_iter->second.set_type(new_type);
        return true;
    }
    else {
        return false;
    }
}

bool DepthOfMarket_2::delete_order(size_t delete_index) {
    auto iter = DOM.begin();
    for(iter; iter != DOM.end(); iter++) {
        if(iter->second.get_index() == delete_index) {
            break;
        }
    }
    if(iter != DOM.end()) {
        DOM.erase(iter);
        return true;
    }
    return false;
}

const Order* DepthOfMarket_2::get_order(size_t order_index) {
    auto found_iter = DOM.begin();
    for(found_iter; found_iter != DOM.end(); found_iter++) {
        if(found_iter->second.get_index() == order_index) {
            return &(found_iter->second);
        } 
    }
    return nullptr;
}

std::vector<Order> DepthOfMarket_2::get_DOM() {
    std::vector<Order> order_vector;
    for( std::map<float, Order>::iterator it = DOM.begin(); it != DOM.end(); ++it ) {
        order_vector.push_back( it->second );
    }
    return order_vector;
}

void DepthOfMarket_2::set_DOM(std::vector<Order> new_DOM) {
    counter = 0;
    DOM.clear();
    size_t DOM_size = new_DOM.size();
    for(auto new_order: new_DOM) {
        size_t index = ++counter;
        std::pair<float, Order> new_pair(new_order.get_price(), std::move(new_order));
        new_pair.second.set_index(index);
        DOM.insert(new_pair);
    }
}

std::pair<std::vector<Order>, std::vector<Order>> DepthOfMarket_2::show_10_best(){
    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;

    std::map<float, Order>::iterator iter_sell = DOM.begin();
    std::map<float, Order>::reverse_iterator iter_buy = DOM.rbegin();
    while( (iter_sell != DOM.end()) && (iter_buy != DOM.rend()) ) {
        if(sell_orders.size() < 5) {
            if(iter_sell->second.get_type() == order_book_type::Sell) {
                sell_orders.push_back(iter_sell->second);
            }
            iter_sell++;
        }
        if(buy_orders.size() < 5) {
            if(iter_buy->second.get_type() == order_book_type::Buy) {
                buy_orders.push_back(iter_buy->second);
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