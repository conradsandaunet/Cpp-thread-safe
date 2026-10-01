#include <catch2/catch_test_macros.hpp>
#include "ThreadSafeQueue.hpp"
#include <thread>
#include <vector>
#include <atomic>
#include <string>
#include <chrono>

TEST_CASE("push and pop of one single element", "[basic]") {
    ThreadSafeQueue<int> q;
    q.push(42);

    auto result = q.pop();
    REQUIRE(result.has_value());
    REQUIRE(*result == 42);
}

TEST_CASE("works with non-trivial types such as std::string", "[basic]") {
    ThreadSafeQueue<std::string> q;
    q.push("hello");
    q.push("world");

    REQUIRE(*q.pop() == "hello");
    REQUIRE(*q.pop() == "world");
}

TEST_CASE("maintance FIFO-order", "[basic]") {
    ThreadSafeQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    REQUIRE(*q.pop() == 1);
    REQUIRE(*q.pop() == 2);
    REQUIRE(*q.pop() == 3);
}

TEST_CASE("try_pop on an empty queue returns nullopt immediately", "[try_pop]") {
    ThreadSafeQueue<int> q;
    REQUIRE_FALSE(q.try_pop().has_value());
}

TEST_CASE("try_pop returns value when queue is not empty", "[try_pop]") {
    ThreadSafeQueue<int> q;
    q.push(7);
    auto result = q.try_pop();
    REQUIRE(result.has_value());
    REQUIRE(*result == 7);
}

TEST_CASE("empty() and size() reflects actuall contents", "[state]") {
    ThreadSafeQueue<int> q;
    REQUIRE(q.empty());
    REQUIRE(q.size() == 0);


}



