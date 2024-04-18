#ifndef ORDER_HEADER
#define ORDER_HEADER

#include <stdint.h>
#include <iostream>


enum class order_book_type {Buy, Sell};

class Order {
    private:
        size_t index; 
        float price;
        uint64_t amount;
        order_book_type type;
    public:
        Order(float new_price, int new_amount, order_book_type new_type);
        Order();
        float get_price() const;
        void set_index(int new_index);
        int get_index() const;
        void set_price(float new_price);
        int get_amount() const;
        void set_amount(int new_amount);
        order_book_type get_type() const;
        void set_type(order_book_type new_type);
        void print_without_index() const;
        void print_with_index() const;

        void operator=(const Order& second_order);

        bool operator<(const Order& second_order) const;
        bool operator>(const Order& second_order) const;
        bool operator==(const Order& second_order) const;
        bool operator!=(const Order& second_order) const;
        bool operator>=(const Order& second_order) const;
        bool operator<=(const Order& second_order) const;
};

#endif