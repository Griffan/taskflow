#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include <taskflow/taskflow.hpp>

// --------------------------------------------------------
// Testcase: static_task_exception
// --------------------------------------------------------

void static_task_exception(unsigned W) {

  tf::Taskflow taskflow;
  tf::Executor executor(W);

  std::atomic<size_t> counter(0);

  auto A = taskflow.emplace([&](){ counter.fetch_add(1, std::memory_order_relaxed); });
  auto B = taskflow.emplace([&](){ counter.fetch_add(1, std::memory_order_relaxed); });
  auto C = taskflow.emplace([&](){ counter.fetch_add(1, std::memory_order_relaxed); });
  auto D = taskflow.emplace([&](){ counter.fetch_add(1, std::memory_order_relaxed); });
  auto E = taskflow.emplace([&](){ counter.fetch_add(1, std::memory_order_relaxed); });
  auto F = taskflow.emplace([&](){ counter.fetch_add(1, std::memory_order_relaxed); });

  A.precede(B);
  B.precede(C);
  C.precede(D);
  D.precede(E);
  E.precede(F);

  REQUIRE_NOTHROW(executor.run(taskflow).get());
  REQUIRE(counter == 6);

  counter = 0;
  C.work([](){ throw std::runtime_error("x"); });
  
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "x", std::runtime_error);
  REQUIRE(counter == 2);

  try {
    counter = 0;
    executor.run(taskflow).get();
    REQUIRE(false);
  }
  catch(std::runtime_error& e) {
    REQUIRE(counter == 2);
    REQUIRE(std::strcmp(e.what(), "x") == 0);
  }
}

TEST_CASE("Exception.StaticTask.1thread") {
  static_task_exception(1);
}

TEST_CASE("Exception.StaticTask.2threads") {
  static_task_exception(2);
}

TEST_CASE("Exception.StaticTask.3threads") {
  static_task_exception(3);
}

TEST_CASE("Exception.StaticTask.4threads") {
  static_task_exception(4);
}

// --------------------------------------------------------
// Testcase: condition_task_exception
// --------------------------------------------------------

void condition_task_exception(unsigned W) {

  tf::Taskflow taskflow;
  tf::Executor executor(W);

  std::atomic<size_t> counter(0);

  auto A = taskflow.emplace([&](){ 
    counter.fetch_add(1, std::memory_order_relaxed); 
    return 0;
  });
  auto B = taskflow.emplace([&](){ 
    counter.fetch_add(1, std::memory_order_relaxed); 
    return 0;
  });
  auto C = taskflow.emplace([&](){ 
    counter.fetch_add(1, std::memory_order_relaxed); 
    return 0;
  });
  auto D = taskflow.emplace([&](){ 
    counter.fetch_add(1, std::memory_order_relaxed); 
    return 0;
  });
  auto E = taskflow.emplace([&](){ 
    counter.fetch_add(1, std::memory_order_relaxed); 
    return 0;
  });
  auto F = taskflow.emplace([&](){ 
    counter.fetch_add(1, std::memory_order_relaxed); 
    return 0;
  });

  A.precede(B);
  B.precede(C);
  C.precede(D);
  D.precede(E);
  E.precede(F);

  REQUIRE_NOTHROW(executor.run(taskflow).get());
  REQUIRE(counter == 6);

  counter = 0;
  C.work([](){ throw std::runtime_error("x"); });
  
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "x", std::runtime_error);
  REQUIRE(counter == 2);

  try {
    counter = 0;
    executor.run(taskflow).get();
    REQUIRE(false);
  }
  catch(std::runtime_error& e) {
    REQUIRE(counter == 2);
    REQUIRE(std::strcmp(e.what(), "x") == 0);
  }
}

TEST_CASE("Exception.ConditionTask.1thread") {
  condition_task_exception(1);
}

TEST_CASE("Exception.ConditionTask.2threads") {
  condition_task_exception(2);
}

TEST_CASE("Exception.ConditionTask.3threads") {
  condition_task_exception(3);
}

TEST_CASE("Exception.ConditionTask.4threads") {
  condition_task_exception(4);
}

