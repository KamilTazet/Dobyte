#include "Order.h"


Order::Order(float new_price, int new_amount, order_book_type new_type): price(new_price), amount(new_amount), type(new_type) {
    index = 0;
}

Order::Order() {
    index = 0;
    price = 0.0;
    amount = 0;
    type =order_book_type::Sell;
}

float Order::get_price() const {
    return price;
}

void Order::set_index(int new_index) {
    index = new_index;
}

int Order::get_index() const {
    return index;
}

void Order::set_price(float new_price) {
    price = new_price;
}

int Order::get_amount() const {
    return amount;
}

void Order::set_amount(int new_amount) {
    amount = new_amount;
}

order_book_type Order::get_type() const {
    return type;
}

void Order::set_type(order_book_type new_type) {
    type = new_type;
}

void Order::print_without_index() const {
    std::cout << "Order: price = " << price << ", amount = " << amount << ", ";
    if(type == order_book_type::Sell) {
        std::cout << "type = Sell" << std::endl;
    }
    else {
        std::cout << "type = Buy" << std::endl;
    }
}

void Order::print_with_index() const {
    std::cout << "Order: price = " << price << ", amount = " << amount << ", ";
    if(type == order_book_type::Sell) {
        std::cout << "type = Sell, ";
    }
    else {
        std::cout << "type = Buy, ";
    }
    std::cout << " index = " << index << std::endl;
}

void Order::operator=(const Order& second_order) {
    index = second_order.index; 
    price = second_order.price;
    amount = second_order.amount;
    type = second_order.type;
}


bool Order::operator<(const Order& second_order) const  {
    if((price < second_order.price)) {
        return true;
    }
    else {
        return false;
    }
}

bool Order::operator>(const Order& second_order) const  {
    if((price > second_order.price)) {
        return true;
    }
    else {
        return false;
    }
}

bool Order::operator==(const Order& second_order) const {
    if((price == second_order.price) &&
    (amount == second_order.amount) &&
    (type == second_order.type)) {
        return true;
    }
    else {
        return false;
    }
}

bool Order::operator!=(const Order& second_order) const  {
    if((price != second_order.price) ||
    (amount != second_order.amount) ||
    (type != second_order.type)) {
        return true;
    }
    else {
        return false;
    }
}

bool Order::operator>=(const Order& second_order) const  {
    if((price >= second_order.price)) {
        return true;
    }
    else {
        return false;
    }
}

bool Order::operator<=(const Order& second_order) const  {
    if((price <= second_order.price)) {
        return true;
    }
    else {
        return false;
    }
}