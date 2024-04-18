#ifndef DOM_1_HEADER
#define DOM_1_HEADER

#include <vector>
#include <unordered_map>
#include <iostream>
#include "Order.h"
#include "DOM.h"


struct cmpByPriceAsc {
    bool operator()(Order a, Order b) const;
};

struct cmpByPriceDesc {
    bool operator()(Order a, Order b) const;
};


class DepthOfMarket_1: public IDepthOfMarket {
    private:
        std::unordered_map<size_t, Order> DOM;
        size_t counter;
    public:
        DepthOfMarket_1();
        ~DepthOfMarket_1();

        size_t add_order(const Order& new_order);

        bool edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type);

        bool delete_order(size_t delete_index);

        const Order* get_order(size_t order_index);

        std::vector<Order> get_DOM();

        void set_DOM(std::vector<Order> new_DOM);

        std::pair<std::vector<Order>, std::vector<Order>> show_10_best();

};

#endif