// --------------------------------------------------------
// Testcase: multicondition_task_exception
// --------------------------------------------------------

void multicondition_task_exception(unsigned W) {

  tf::Taskflow taskflow;
  tf::Executor executor(W);

  std::atomic<size_t> counter(0);

  auto A = taskflow.emplace([&](){ 
    tf::SmallVector<int> ret = {0};
    counter.fetch_add(1, std::memory_order_relaxed); 
    return ret;
  });
  auto B = taskflow.emplace([&](){ 
    tf::SmallVector<int> ret = {0};
    counter.fetch_add(1, std::memory_order_relaxed); 
    return ret;
  });
  auto C = taskflow.emplace([&](){ 
    tf::SmallVector<int> ret = {0};
    counter.fetch_add(1, std::memory_order_relaxed); 
    return ret;
  });
  auto D = taskflow.emplace([&](){ 
    tf::SmallVector<int> ret = {0};
    counter.fetch_add(1, std::memory_order_relaxed); 
    return ret;
  });
  auto E = taskflow.emplace([&](){ 
    tf::SmallVector<int> ret = {0};
    counter.fetch_add(1, std::memory_order_relaxed); 
    return ret;
  });
  auto F = taskflow.emplace([&](){ 
    tf::SmallVector<int> ret = {0};
    counter.fetch_add(1, std::memory_order_relaxed); 
    return ret;
  });

  A.precede(B);
  B.precede(C);
  C.precede(D);
  D.precede(E);
  E.precede(F);

  REQUIRE_NOTHROW(executor.run(taskflow).get());
  REQUIRE(counter == 6);

  counter = 0;
  C.work([](){ throw std::runtime_error("x"); });
  
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "x", std::runtime_error);
  REQUIRE(counter == 2);

  try {
    counter = 0;
    executor.run(taskflow).get();
    REQUIRE(false);
  }
  catch(std::runtime_error& e) {
    REQUIRE(counter == 2);
    REQUIRE(std::strcmp(e.what(), "x") == 0);
  }
}

TEST_CASE("Exception.MultiConditionTask.1thread") {
  multicondition_task_exception(1);
}

TEST_CASE("Exception.MultiConditionTask.2threads") {
  multicondition_task_exception(2);
}

TEST_CASE("Exception.MultiConditionTask.3threads") {
  multicondition_task_exception(3);
}

TEST_CASE("Exception.MultiConditionTask.4threads") {
  multicondition_task_exception(4);
}

// ----------------------------------------------------------------------------
// Subflow Task
// ----------------------------------------------------------------------------

void subflow_task_exception(unsigned W) {

  tf::Taskflow taskflow;
  tf::Executor executor(W);
  
  // subflow work throws
  for(int i=0; i<100; i++) {
    taskflow.emplace([](tf::Subflow& sf){
      throw std::runtime_error("x");
      sf.emplace([](){});
      sf.emplace([](){ throw std::runtime_error("y"); });
    });
  }
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "x", std::runtime_error);

  taskflow.clear();
  
  // subflow's task throws
  for(int i=0; i<100; i++) {
    taskflow.emplace([](tf::Subflow& sf){
      sf.emplace([](){});
      sf.emplace([](){ throw std::runtime_error("y"); });
    });
  }
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "y", std::runtime_error);
}

TEST_CASE("Exception.SubflowTask.1thread") {
  subflow_task_exception(1);
}

TEST_CASE("Exception.SubflowTask.2threads") {
  subflow_task_exception(2);
}

TEST_CASE("Exception.SubflowTask.3threads") {
  subflow_task_exception(3);
}

TEST_CASE("Exception.SubflowTask.4threads") {
  subflow_task_exception(4);
}

// ----------------------------------------------------------------------------
// Exception.AsyncTask
// ----------------------------------------------------------------------------

void async_task_exception(unsigned W) {

  // executor async
  tf::Executor executor(W);

  auto fu1 = executor.async([](){
    return 1;
  });
  REQUIRE(fu1.get() == 1);
  
  auto fu2 = executor.async([](){
    throw std::runtime_error("x");
  });
  REQUIRE_THROWS_WITH_AS(fu2.get(), "x", std::runtime_error);
  
  // exception is caught without any action
  executor.silent_async([](){
    throw std::runtime_error("y"); 
  });

  executor.wait_for_all();
}

