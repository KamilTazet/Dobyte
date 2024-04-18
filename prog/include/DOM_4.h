#ifndef DOM_4_HEADER
#define DOM_4_HEADER

#include <vector>
#include "Order.h"
#include "DOM.h"

class DepthOfMarket_4: public IDepthOfMarket {
    private:
        std::vector<Order> DOM;
        size_t counter;
    public:
        DepthOfMarket_4();
        ~DepthOfMarket_4();

        size_t add_order(const Order& new_order);

        bool edit_order(size_t index, float new_price, uint64_t new_amount, order_book_type new_type);

        bool delete_order(size_t delete_index);

        const Order* get_order(size_t order_index);

        std::vector<Order> get_DOM();

        void set_DOM(std::vector<Order> new_DOM);

        std::pair<std::vector<Order>, std::vector<Order>> show_10_best();

};

#endif