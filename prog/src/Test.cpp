#include "Test.h"


bool DomTest::check_add_order(std::vector<Order> input_data, Order test_order, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);
    size_t add_order_index = DOM.add_order(test_order);
    std::vector<Order> result_vector = DOM.get_DOM();
    if(const Order* returned_order = DOM.get_order(add_order_index)) {
        if(*returned_order == test_order) {
            return true;
        }
        std::cout << "Переданный и полученнный по индексу " << add_order_index << " объекты не совпадают" << std::endl;
        return false;
    }
    std::cout << "Не найден переданный объект" << std::endl;
    return false;
}

bool DomTest::check_delete_order(std::vector<Order> input_data, size_t delete_index, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);
    const Order* deleted_order = DOM.get_order(delete_index); 
    if(DOM.delete_order(delete_index)) {
        if(((DOM.get_DOM().size() == 0) && !(DOM.get_order(delete_index))) || !(DOM.get_order(delete_index))) {
            return true;
        }
        std::cout << "Объект с индексом " << delete_index << " не удалился" << std::endl;
        return false;
    }
    std::cout << "Нет элемента с индексом " << delete_index << std::endl;
    return false;
}

bool DomTest::check_edit_order(std::vector<Order> input_data, size_t edit_order_index, float new_price, uint64_t new_amount, order_book_type new_type, Order expected_order, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);
    if(DOM.edit_order(edit_order_index, new_price, new_amount, new_type)) {
        const Order* edited_order;
        if(edited_order=DOM.get_order(edit_order_index)) {
            if(*(edited_order) == expected_order) {
                return true;
            }
            std::cout << "Элемент с индексом " << edit_order_index << " не соотвествует переданному элементу" << std::endl;
            return false;
        }
        std::cout << "Элемент с индексом " << edit_order_index << " не найден" << std::endl;
        return false;
    }
    std::cout << "Ошибка при редоктировании элемента с индексом " << edit_order_index << std::endl;
    return false;

}

bool DomTest::check_show_10_order(std::vector<Order> input_data,  std::pair<std::vector<Order>, std::vector<Order>> expected_result, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);
    std::pair<std::vector<Order>, std::vector<Order>> result = DOM.show_10_best();
    std::vector<Order> expected_sell_orders = expected_result.first;
    std::vector<Order> expected_buy_orders = expected_result.second;
    std::vector<Order> result_sell_orders = result.first;
    std::vector<Order> result_buy_orders = result.second;

    if(expected_sell_orders.size() == result_sell_orders.size()) {
        for(int i = 0; i < result_sell_orders.size(); i++) {
            if(result_sell_orders[i].get_price() != expected_sell_orders[i].get_price()) {
                std::cout << "Не сопадает " << i << "-ый элемент списокв Sell" << std::endl;
                return false;
            }
        }
    }
    else {
        std::cout << "Не сопадает размер полученого и ожидаемого списка элементов Sell" << std::endl;
        return false;
    }

    if(expected_buy_orders.size() == result_buy_orders.size()) {
        for(int i = 0; i < result_buy_orders.size(); i++) {
            if(result_buy_orders[i].get_price() != expected_buy_orders[i].get_price()) {
                std::cout << "Не сопадает " << i << "-ый элемент списокв Buy" << std::endl;
                return false;
            }
        }
    }
    else {
        std::cout << "Не сопадает размер полученого и ожидаемого списка элементов Buy" << std::endl;
        return false;
    }
    return true;
}


float DomTest::measure_time_add_order(std::vector<Order> input_data, Order test_order, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);

    std::vector<Order> test_data;

    uint64_t N = 1000;

    for(int i = 0; i < N; i++) {
        uint64_t new_amount = rand() % 100;
        float new_price = (float)(rand()) / (float)(rand());
        order_book_type new_type;
        if(rand() % 2 == 0) {
            new_type = order_book_type::Sell;
        }
        else {
            new_type = order_book_type::Buy;
        }
        Order new_order(new_price, new_amount, new_type);
        test_data.push_back(new_order);
    } 

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(auto order: test_data) {
        DOM.add_order(order);
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = (end - start) / N;

    std::cout << "Среднее время выполнения add_order - " << time_span.count() << " миллисекунд";
    std::cout << std::endl;
    return time_span.count();
}

float DomTest::measure_time_delete_order(std::vector<Order> input_data, size_t delete_index, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++) {
        DOM.delete_order(input_data[i].get_index());

    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = (end - start) / 1000;

    std::cout << "Среднее врeмя выполнения delete_order - " << time_span.count() << " миллисекунд";
    std::cout << std::endl;
    return time_span.count();
}

float DomTest::measure_time_edit_order(std::vector<Order> input_data, size_t edit_order_index, float new_price, uint64_t new_amount, order_book_type new_type, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);


    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++) {
        uint64_t rand_amount = rand() % 100;
        float rand_price = (float)(rand()) / (float)(rand());
        order_book_type rand_type;
        if(rand() % 2 == 0) {
            rand_type = order_book_type::Sell;
        }
        else {
            rand_type = order_book_type::Buy;
        }

        DOM.edit_order(input_data[i].get_index(), rand_price, rand_amount, rand_type);

    }

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> time_span = (end - start) / 1000;

    std::cout << "Среднее врeмя выполнения edit_order - " << time_span.count() << " миллисекунд";
    std::cout << std::endl;
    return time_span.count();
}

