
#include <algorithm>
#include <queue>
#include "DOM_3.h"


DepthOfMarket_3::DepthOfMarket_3() {
    counter = 0;
}

DepthOfMarket_3::~DepthOfMarket_3() {
}

size_t DepthOfMarket_3::add_order(const Order& new_order) { 
    size_t index = ++counter;
    std::pair<size_t, Order> new_pair(index, std::move(new_order));
    std::pair<float, size_t> new_price_pair(new_order.get_price(), index);
    new_pair.second.set_index(index);
    DOM.insert(new_pair);
    price_map.insert(new_price_pair);
    return index;
}

bool DepthOfMarket_3::edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type) {
    auto found_iter = DOM.find(index);

    float old_price = found_iter->second.get_price();
    size_t old_index = found_iter->second.get_index();
    if(new_price != old_price) {
        auto iter = price_map.find(old_price);
        while(iter->first == old_price) {
            if(iter->second == old_index) {
                price_map.erase(iter);
                std::pair<float, size_t> new_price_id_pair(new_price, index);
                price_map.insert(new_price_id_pair);
                break;
            }
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

bool DepthOfMarket_3::delete_order(size_t delete_index) {
    auto iter = DOM.find(delete_index);
    if(iter != DOM.end()) {
        float deleted_order_price = iter->second.get_price();
        DOM.erase(iter);
        auto price_map_iter = price_map.find(deleted_order_price);
        while(price_map_iter->first == deleted_order_price) {
            if(price_map_iter->second == delete_index) {
                price_map.erase(price_map_iter);
                break;
            }
        }
        return true;
    }
    return false;
}

const Order* DepthOfMarket_3::get_order(size_t order_index) {
    auto found_iter = DOM.find(order_index);
    if(found_iter != DOM.end()) {
        return &(found_iter->second);
    }
    return nullptr;
}

std::vector<Order> DepthOfMarket_3::get_DOM() {
    std::vector<Order> order_vector;
    for( std::map<size_t, Order>::iterator it = DOM.begin(); it != DOM.end(); ++it ) {
        order_vector.push_back( it->second );
    }
    return order_vector;
}

void DepthOfMarket_3::set_DOM(std::vector<Order> new_DOM) {
    counter = 0;
    DOM.clear();
    price_map.clear();
    size_t DOM_size = new_DOM.size();
    for(auto new_order: new_DOM) {
        size_t index = ++counter;
        std::pair<size_t, Order> new_pair(index, std::move(new_order));
        std::pair<float, size_t> price_pair(new_order.get_price(), index);
        new_pair.second.set_index(index);
        DOM.insert(new_pair);
        price_map.insert(price_pair);
    }
}

std::pair<std::vector<Order>, std::vector<Order>> DepthOfMarket_3::show_10_best(){
    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;

    std::multimap<float, size_t>::iterator iter_sell = price_map.begin();
    std::multimap<float, size_t>::reverse_iterator iter_buy = price_map.rbegin();
    while( (iter_sell != price_map.end()) && (iter_buy != price_map.rend()) ) {
        if(sell_orders.size() < 5) {
            if(DOM[iter_sell->second].get_type() == order_book_type::Sell) {
                sell_orders.push_back(DOM[iter_sell->second]);
            }
            iter_sell++;
        }
        if(buy_orders.size() < 5) {
            if(DOM[iter_buy->second].get_type() == order_book_type::Buy) {
                buy_orders.push_back(DOM[iter_buy->second]);
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