#ifndef DOM_HEADER
#define DOM_HEADER

#include <vector>
#include <map>
#include <iostream>
#include "Order.h"


class IDepthOfMarket {
    public:
        virtual ~IDepthOfMarket(){};

        virtual size_t add_order(const Order& new_order) = 0;

        virtual bool edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type) = 0;

        virtual bool delete_order(size_t delete_index) = 0;

        virtual const Order* get_order(size_t order_index) = 0;

        virtual std::vector<Order> get_DOM() = 0;

        virtual void set_DOM(std::vector<Order> new_DOM) = 0;

        virtual std::pair<std::vector<Order>, std::vector<Order>> show_10_best() = 0;

};
#endif