//
// Created by Megan Lov on 12/6/20.
//
#include "visualizer/simulator.h"

#include <catch2/catch.hpp>

TEST_CASE("Check member variables update") {

}

TEST_CASE("Check population gets created") {

}

TEST_CASE("Check feature values change") {
  SECTION("Check quarantine value changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }
  }

  SECTION("Check exposure time changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Exposure time is minimum before change") {

    }
  }

  SECTION("Check infected time changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Infected time is minimum before change") {

    }
  }

  SECTION("Check social distance changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Social distance is minimum before change") {

    }

    SECTION("Social distance is maximum before change") {

    }
  }

  SECTION("Check infection radius changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Infection radius is minimum before change") {

    }

    SECTION("Infection radius cannot be lower than social distance value") {

    }
  }
}

TEST_CASE("Check member variables clear") {

}

TEST_CASE("Check GetFeatureBeingChanged() works") {
  SECTION("Quarantine is feature being changed") {

  }

  SECTION("Exposed time is feature being changed") {

  }

  SECTION("Infected time is feature being changed") {

  }

  SECTION("Social distance is feature being changed") {

  }

  SECTION("Radius of infection is feature being changed") {

  }
}