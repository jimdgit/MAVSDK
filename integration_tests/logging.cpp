#include <iostream>
#include <unistd.h>
#include "dronelink.h"
#include <gtest/gtest.h>
#include "integration_test_helper.h"

using namespace dronelink;

void test_logging()
{
    usleep(5000000);

    DroneLink dl;

    DroneLink::ConnectionResult ret = dl.add_udp_connection();
    ASSERT_EQ(ret, DroneLink::ConnectionResult::SUCCESS);

    usleep(2000000);

    Logging::Result log_ret = dl.device().logging().start_logging();

    if (log_ret == Logging::Result::COMMAND_DENIED) {
        usleep(10000);
        dl.device().logging().stop_logging();
        //ASSERT_EQ(log_ret, Logging::Result::SUCCESS);
        usleep(10000);
        log_ret = dl.device().logging().start_logging();
    }

    ASSERT_EQ(log_ret, Logging::Result::SUCCESS);


    while (true) {
        usleep(1000000);
    }

    log_ret = dl.device().logging().stop_logging();
    ASSERT_EQ(log_ret, Logging::Result::SUCCESS);
}

TEST(Logging, StartStop)
{
    sitl::start();
    test_logging();
    sitl::stop();
}
