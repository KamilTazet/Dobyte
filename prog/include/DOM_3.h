#ifndef DOM_3_HEADER
#define DOM_3_HEADER

#include <vector>
#include <map>
#include "Order.h"
#include "DOM.h"


class DepthOfMarket_3: public IDepthOfMarket {
    private:
        std::map<size_t, Order> DOM;
        std::multimap<float, size_t> price_map;
        size_t counter;
    public:
        DepthOfMarket_3();
        ~DepthOfMarket_3();

        size_t add_order(const Order& new_order);

        bool edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type);

        bool delete_order(size_t delete_index);

        const Order* get_order(size_t order_index);

        std::vector<Order> get_DOM();

        void set_DOM(std::vector<Order> new_DOM);

        std::pair<std::vector<Order>, std::vector<Order>> show_10_best();

};

#endif