
#include <algorithm>
#include <queue>
#include "DOM_1.h"

bool cmpByPriceAsc::operator()(Order a, Order b) const {
    return a.get_price() < b.get_price();
}


bool cmpByPriceDesc::operator()(Order a, Order b) const {
    return a.get_price() > b.get_price();
}

DepthOfMarket_1::DepthOfMarket_1() {
    counter = 0;
}

DepthOfMarket_1::~DepthOfMarket_1() {}

size_t DepthOfMarket_1::add_order(const Order& new_order) {
    size_t index = ++counter;
    std::pair<size_t, Order> new_pair(index, std::move(new_order));
    new_pair.second.set_index(index);
    DOM.insert(new_pair);
    return index;
}

bool DepthOfMarket_1::edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type) {
    auto found_iter = DOM.find(index);
    
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

bool DepthOfMarket_1::delete_order(size_t delete_index) {
    auto iter = DOM.find(delete_index);
    if(iter != DOM.end()) {
        DOM.erase(iter);
        return true;
    }
    return false;
}

const Order* DepthOfMarket_1::get_order(size_t order_index) {
     auto found_iter = DOM.find(order_index);
    if(found_iter != DOM.end()) {
        return &(found_iter->second);
    }
    else {
        return nullptr;
    }
}

std::vector<Order> DepthOfMarket_1::get_DOM() {
    std::vector<Order> order_vector;
    for( std::map<size_t, Order>::iterator it = DOM.begin(); it != DOM.end(); ++it ) {
        order_vector.push_back( it->second );
    }
    return order_vector;
}

void DepthOfMarket_1::set_DOM(std::vector<Order> new_DOM) {
    counter = 0;
    DOM.clear();
    size_t DOM_size = new_DOM.size();
    for(auto new_order: new_DOM) {
        size_t index = ++counter;
        std::pair<float, Order> new_pair(index, std::move(new_order));
        new_pair.second.set_index(index);
        DOM.insert(new_pair);
    }
}

std::pair<std::vector<Order>, std::vector<Order>> DepthOfMarket_1::show_10_best(){
    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;

    std::priority_queue<Order, std::vector<Order>, cmpByPriceAsc> sell_queue;

    std::priority_queue<Order, std::vector<Order>, cmpByPriceDesc> buy_queue;

    for(auto dom_pair: DOM) {
        if(dom_pair.second.get_type() == order_book_type::Sell) {
            sell_queue.push(dom_pair.second);
        }
        else {
            buy_queue.push(dom_pair.second);
        }
        if(sell_queue.size() > 5) {
            sell_queue.pop();
        }
        if(buy_queue.size() > 5) {
            buy_queue.pop();
        }
    }

    while(sell_queue.size() > 0) {
        sell_orders.push_back(sell_queue.top());
        sell_queue.pop();
    }
    while(buy_queue.size() > 0) {
        buy_orders.push_back(buy_queue.top());
        buy_queue.pop();
    }    
    std::reverse(sell_orders.begin(), sell_orders.end());
    std::reverse(buy_orders.begin(), buy_orders.end());
    std::pair<std::vector<Order>, std::vector<Order>> return_pair = {sell_orders, buy_orders};
    return return_pair;
}