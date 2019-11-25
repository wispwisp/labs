#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "RuleOfFiveBehaviourLogger.hpp"

#include "Counter.hpp"

using ::testing::Eq;

struct TestsByCounter : public testing::Test
{
  std::shared_ptr<ICounter> counter = std::make_shared<Counter>();
  // ASSERT_ANY_THROW(vector.push_back(0));
  // ASSERT_NO_THROW(vector.resize(N));
};

TEST_F(TestsByCounter, Created)
{
  RuleOfFiveBehaviourLogger obj(counter);

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounter, Copied)
{
  RuleOfFiveBehaviourLogger obj(counter);

  RuleOfFiveBehaviourLogger obj2 = obj;

  ASSERT_THAT(counter->count(), Eq(2));
}

TEST_F(TestsByCounter, CtorCopied)
{
  RuleOfFiveBehaviourLogger obj(counter);

  RuleOfFiveBehaviourLogger obj2(obj);

  ASSERT_THAT(counter->count(), Eq(2));
}

TEST_F(TestsByCounter, BracketMoved)
{
  RuleOfFiveBehaviourLogger obj(counter);

  RuleOfFiveBehaviourLogger obj2{ std::move(obj) };

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounter, CtorMoved)
{
  RuleOfFiveBehaviourLogger obj(counter);

  RuleOfFiveBehaviourLogger obj2( std::move(obj) );

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounter, OpMoved)
{
  RuleOfFiveBehaviourLogger obj(counter);

  RuleOfFiveBehaviourLogger obj2 = std::move(obj) ;

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounter, CtorReturn)
{
  RuleOfFiveBehaviourLogger obj = RuleOfFiveBehaviourLogger(counter);

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounter, Declaration)
{
  // Wrong !!!
  RuleOfFiveBehaviourLogger obj(RuleOfFiveBehaviourLogger(counter));

  ASSERT_THAT(counter->count(), Eq(0));
}

TEST_F(TestsByCounter, AntiDeclaration)
{
  // additional '()'
  RuleOfFiveBehaviourLogger obj((RuleOfFiveBehaviourLogger(counter)));

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounter, CopyAssigned)
{
  RuleOfFiveBehaviourLogger obj(counter);

  RuleOfFiveBehaviourLogger obj2(counter);

  ASSERT_THAT(counter->count(), Eq(2));

  obj = obj2;

  ASSERT_THAT(counter->count(), Eq(3));
}

TEST_F(TestsByCounter, MoveAssigned)
{
  RuleOfFiveBehaviourLogger obj(counter);
  RuleOfFiveBehaviourLogger obj2(counter);
  ASSERT_THAT(counter->count(), Eq(2));

  obj = std::move(obj2);
  ASSERT_THAT(counter->count(), Eq(2));
}

struct TestsByCounterWithMap : public TestsByCounter
{
  std::map<int, RuleOfFiveBehaviourLogger> map{};
};

TEST_F(TestsByCounterWithMap, Copied)
{
  RuleOfFiveBehaviourLogger obj(counter);

  map.insert(std::make_pair(10, obj));

  ASSERT_THAT(counter->count(), Eq(2));
}

TEST_F(TestsByCounterWithMap, AllMoved)
{
  RuleOfFiveBehaviourLogger obj(counter);

  std::pair<const int, RuleOfFiveBehaviourLogger> p(10,
                                                    std::move(obj));
  map.insert(std::move(p));

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounterWithMap, CreateAndMove)
{
  RuleOfFiveBehaviourLogger obj(counter);

  auto p = std::make_pair(10, std::move(obj));

  map.insert(std::move(p));

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounterWithMap, OneLineMoved)
{
  RuleOfFiveBehaviourLogger obj(counter);

  map.insert(std::make_pair(10, std::move(obj)));

  ASSERT_THAT(counter->count(), Eq(1));
}

TEST_F(TestsByCounterWithMap, Emplace)
{
  RuleOfFiveBehaviourLogger obj(counter);

  map.emplace(10, obj);

  ASSERT_THAT(counter->count(), Eq(2));
}

TEST_F(TestsByCounterWithMap, EmplaceMoved)
{
  RuleOfFiveBehaviourLogger obj(counter);

  map.emplace(10, std::move(obj));

  ASSERT_THAT(counter->count(), Eq(1));
}

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