float DomTest::measure_time_show_10_order(std::vector<Order> input_data, IDepthOfMarket& DOM) {
    DOM.set_DOM(input_data);
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    DOM.show_10_best();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = end - start;
 
    std::cout << "Время выполнения show_10_best - " << time_span.count() << " миллисекунд";
    std::cout << std::endl;
    return time_span.count();
}

void DomTest::test_methods(IDepthOfMarket& DOM) {
    std::cout << "Начало тестирвания методов" << std::endl;
    std::vector<Order> input_data;
    
    std::cout << "Генерация тестовых входных данных" << std::endl;

    input_data.push_back(Order(2.91554, 41, order_book_type::Sell));
    input_data.push_back(Order(1.36993, 69, order_book_type::Sell));
    input_data.push_back(Order(4.28817, 62, order_book_type::Buy)); 
    input_data.push_back(Order(1.68929, 81, order_book_type::Buy));
    input_data.push_back(Order(2.474, 95, order_book_type::Sell)); 
    input_data.push_back(Order(3.7427, 91, order_book_type::Buy));
    input_data.push_back(Order(0.710751, 92, order_book_type::Sell));
    input_data.push_back(Order(3.65247, 18, order_book_type::Sell));
    input_data.push_back(Order(6.17335, 71, order_book_type::Sell));
    input_data.push_back(Order(1.54382, 67, order_book_type::Sell));
    input_data.push_back(Order(0.760201, 3, order_book_type::Buy));
    input_data.push_back(Order(0.308038, 73, order_book_type::Buy));
    input_data.push_back(Order(0.268838, 53, order_book_type::Sell)); 
    input_data.push_back(Order(1.63483, 62, order_book_type::Buy)); 
    input_data.push_back(Order(0.353845, 23, order_book_type::Sell));
    input_data.push_back(Order(0.136773, 16, order_book_type::Sell));
    input_data.push_back(Order(0.136773, 88, order_book_type::Sell));
    input_data.push_back(Order(0.825184, 64, order_book_type::Buy)); 
    input_data.push_back(Order(0.276118, 90, order_book_type::Sell));
    input_data.push_back(Order(1.275, 6, order_book_type::Sell));

    Order test_order(0.34756, 45, order_book_type::Buy);

    std::vector<Order> expected_results_show_10_best_sell;
    std::vector<Order> expected_results_show_10_best_buy;
    
    std::cout << "Создание тестовых входных данных для 10 лучших заказов" << std::endl;

    // 5 Best Sell Orders:
    expected_results_show_10_best_sell.push_back(Order(0.136773, 16, order_book_type::Sell)); 
    expected_results_show_10_best_sell.push_back(Order(0.136773, 88, order_book_type::Sell));
    expected_results_show_10_best_sell.push_back(Order(0.268838, 53, order_book_type::Sell));
    expected_results_show_10_best_sell.push_back(Order(0.276118, 90, order_book_type::Sell));
    expected_results_show_10_best_sell.push_back(Order(0.353845, 23, order_book_type::Sell));
    // 5 Best Buy Orders:
    expected_results_show_10_best_buy.push_back(Order(4.28817, 62, order_book_type::Buy));
    expected_results_show_10_best_buy.push_back(Order(3.7427, 91, order_book_type::Buy));
    expected_results_show_10_best_buy.push_back(Order(1.68929, 81, order_book_type::Buy));
    expected_results_show_10_best_buy.push_back(Order(1.63483, 62, order_book_type::Buy));
    expected_results_show_10_best_buy.push_back(Order(0.825184, 64, order_book_type::Buy));

    std::pair<std::vector<Order>, std::vector<Order>> expected_results_show_10_best = {expected_results_show_10_best_sell, expected_results_show_10_best_buy};

    std::cout << "Начинается тест метода add_order..." << std::endl;
    check_add_order(input_data, test_order, DOM);
    std::cout << "Начинается тест метода delete_order..." << std::endl;
    check_delete_order(input_data, 10, DOM);
    std::cout << "Начинается тест метода edit_order..." << std::endl;
    Order expected_order(14.136773, 256, order_book_type::Buy);
    check_edit_order(input_data, 15, 14.136773, 256, order_book_type::Buy, expected_order, DOM);
    std::cout << "Начинается тест метода show_10_order..." << std::endl;
    check_show_10_order(input_data, expected_results_show_10_best, DOM);
}

void  DomTest::time_methods(IDepthOfMarket& DOM) {
    std::cout << "Начинается замер времени" << std::endl;
    std::vector<Order> input_data;
    for(int i = 0; i < 100000; i++) {
        uint64_t new_amount = rand() % 100;
        float new_price = (float)(rand()) / (float)(rand());
        order_book_type new_type;
        if(rand() % 2 == 0) {
            new_type = order_book_type::Sell;
        }
        else {
            new_type = order_book_type::Buy;
        }
        Order new_order(new_price, new_amount, new_type);
        input_data.push_back(new_order);
    } 

    Order test_order(5.3847, 57, order_book_type::Buy);
    measure_time_add_order(input_data, test_order, DOM);
    measure_time_delete_order(input_data, 34, DOM);
    measure_time_edit_order(input_data, 78, 9.677, 12, order_book_type::Sell, DOM);
    measure_time_show_10_order(input_data, DOM);

 }