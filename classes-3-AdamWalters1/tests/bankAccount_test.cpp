#include "bankAccount.h"
#include <gtest/gtest.h>

class GradingListener : public ::testing::EmptyTestEventListener {
    int passedTests = 0;
    const int totalTests;

public:
    explicit GradingListener(int total) : totalTests(total) {}

    void OnTestEnd(const ::testing::TestInfo& test_info) override {
        if (test_info.result()->Passed()) {
            passedTests++;
        }
    }

    void OnTestProgramEnd(const ::testing::UnitTest& /* unit_test */) override {
        int grade = static_cast<int>((static_cast<double>(passedTests) / totalTests) * 10);
        std::cout << "Grade: " << grade << "/10 (" << passedTests << " out of " << totalTests << " tests passed)" << std::endl;
    }
};

// Test for deposit functionality
TEST(BankAccountTest, Deposit) {
    bankAccount account("Test User", "savings", 100.0, 1.0);
    account.deposit(50);
    EXPECT_EQ(account.getBalance(), 150.0);
}

// Test for withdrawal functionality
TEST(BankAccountTest, Withdraw) {
    bankAccount account("Test User", "savings", 100.0, 1.0);
    account.withdraw(30);
    EXPECT_EQ(account.getBalance(), 70.0);
}

// Test for insufficient funds during withdrawal
TEST(BankAccountTest, WithdrawInsufficientFunds) {
    bankAccount account("Test User", "savings", 100.0, 1.0);
    account.withdraw(150); // Attempt to withdraw more than the balance
    EXPECT_EQ(account.getBalance(), 100.0); // Balance should remain unchanged
}

// Test for getting account balance
TEST(BankAccountTest, CheckBalance) {
    bankAccount account("Test User", "savings", 200.0, 1.0);
    EXPECT_EQ(account.getBalance(), 200.0);
}

// Test for updating balance with interest
TEST(BankAccountTest, UpdateBalanceWithInterest) {
    bankAccount account("Test User", "savings", 100.0, 10.0); // 10% interest
    account.updateBalance();
    EXPECT_NEAR(account.getBalance(), 110.0, 0.01); // Allow a small margin of error
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int totalTests = ::testing::UnitTest::GetInstance()->total_test_count();
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new GradingListener(totalTests));

    int result = RUN_ALL_TESTS();

    // Remove the listener so it doesn't interfere with potential other test runs.
    delete listeners.Release(listeners.default_result_printer());

    return result;
}