TEST_CASE("Exception.AsyncTask.1thread") {
  async_task_exception(1);
}

TEST_CASE("Exception.AsyncTask.2threads") {
  async_task_exception(2);
}

TEST_CASE("Exception.AsyncTask.3threads") {
  async_task_exception(3);
}

TEST_CASE("Exception.AsyncTask.4threads") {
  async_task_exception(4);
}

// ----------------------------------------------------------------------------
// Runtime Async Task
// ----------------------------------------------------------------------------

void runtime_async_task_exception(unsigned W) {

  // executor async
  tf::Executor executor(W);
  tf::Taskflow taskflow;
  int flag = 0;

  // runtime async
  auto A = taskflow.emplace([](tf::Runtime& rt){
    auto fu1 = rt.async([](){ return 1; });
    REQUIRE(fu1.get() == 1);
    auto fu2 = rt.async([](){ throw std::runtime_error("z"); });
    REQUIRE_THROWS_WITH_AS(fu2.get(), "z", std::runtime_error);
  });
  auto B = taskflow.emplace([&](){
    flag = 1;
  });
  executor.run(taskflow).wait();
  REQUIRE(flag == 1);

  // runtime silent async
  flag = 0;
  taskflow.clear();
  A = taskflow.emplace([&](tf::Runtime& rt){
    rt.silent_async([&](){ throw std::runtime_error("a"); });
    rt.corun_all();  // must join to propagate the exception to taskflow
                     // because async is independent of taskflow
    flag = 1;
  });
  B = taskflow.emplace([&](){
    flag = 2;
  });
  A.precede(B);
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "a", std::runtime_error);
  REQUIRE(flag == 1);
}

TEST_CASE("Exception.RuntimeAsyncTask.2threads") {
  runtime_async_task_exception(2);
}

TEST_CASE("Exception.RuntimeAsyncTask.3threads") {
  runtime_async_task_exception(3);
}

TEST_CASE("Exception.RuntimeAsyncTask.4threads") {
  runtime_async_task_exception(4);
}

// ----------------------------------------------------------------------------
// Exception.ThreadSafety
// ----------------------------------------------------------------------------

void thread_safety(unsigned W) {

  tf::Executor executor(W);
  tf::Taskflow taskflow;

  for(int i=0; i<1000; i++) {
    taskflow.emplace([&](){ throw std::runtime_error("x"); });
  }

  // thread sanitizer should not report any data race 
  REQUIRE_THROWS_WITH_AS(executor.run(taskflow).get(), "x", std::runtime_error);
}

TEST_CASE("Exception.ThreadSafety.1thread") {
  thread_safety(1);
}

TEST_CASE("Exception.ThreadSafety.2threads") {
  thread_safety(2);
}

TEST_CASE("Exception.ThreadSafety.3threads") {
  thread_safety(3);
}

TEST_CASE("Exception.ThreadSafety.4threads") {
  thread_safety(4);
}

// ----------------------------------------------------------------------------
// Subflow exception
// ----------------------------------------------------------------------------

void test_subflow_exception(unsigned W) {

  tf::Executor executor(W);
  tf::Taskflow taskflow;

  taskflow.emplace([&] (tf::Subflow& sf0) {
    for (int i = 0; i < 16; ++i) {
      sf0.emplace([&, i] (tf::Subflow& sf1) {
        for (int j = 0; j < 16; ++j) {
          sf1.emplace([&, j] () {
            std::stringstream ss;
            ss << "exception (" << i << " " << j << ")";
            throw std::runtime_error(ss.str());
            std::cout << "post-join (" << i << " " << j << ")" << std::endl;
          });
        }
        sf1.join();
        std::cout << "post-join " << i << std::endl;
      });
    }
  });

  try {
    executor.run(taskflow).get();
  }
  catch (const std::runtime_error& e) {
    std::cerr << "caught std::runtime_error " << e.what() << std::endl;
  }
}

TEST_CASE("Exception.Subflow.1thread") {
  test_subflow_exception(1);
}

