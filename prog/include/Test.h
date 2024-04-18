#include <iostream>
#include <vector>
#include <chrono>
#include "DOM.h"


class DomTest {
    public:
        // Проверка методов
        bool check_add_order(std::vector<Order> input_data, Order test_order, IDepthOfMarket& DOM);
        bool check_delete_order(std::vector<Order> input_data, size_t delete_index, IDepthOfMarket& DOM);
        bool check_edit_order(std::vector<Order> input_data, size_t edit_order_index, float new_price, uint64_t new_amount, order_book_type new_type, Order expected_order, IDepthOfMarket& DOM);
        bool check_show_10_order(std::vector<Order> input_data,  std::pair<std::vector<Order>, std::vector<Order>> expected_result, IDepthOfMarket& DOM);

        // Замер времени выполнения методов
        float measure_time_add_order(std::vector<Order> input_data, Order test_order, IDepthOfMarket& DOM);
        float measure_time_delete_order(std::vector<Order> input_data, size_t delete_index, IDepthOfMarket& DOM);
        float measure_time_edit_order(std::vector<Order> input_data, size_t edit_order_index, float new_price, uint64_t new_amount, order_book_type new_type, IDepthOfMarket& DOM);
        float measure_time_show_10_order(std::vector<Order> input_data, IDepthOfMarket& DOM);

        void test_methods(IDepthOfMarket& DOM);
        void time_methods(IDepthOfMarket& DOM);
}; 

