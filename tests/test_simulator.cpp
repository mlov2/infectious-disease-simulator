//
// Created by Megan Lov on 12/6/20.
//
#include "visualizer/simulator.h"

#include <catch2/catch.hpp>

using disease::visualizer::Simulator;

TEST_CASE("Check member variables update") {
  Simulator simulator;

  SECTION("Population has been created") {
    simulator.CreatePopulation();

    simulator.Update();

    REQUIRE(simulator.GetParticlesInfo().size() == 201);
    REQUIRE(simulator.GetTimePassed() == 1);
  }

  SECTION("Population has not been created") {
    simulator.Update();

    REQUIRE(simulator.GetParticlesInfo().size() == 0);
    REQUIRE(simulator.GetTimePassed() == 0);
  }
}

TEST_CASE("Check population gets created") {
  Simulator simulator;

  simulator.CreatePopulation();
  REQUIRE(simulator.GetDiseaseClass().GetPopulation().size() == 201);
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
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Exposure time is maximum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }
  }

  SECTION("Check infected time changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Infected time is minimum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Infected time is maximum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }
  }

  SECTION("Check social distance changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Social distance is minimum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Social distance is maximum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }
  }

  SECTION("Check infection radius changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Infection radius is minimum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Infection radius is maximum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
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